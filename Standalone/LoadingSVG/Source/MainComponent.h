#pragma once

#include "JuceHeader.h"
#include "SVGDisplay.h"

constexpr int loadButtonHeight = 50;

class MainComponent
    : public Component
    , public FileDragAndDropTarget
{
public:
    MainComponent()
    {
        addAndMakeVisible(loadButton);
        addAndMakeVisible(stretchButton);

        loadButton.onClick = [&] { buttonClicked();};
        stretchButton.onClick = [&] { stretchButtonClicked();};

        setSize(600, 400);
    }

    bool isInterestedInFileDrag(const StringArray&) override { return true; }
    void filesDropped(const StringArray& files, int, int) override
    {
        loadImageFromFile(files[0]);
    }

    void resized() override
    {
        loadButton.setBounds(0, 0, 80, loadButtonHeight);
        stretchButton.setBounds(100, 0, 80, loadButtonHeight);

        if (svg != nullptr)
        {
            svg->setBounds(getLocalBounds()
                               .withY(loadButtonHeight)
                               .reduced(0, loadButtonHeight));
        }
    }

    void stretchButtonClicked()
    {
        if (stretchButton.getToggleState())
            placement = RectanglePlacement::stretchToFit;
        else
            placement = RectanglePlacement::doNotResize;

        repaint();
    }

    void buttonClicked()
    {
        fc = std::make_unique<FileChooser>("Load image file");

        auto flags =
            FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;

        auto callback = [this](const FileChooser& chooser)
        {
            auto result = chooser.getResult();

            if (result.existsAsFile())
                loadImageFromFile(result);
        };

        fc->launchAsync(flags, callback);

        auto result = fc->getResult();
    }

private:
    void loadImageFromFile(const File& fileToLoad)
    {
        svg = std::make_unique<SVGDisplayer>(fileToLoad, placement);
        addAndMakeVisible(*svg);
        resized();
    }

    TextButton loadButton {"Load File"};
    ToggleButton stretchButton {"Stretch"};
    RectanglePlacement placement = RectanglePlacement::doNotResize;
    std::unique_ptr<SVGDisplayer> svg;
    std::unique_ptr<FileChooser> fc;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
