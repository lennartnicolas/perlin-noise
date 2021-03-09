/*
  ==============================================================================

    PerlinWave.h
    Created: 8 Mar 2021 8:34:13pm
    Author:  Lennart Krebs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PerlinWave{
    
public:
    PerlinWave(const juce::AudioSampleBuffer& audioBuffer);
    void setFrequency(float frequency, float sampleRate);
    float getNextSample() noexcept;
        
private:
    const juce::AudioSampleBuffer& _waveTable;
    const int _tableSize;
    float _currentIndex = 0.f;
    float _tableDelta   = 0.f;
};
