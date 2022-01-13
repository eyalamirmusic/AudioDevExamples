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
    explicit SVGDisplayer(const File& fileToLoad, RectanglePlacement& placementToUse)
        : placement(placementToUse)
    {
        image = Drawable::createFromImageFile(fileToLoad);

        if (image == nullptr)
            addAndMakeVisible(invalidImageLabel);
    }

    void paint(Graphics& g) override
    {
        if (image != nullptr)
            image->drawWithin(g, getLocalBounds().toFloat(), placement, 1.f);
    }

    void resized() override
    {
        if (image == nullptr)
            invalidImageLabel.setBounds(getLocalBounds());
    }

    InvalidImageLabel invalidImageLabel;
    std::unique_ptr<Drawable> image;
    RectanglePlacement& placement;
};