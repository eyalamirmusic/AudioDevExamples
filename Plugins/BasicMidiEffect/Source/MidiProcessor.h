#pragma once

#include "JuceHeader.h"

//A very simple class, that takes a midi buffer and adds another note
//At at fixed interval for each incoming note on or off:

class MidiProcessor
{
public:
    void process(MidiBuffer& midiMessages);

private:

    void processMidiInput(const MidiBuffer& midiMessages);
    void addTransposedNote(MidiMessage messageToTranspose, int samplePos);

    //We create a temporary buffer that represents our changes
    MidiBuffer processedBuffer;
};