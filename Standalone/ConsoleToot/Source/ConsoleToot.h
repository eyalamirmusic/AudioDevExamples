#pragma once

#include "JuceHeader.h"

//A class for testing audio streaming.
//To initialize one of those, just create it on the stack, and pass any
//object that inherits from AudioIODeviceCallback to it:

namespace ConsoleTootConsts
{
//You can change this const for a different playing time:
constexpr int playbackTime = 2000;
}

class ConsoleToot
{
public:
    explicit ConsoleToot(AudioIODeviceCallback& cb)
    {
        String err = deviceManager.initialiseWithDefaultDevices(0, 2);

        if (err.isEmpty())
            triggerAudioCallback(cb);
        else
            std::cout << "could not open device : " << err << "\n";
    }

private:
    void triggerAudioCallback(AudioIODeviceCallback& cb)
    {
        std::cout << "device opened : " << getDeviceName() << "\n";
        deviceManager.addAudioCallback(&cb);

        // keep the program running so the audio has a chance to play:
        Thread::sleep(ConsoleTootConsts::playbackTime);
        std::cout << "closing device...\n";
    }

    const String& getDeviceName()
    {
        return deviceManager.getCurrentAudioDevice()->getName();
    }

    // not used for "GUI" in this case,
    // just for initing and shutting down the MessageManager
    ScopedJuceInitialiser_GUI gui_init;

    //Audio Device manager:
    AudioDeviceManager deviceManager;
};