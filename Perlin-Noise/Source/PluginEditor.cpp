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
    addAndMakeVisible(_levelSlider);
    addAndMakeVisible(_changeTableButton);
    addAndMakeVisible(_interpolate);
    
    _freqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    _freqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    _freqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(*audioProcessor.getValueTree(), "FREQUENCY", _freqSlider);
    
    _levelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    _levelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    _levelSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(*audioProcessor.getValueTree(), "LEVEL" , _levelSlider);
    
    _changeTableButton.setButtonText("Change Waveform");
    _changeTableButton.setClickingTogglesState(true);
    _changeTableButton.onClick = [this, &p](){
        auto& random = juce::Random::getSystemRandom();
        p.updateWaveTable(_interpolate.getValue(),random.nextInt());
        _drawWave->setWaveTable(p.getWaveTable());
        _drawWave->repaint();
    };
    
    _interpolate.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    _interpolate.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    _interpolate.setRange(juce::Range<double>(0.0, 1.0), 0.01);
    _interpolate.setValue(0.01f);
    

    
    setSize (700, 500);
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
    _drawWave->setBounds(0, 0, getWidth(), getHeight() / 2);
    _freqSlider.setBounds(getWidth()/2, getHeight()/2, 100, 100);
    _levelSlider.setBounds(getWidth()/2 , getHeight()/2 + 50
                           , 100, 100);
    _changeTableButton.setBounds(0, getHeight()/2, 100, 30);
    _interpolate.setBounds(100,getHeight()-getHeight()/4, 100, 100);
}
