#include "MidiProcessor.h"

constexpr int interval = 4;

void MidiProcessor::process(MidiBuffer& midiMessages)
{
    processedBuffer.clear();
    processMidiInput(midiMessages);
    midiMessages.swapWith(processedBuffer);
}

void MidiProcessor::processMidiInput(const MidiBuffer& midiMessages)
{
    //new JUCE 6 way of iterating through the midi buffer:
    for (auto message: midiMessages)
        addTransposedNote(message.getMessage(), message.samplePosition);
}

void MidiProcessor::addTransposedNote(MidiMessage messageToTranspose, int samplePos)
{
    //Adds the original event first
    processedBuffer.addEvent(messageToTranspose, samplePos);

    auto oldNoteNum = messageToTranspose.getNoteNumber();
    messageToTranspose.setNoteNumber(oldNoteNum + interval);

    processedBuffer.addEvent(messageToTranspose, samplePos);
}
