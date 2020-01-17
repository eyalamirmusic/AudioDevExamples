#pragma once

#include "JuceHeader.h"

class InvalidImageLabel : public Label
{
public:
    InvalidImageLabel()
    {
        setText("Invalid Image", dontSendNotification);
        setJustificationType(Justification::centred);
    }
};

class SVGDisplayer : public Component
{
public:
    explicit SVGDisplayer(const File& fileToLoad)
    {
        image = Drawable::createFromImageFile(fileToLoad);

        if (image != nullptr)
            addAndMakeVisible(*image);
        else
            addAndMakeVisible(invalidImageLabel);
    }

    void resized() override
    {
        if (image != nullptr)
            image->setBounds(getLocalBounds());
        else
            invalidImageLabel.setBounds(getLocalBounds());
    }

    InvalidImageLabel invalidImageLabel;
    std::unique_ptr<Drawable> image;
};