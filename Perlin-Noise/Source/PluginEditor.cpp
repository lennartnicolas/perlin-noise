/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PNAudioProcessorEditor::PNAudioProcessorEditor (PNAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    _drawWave = new DrawWavetable(p.getWaveTable());
    addAndMakeVisible(_drawWave);
    addAndMakeVisible(_freqSlider);
    
    _freqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    _freqSlider.setName("Frequency");
    _freqSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    _freqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(*audioProcessor.getValueTree(), "FREQUENCY", _freqSlider);
    
    setSize (400, 300);
}

PNAudioProcessorEditor::~PNAudioProcessorEditor()
{
    delete _drawWave;
}

//==============================================================================
void PNAudioProcessorEditor::paint (juce::Graphics& g)
{

}

void PNAudioProcessorEditor::resized()
{
    
    _drawWave->setBounds(0, 0, getWidth(), getHeight()/2);
    _freqSlider.setBounds(getWidth()/2, getHeight()/2, 100, 100);
}
