/*
  ==============================================================================

    WaveOsc.h
    Created: 11 Mar 2021 1:24:06pm
    Author:  Lennart Krebs

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class WaveOsc
{
public:
    WaveOsc();
    WaveOsc(const juce::AudioSampleBuffer& wavetableToUse);
    void setFrequency(float frequency, float sampleRate);
    float getNextSample() noexcept;
    void setWavetable(const juce::AudioSampleBuffer& newWavetable);
    
private:
    juce::AudioSampleBuffer wavetable;
    const int tableSize;
    float currentIndex = 0.0f, tableDelta = 0.0f;
    float _level = 1.f;
};
