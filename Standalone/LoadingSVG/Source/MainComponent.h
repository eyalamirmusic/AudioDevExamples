#pragma once

#include "JuceHeader.h"
#include "SVGDisplay.h"

class MainComponent
    : public Component
    , public Button::Listener
{
public:
    MainComponent()
    {
        addAndMakeVisible(loadButton);
        loadButton.addListener(this);

        setSize(600, 400);
    }

    void resized() override
    {
        constexpr int loadButtonHeight = 50;
        loadButton.setBounds(0, 0, 80, loadButtonHeight);

        if (svg != nullptr)
        {
            svg->setBounds(getLocalBounds()
                               .withY(loadButtonHeight)
                               .reduced(0, loadButtonHeight));
        }
    }

    void buttonClicked(Button* button) override
    {
        std::unique_ptr<FileChooser> fc;
        fc = std::make_unique<FileChooser>("Load image file");

        fc->browseForFileToOpen();

        auto result = fc->getResult();

        if (result.existsAsFile())
            loadImageFromFile(result);
    }

private:
    void loadImageFromFile(const File& fileToLoad)
    {
        svg = std::make_unique<SVGDisplayer>(fileToLoad);
        addAndMakeVisible(*svg);
        resized();
    }

    TextButton loadButton {"Load File"};
    std::unique_ptr<SVGDisplayer> svg;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
