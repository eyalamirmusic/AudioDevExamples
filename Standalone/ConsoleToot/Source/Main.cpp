#include "JuceHeader.h"

class MyCallback : public AudioIODeviceCallback
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

int main(int argc, char* argv[])
{
    // not used for "GUI" in this case,
    // just for initing and shutting down the MessageManager
    ScopedJuceInitialiser_GUI gui_init;
    AudioDeviceManager aman;

    String err = aman.initialiseWithDefaultDevices(0, 2);

    if (err.isEmpty())
    {
        std::cout << "device opened : " << aman.getCurrentAudioDevice()->getName()
                  << "\n";
        MyCallback cb;
        aman.addAudioCallback(&cb);

        // keep the program running so the audio has a chance to play:
        Thread::sleep(2000);
        std::cout << "closing device...\n";
    }
    else
        std::cout << "could not open device : " << err << "\n";

    return 0;
}
