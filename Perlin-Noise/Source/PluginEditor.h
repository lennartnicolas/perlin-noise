/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "DrawWavetable.h"

//==============================================================================
/**
*/
class PNAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PNAudioProcessorEditor (PNAudioProcessor&);
    ~PNAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider _freqSlider;
    DrawWavetable* _drawWave;

    PNAudioProcessor& audioProcessor;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> _freqSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PNAudioProcessorEditor)
};
