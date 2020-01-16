#pragma once

#include "JuceHeader.h"
#include "MidiProcessor.h"

/* This is a very basic project, just showing how to create a simple
 * midi processing effect. All the processor does here is forward the
 * processing call to a MidiProcessor object, that adds an interval
 * to each incoming note
 * */

//#undef JucePlugin_IsMidiEffect
//#if JucePlugin_Build_AU
//#define JucePlugin_IsMidiEffect 1
//#else
//#define JucePlugin_IsMidiEffect 0
//#endif

class MidiEffectAudioProcessor  : public AudioProcessor
{
public:
    MidiEffectAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

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
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:

    //This is the actual processor that does something with midi events:
    MidiProcessor midiProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiEffectAudioProcessor)
};
