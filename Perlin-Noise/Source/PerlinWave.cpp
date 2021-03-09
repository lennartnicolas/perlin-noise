/*
  ==============================================================================

    PerlinWave.cpp
    Created: 8 Mar 2021 8:34:13pm
    Author:  Lennart Krebs

  ==============================================================================
*/

#include "PerlinWave.h"

PerlinWave::PerlinWave(const juce::AudioSampleBuffer& wavetableToUse) : _waveTable(wavetableToUse), _tableSize(_waveTable.getNumSamples() - 1)
{
    jassert(_waveTable.getNumChannels() == 1);
}



void PerlinWave::setFrequency(float frequency, float sampleRate)
{
    _tableDelta = frequency * ((float) _tableSize / sampleRate);
}

float PerlinWave::getNextSample() noexcept
{
    auto index0 = (unsigned int) _currentIndex;
    auto index1 = index0 + 1;
    
    auto frac = _currentIndex - (float) index0;
    
    auto* table = _waveTable.getReadPointer(0);
    auto value0 = table[index0];
    auto value1 = table[index1];
    
    auto currentSample = value0 + frac * (value1 - value0);
    if((_currentIndex += _tableDelta) > (float) _tableSize){
        _currentIndex -= (float) _tableSize;
    }
    return currentSample;
    
}
