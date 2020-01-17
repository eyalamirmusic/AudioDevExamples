#pragma once

#include "JuceHeader.h"
#include "CustomProcessor.h"


//This process class does very little.
//All it does is initialize the Processors class, and the
//AudioProcessorValueTreeState class, which grabs the parameters from the Processors.
//
//Later, it's forwarding the processBlock call to the Processors class
//
//Look at CustomProcessor.h for more info:
//==============================================================================
/**
*/
class DynamicParametersAudioProcessor : public AudioProcessor
{
public:
    //==============================================================================
    DynamicParametersAudioProcessor();

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
    void changeProgramName(int index, const String& newName) override;

    //==============================================================================
    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:

    Processors processors;
    AudioProcessorValueTreeState state {
        *this, nullptr, "GainProcessors", processors.getLayout()};

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DynamicParametersAudioProcessor)
};
