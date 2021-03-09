/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PerlinNoiseAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PerlinNoiseAudioProcessorEditor (PerlinNoiseAudioProcessor&);
    ~PerlinNoiseAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    PerlinNoiseAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PerlinNoiseAudioProcessorEditor)
};
