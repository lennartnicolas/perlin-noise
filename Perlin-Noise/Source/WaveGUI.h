/*
  ==============================================================================

    WaveGUI.h
    Created: 9 Mar 2021 6:15:36pm
    Author:  Lennart Krebs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PerlinNoise.h"
#include "PerlinWave.h"
#include <iostream>
#include <vector>

//==============================================================================
/*
*/
class WaveGUI  : public juce::Component
{
public:
    WaveGUI();
    ~WaveGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void createWavetable();
    juce::AudioSampleBuffer* getWaveTable();
    unsigned int getTableSize();


private:
    juce::AudioSampleBuffer _pnTable;
    unsigned int _pnTableSize;
    float _x = 0.f;
    PerlinNoise _pnNoise;
    std::vector<juce::Point<float> > points;
    float increment = 0.01f;
    
    juce::TextButton button;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveGUI)
};
