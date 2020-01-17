#pragma once

#include "ParameterHelpers.h"

using Layout = AudioProcessorValueTreeState::ParameterLayout;

struct ProcessorParams
{
    void addParams(Layout& layout,
                   const String& prefix = String())
    {
        ParameterList list(layout);

        //Create all your processor parameters, in this case appending the processor name:
        bypass = list.addNamed<AudioParameterBool>(prefix + "Bypass", false);
        gain = list.addNamed<AudioParameterFloat>(prefix + "Gain", 0.0f, 1.0f, 0.1f);

        //When exiting the scope, parameters will be added to the given layout
    }

    //A cached version of the parameter you can use in the process block
    AudioParameterFloat* gain = nullptr;
    AudioParameterBool* bypass = nullptr;
};

struct Processor
{
    void process(AudioBuffer<float>& buffer)
    {
        if (!params.bypass->get())
            buffer.applyGain(params.gain->get());
    }

    ProcessorParams params;
};

struct Processors
{
    Layout getLayout()
    {
        Layout layout;

        int index = 0;

        for (auto& processor: processors)
        {
            String name = "Processor " + String(index++) + " ";
            processor.params.addParams(layout, name);
        }

        return layout;
    }

    void process(AudioBuffer<float>& buffer)
    {
        for (auto& processor: processors)
            processor.process(buffer);
    }

    Processor processors[3];
};