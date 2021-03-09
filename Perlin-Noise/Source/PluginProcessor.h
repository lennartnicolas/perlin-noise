/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once
#include "PerlinNoise.h"
#include "PerlinWave.h"

//==============================================================================
/**
*/
class PerlinNoiseAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    PerlinNoiseAudioProcessor();
    ~PerlinNoiseAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    void createWavetable();
    
    juce::AudioSampleBuffer getWaveTable(){
        return _pnTable;
    }
    

private:
    juce::AudioSampleBuffer _pnTable;
    PerlinNoise _pnNoise;
    float _x = 0.f;
    const unsigned int _pnTableSize = 1 << 7;
    PerlinWave* _waveTableOscillator;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PerlinNoiseAudioProcessor)
};
