/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PerlinNoise.h"
#include "WaveOsc.h"

//==============================================================================
/**
*/
class PNAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    PNAudioProcessor();
    ~PNAudioProcessor() override;

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
    juce::AudioProcessorValueTreeState* getValueTree();
    void createWaveTable();
    void updateWaveTable();
    juce::AudioSampleBuffer& getWaveTable();

private:
    std::atomic<float>* _frequencyParameter = nullptr;
    std::atomic<float>* _levelParameter = nullptr;
    std::atomic<float>* _changeWavetableParameter = nullptr;

    float currentLevel = 1.0f;
    float targetLevel  = 0.1f;
    
    WaveOsc* _wOsc;
    juce::AudioSampleBuffer _waveTable;
    unsigned int _waveTableSize = 1 << 8;
    
    PerlinNoise _pnNoise;
    
    juce::AudioProcessorValueTreeState _valueTree;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PNAudioProcessor)
};
