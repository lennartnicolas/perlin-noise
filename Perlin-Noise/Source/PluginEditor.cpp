/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PerlinNoiseAudioProcessorEditor::PerlinNoiseAudioProcessorEditor (PerlinNoiseAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setSize (256, 256);
}

PerlinNoiseAudioProcessorEditor::~PerlinNoiseAudioProcessorEditor()
{
}

//==============================================================================
void PerlinNoiseAudioProcessorEditor::paint (juce::Graphics& g)
{

    for(int x = 0; x < getWidth(); x++){
        g.setColour(juce::Colours::white);
        int sampleIndex = x % audioProcessor.getWaveTable().getNumSamples();
        auto y = audioProcessor.getWaveTable().getSample(0, sampleIndex);
        g.drawEllipse(x, y * getWidth(), 2, 2, 1);
    }
}

void PerlinNoiseAudioProcessorEditor::resized()
{
    
}
