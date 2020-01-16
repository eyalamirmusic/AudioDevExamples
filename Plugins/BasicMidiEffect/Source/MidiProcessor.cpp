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
    MidiBuffer::Iterator it(midiMessages);
    MidiMessage currentMessage;
    int samplePos;

    while (it.getNextEvent(currentMessage, samplePos))
    {
        if (currentMessage.isNoteOnOrOff())
            addTransposedNote(currentMessage, samplePos);

        processedBuffer.addEvent(currentMessage, samplePos);
    }
}

void MidiProcessor::addTransposedNote(MidiMessage messageToTranspose, int samplePos)
{
    auto oldNoteNum = messageToTranspose.getNoteNumber();
    messageToTranspose.setNoteNumber(oldNoteNum + interval);

    processedBuffer.addEvent(messageToTranspose, samplePos);
}
