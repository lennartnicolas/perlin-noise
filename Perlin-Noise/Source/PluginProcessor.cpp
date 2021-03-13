/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PNAudioProcessor::PNAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), _valueTree(*this, nullptr, "Parameters", createParameters())
#endif
{
    _frequencyParameter       = _valueTree.getRawParameterValue("FREQUENCY");
    _levelParameter           = _valueTree.getRawParameterValue("LEVEL");
    createWaveTable();
    _wOsc = new WaveOsc(_waveTable);
}

PNAudioProcessor::~PNAudioProcessor()
{
    delete _wOsc;
}

//==============================================================================
const juce::String PNAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PNAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PNAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PNAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PNAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PNAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PNAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PNAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PNAudioProcessor::getProgramName (int index)
{
    return {};
}

void PNAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PNAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    _wOsc->setFrequency(*_frequencyParameter, sampleRate);
}

void PNAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PNAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PNAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    

    targetLevel = *_levelParameter;
    _wOsc->setFrequency(*_frequencyParameter, getSampleRate());

    auto* leftBuffer = buffer.getWritePointer(0);
    auto* rightBuffer = buffer.getWritePointer(1);
    
    for(int i = 0; i < buffer.getNumSamples(); ++i)
    {
        auto sample = _wOsc->getNextSample();
        leftBuffer[i] = sample;
        rightBuffer[i] = sample;
    }
    
    auto localTargetLevel = targetLevel;
    for(int channel = 0; channel < totalNumOutputChannels ; ++channel)
    {
        buffer.applyGainRamp(channel, buffer.getSample(channel, 0), buffer.getNumSamples(), currentLevel, localTargetLevel);
    }
    currentLevel = targetLevel;
}

//==============================================================================
bool PNAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PNAudioProcessor::createEditor()
{
    return new PNAudioProcessorEditor (*this);
}

//==============================================================================
void PNAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PNAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PNAudioProcessor();
}


//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout PNAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter> > params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FREQUENCY", "Frequency", 20.0f, 2000.0f, 440.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LEVEL", "Level", 0.0, 1.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("BUTTON", "Button", false));
    return {params.begin(), params.end()};
}


juce::AudioProcessorValueTreeState* PNAudioProcessor::getValueTree()
{
    return &_valueTree;
}

void PNAudioProcessor::createWaveTable()
{
    _waveTable.setSize(1, (int) _waveTableSize + 1);
    _waveTable.clear();
    
    auto* samples = _waveTable.getWritePointer(0);
    
    float x = 0.01f;
    float increment = 0.01f;

    for(unsigned int i = 0; i <= _waveTableSize; ++i){
        auto sample = _pnNoise.noise(x);
        samples[i] = sample;
        x += increment;
    }
}

void PNAudioProcessor::updateWaveTable()
{
    _waveTable.clear();
    _waveTable.setSize(1, (int) _waveTableSize + 1);
    
    auto& random = juce::Random::getSystemRandom();
    _pnNoise.noiseSeed(std::abs(random.nextInt()));
    
    auto* samples = _waveTable.getWritePointer(0);
    
    float x = 0.01f;
    float increment = 0.01f;

    for(unsigned int i = 0; i <= _waveTableSize; ++i){
        auto sample = _pnNoise.noise(x);
        samples[i] = sample;
        x += increment;
    }
    _wOsc->setWavetable(_waveTable);
}


juce::AudioSampleBuffer& PNAudioProcessor::getWaveTable()
{
    return _waveTable;
}
