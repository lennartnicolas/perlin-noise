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
    addAndMakeVisible(_incrementSlider);
    addAndMakeVisible(_interpolateSineSlider);
    addAndMakeVisible(_freqLabel);
    addAndMakeVisible(_levelLabel);
    addAndMakeVisible(_incrementLabel);
    addAndMakeVisible(_flattenLabel);
    
    _freqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    _freqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    _freqSlider.setSize(50, 200);
    _freqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(*audioProcessor.getValueTree(), "FREQUENCY", _freqSlider);
    
    _freqLabel.setText("Frequency", juce::dontSendNotification);
    _freqLabel.setJustificationType(juce::Justification::centred);
    
    _levelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    _freqSlider.setSize(50, 200);
    _levelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    _levelSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(*audioProcessor.getValueTree(), "LEVEL" , _levelSlider);
    
    _levelLabel.setText("Level", juce::dontSendNotification);
    _levelLabel.setJustificationType(juce::Justification::centred);
    
    _incrementSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    _incrementSlider.setSize(50, 200);
    _incrementSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    _incrementSlider.setRange(juce::Range<double>(0.01, 0.35), 0.001);
    _incrementSlider.setValue(0.01f);
    _incrementSlider.onValueChange = [this, &p](){
        auto& random = juce::Random::getSystemRandom();
        p.updateWaveTable(_incrementSlider.getValue(),random.nextInt());
        _interpolateSineSlider.setValue(0.f);
        _drawWave->setWaveTable(p.getWaveTable());
        _drawWave->repaint();
    };

    _incrementLabel.setText("Perlin Wave", juce::dontSendNotification);
    _incrementLabel.setJustificationType(juce::Justification::centred);
    
    _interpolateSineSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    _interpolateSineSlider.setSize(50, 200);
    _interpolateSineSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    _interpolateSineSlider.setRange(juce::Range<double>(0.00, 1.0), 0.01);
    _interpolateSineSlider.setValue(0.0f);
    _interpolateSineSlider.onValueChange = [this, &p](){
        p.interpolateWaveTable(_interpolateSineSlider.getValue());
        _drawWave->setWaveTable(p.getWaveTable());
        _drawWave->repaint();
    };
    
    _flattenLabel.setText("Flatten", juce::dontSendNotification);
    _flattenLabel.setJustificationType(juce::Justification::centred);

    setSize (600, 500);
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
    
    auto width = (getWidth()/5);
    auto height = getHeight() - getHeight()/2 + 20;
    auto centre = _freqSlider.getWidth();
    auto sliderHeight = 180;
    
    _freqSlider.setBounds(width * 1 - centre, height, 100, sliderHeight);
    _levelSlider.setBounds(width * 2 - centre, height, 100, sliderHeight);
    _incrementSlider.setBounds(width * 3 - centre, height, 100, sliderHeight);
    _interpolateSineSlider.setBounds(width * 4 - centre, height, 100, sliderHeight);
    
    _freqLabel.setBounds(_freqSlider.getX(), _freqSlider.getBottom() + 15, 100, 20);
    _levelLabel.setBounds(_levelSlider.getX(), _levelSlider.getBottom() + 15, 100, 20);
    _incrementLabel.setBounds(_incrementSlider.getX(), _incrementSlider.getBottom() + 15, 100, 20);
    _flattenLabel.setBounds(_interpolateSineSlider.getX(), _interpolateSineSlider.getBottom() + 15, 100, 20);
}
