#include "AudioCallback.h"
#include "ConsoleToot.h"

//This is an example on running a very simple audio callback in the console
//To use it, you can just create a ConsoleToot object on the stack
//And attach your own AudioIODeviceCallback.

int main(int argc, char* argv[])
{
    SineWaveCallback audioCallback;
    ConsoleToot console(audioCallback);
}
