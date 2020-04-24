#include "PluginProcessor.h"
#include "PluginEditor.h"

MidiEffectAudioProcessor::MidiEffectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

//==============================================================================
const String MidiEffectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiEffectAudioProcessor::acceptsMidi() const
{
    DBG ("Accepts MIDI:" << JucePlugin_WantsMidiInput);

   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiEffectAudioProcessor::producesMidi() const
{
    DBG ("Produces MIDI:" << JucePlugin_ProducesMidiOutput);

   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidiEffectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidiEffectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidiEffectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidiEffectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidiEffectAudioProcessor::setCurrentProgram (int index)
{
}

const String MidiEffectAudioProcessor::getProgramName (int index)
{
    return {};
}

void MidiEffectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MidiEffectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MidiEffectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiEffectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MidiEffectAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    //Clearing the buffer to mute any audio that might come in
    buffer.clear();

    //Only forwarding the call to the actual processor:
    midiProcessor.process(midiMessages);
}

//==============================================================================
bool MidiEffectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MidiEffectAudioProcessor::createEditor()
{
    return new MidiEffectAudioProcessorEditor (*this);
}

//==============================================================================
void MidiEffectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MidiEffectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiEffectAudioProcessor();
}
