#pragma once

#include "JuceHeader.h"

//An example for an audio callback, generating a sine wave oscillator:

class SineWaveCallback : public AudioIODeviceCallback
{
public:
    void audioDeviceIOCallback(const float** inputChannelData,
                               int numInputChannels,
                               float** outputChannelData,
                               int numOutputChannels,
                               int numSamples) override
    {
        for (int i = 0; i < numSamples; ++i)
        {
            float s = gain * sin(phase);

            for (int j = 0; j < numOutputChannels; ++j)
            {
                outputChannelData[j][i] = s;
            }

            phase += (freq / sampleRate) * juce::MathConstants<float>::twoPi;
        }
    }

    void audioDeviceAboutToStart(AudioIODevice* device) override
    {
        phase = 0.f;
        sampleRate = (float) device->getCurrentSampleRate();
    }

    void audioDeviceStopped() override {}

private:
    float freq = 440.f;
    float gain = 0.1f;
    float phase = 0.f;
    float sampleRate = 0.f;
};
