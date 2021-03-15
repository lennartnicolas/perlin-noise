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
    juce::Slider _levelSlider;
    juce::Slider _interpolate;

    
    juce::TextButton _changeTableButton;


    DrawWavetable* _drawWave;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> _freqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> _levelSliderAttachment;

    PNAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PNAudioProcessorEditor)
};
