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
    addAndMakeVisible(_waveTableObject);
    setSize (700, 500);

}



PerlinNoiseAudioProcessorEditor::~PerlinNoiseAudioProcessorEditor()
{
}

//==============================================================================
void PerlinNoiseAudioProcessorEditor::paint (juce::Graphics& g)
{

}

void PerlinNoiseAudioProcessorEditor::resized()
{
    _waveTableObject.setBounds(0, 0, getWidth(), getHeight() / 2);
}
