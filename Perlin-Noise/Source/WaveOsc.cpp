/*
  ==============================================================================

    WaveOsc.cpp
    Created: 11 Mar 2021 1:24:06pm
    Author:  Lennart Krebs

  ==============================================================================
*/

#include "WaveOsc.h"

WaveOsc::WaveOsc(const juce::AudioSampleBuffer& wavetableToUse):  wavetable(wavetableToUse),
tableSize(wavetable.getNumSamples() - 1)
{
    jassert (wavetable.getNumChannels() == 1);
}

void WaveOsc::setFrequency(float frequency, float sampleRate)
{
    tableDelta = frequency * ((float) tableSize / sampleRate);
}

float WaveOsc::getNextSample() noexcept
{
    auto index0 = (unsigned int) currentIndex;
    auto index1 = index0 + 1;

    auto frac = currentIndex - (float) index0;

    auto* table = wavetable.getReadPointer (0);
    auto value0 = table[index0];
    auto value1 = table[index1];

    auto currentSample = value0 + frac * (value1 - value0);

    if ((currentIndex += tableDelta) > (float) tableSize)
        currentIndex -= (float) tableSize;

    return currentSample;
}
