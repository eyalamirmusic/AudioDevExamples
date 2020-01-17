#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DynamicParametersAudioProcessor::DynamicParametersAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
}

//==============================================================================
const String DynamicParametersAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DynamicParametersAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool DynamicParametersAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool DynamicParametersAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double DynamicParametersAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DynamicParametersAudioProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
        // so this should be at least 1, even if you're not really implementing programs.
}

int DynamicParametersAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DynamicParametersAudioProcessor::setCurrentProgram(int index)
{
}

const String DynamicParametersAudioProcessor::getProgramName(int index)
{
    return {};
}

void DynamicParametersAudioProcessor::changeProgramName(int index,
                                                        const String& newName)
{
}

//==============================================================================
void DynamicParametersAudioProcessor::prepareToPlay(double sampleRate,
                                                    int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DynamicParametersAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DynamicParametersAudioProcessor::isBusesLayoutSupported(
    const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void DynamicParametersAudioProcessor::processBlock(AudioBuffer<float>& buffer,
                                                   MidiBuffer& midiMessages)
{
    processors.process(buffer);
}

//==============================================================================
bool DynamicParametersAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DynamicParametersAudioProcessor::createEditor()
{
    return new GenericAudioProcessorEditor(*this);
}

//==============================================================================
void DynamicParametersAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DynamicParametersAudioProcessor::setStateInformation(const void* data,
                                                          int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DynamicParametersAudioProcessor();
}
