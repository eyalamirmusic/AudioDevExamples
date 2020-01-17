#pragma once

#include "JuceHeader.h"

/*
  A little helper class to simplify creating a new parameter list,
  caching it and saving it to a parameter layout.

  Use it in a scoped way:

  void addParams(AudioProcessorValueTreeState::ParameterLayout& layout)
  {
       ParameterList list;

        gain = list.add<AudioParameterFloat>("Gain", "Gain", 0.0f, 1.0f, 0.1f);
        bypass = list.addNamed<AudioParameterBool>("Bypass", false);
  }
 */
class ParameterList
{
public:
    //Constructor: stores a reference to the ParameterLayout
    //During the destructor, all parameters added using add() or addNamed()
    //Will be added to the layout
    explicit ParameterList(
        AudioProcessorValueTreeState::ParameterLayout& layoutToUse)
        : layout(layoutToUse)
    {
    }

    //Destructor: only here values will be added to the layout
    ~ParameterList() { layout.add(params.begin(), params.end()); }

    //Adds the parameter to the list, returning a pointer to it
    //which you can store for future reference in your processor
    template <typename T, typename... Args>
    T* add(Args&&... args)
    {
        auto newParam = new T(std::forward<Args>(args)...);
        params.emplace_back(newParam);

        return newParam;
    }

    //Similar to add(), but also copies the value used for parameterID field
    //into the name field, to avoid code duplication
    template <typename T, typename ParamName, typename... Args>
    T* addNamed(const ParamName& name, Args&&... args)
    {
        return add<T>(name, name, std::forward<Args>(args)...);
    }

private:
    AudioProcessorValueTreeState::ParameterLayout& layout;
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
};
