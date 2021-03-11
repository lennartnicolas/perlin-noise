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
    WaveOsc(const juce::AudioSampleBuffer& wavetableToUse);
    void setFrequency(float frequency, float sampleRate);
    float getNextSample() noexcept;
    
private:
    const juce::AudioSampleBuffer& wavetable;
    const int tableSize;
    float currentIndex = 0.0f, tableDelta = 0.0f;
};
