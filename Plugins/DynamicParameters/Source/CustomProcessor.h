#pragma once

#include "ParameterHelpers.h"

using Layout = AudioProcessorValueTreeState::ParameterLayout;

//A parameter class, meant to help the processor with creating and caching
//The parameters, and hand them as a ParameterLayout for use by the plugin
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

//A simple processor class, only applying simple gain, and possibly bypassed
//Reads the value from the cached parameter pointers in the ProcessorParams class
struct Processor
{
    void process(AudioBuffer<float>& buffer)
    {
        if (!params.bypass->get())
            buffer.applyGain(params.gain->get());
    }

    ProcessorParams params;
};

//A simple chainer class, providing an interface for the processor to get the
//parameter layout from all processors combined, and later call process()
//on all of them:

struct Processors
{
    Layout getLayout()
    {
        Layout layout;

        int index = 0;

        for (auto& processor: processors)
        {
            //Creates the processor name using some prefix and it's index
            String processorName = "Processor " + String(index++) + " ";

            //Asks each processor to add it's own parameters
            processor.params.addParams(layout, processorName);
        }

        return layout;
    }

    //Simple forwarding to the actual processing functions
    void process(AudioBuffer<float>& buffer)
    {
        for (auto& processor: processors)
            processor.process(buffer);
    }

    Processor processors[3];
};