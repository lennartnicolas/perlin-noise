/*
  ==============================================================================

    WaveGUI.cpp
    Created: 9 Mar 2021 6:15:36pm
    Author:  Lennart Krebs

  ==============================================================================
*/

#include "WaveGUI.h"


//==============================================================================
WaveGUI::WaveGUI()
{
    button.setSize(120, 30);
    button.setButtonText("Change Waveform");
    
    button.onClick = [this](){
        repaint();
    };
    addAndMakeVisible(button);


}


WaveGUI::~WaveGUI()
{
}

void WaveGUI::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::grey);
    points.clear();
    _pnTableSize = (unsigned int)getWidth();
    
    createWavetable();
    
    g.setColour(juce::Colours::white);
    for(int x = 0; x < getWidth(); ++x){
        int sampleIndex = x % _pnTable.getNumSamples();
        float y = (1.f - _pnTable.getSample(0, sampleIndex)) * getHeight();
        points.push_back(juce::Point<float> (x, y));
    }
    
    for(int i = 0; i < points.size() - 1; ++i){
        juce::Line<float> line(points[i], points[i + 1]);
        g.drawLine(line, 2.0f);
    }

}

void WaveGUI::resized()
{
    button.setBounds(getWidth() - button.getWidth() - 10, getHeight() - button.getHeight() - 10, button.getWidth(), button.getHeight());
}

void WaveGUI::createWavetable()
{

    _pnTable.setSize(1, (int) _pnTableSize + 1);
    _pnTable.clear();
    
    auto* samples = _pnTable.getWritePointer(0);
    
    auto& random = juce::Random::getSystemRandom();
    _pnNoise.noiseSeed(random.nextInt());

    
    for(unsigned int i = 0; i < _pnTableSize; ++i){
        float sample = _pnNoise.noise(_x);
        samples[i] = sample;
        _x += increment;
    }
    
    samples[_pnTableSize] = samples[0];
}



juce::AudioSampleBuffer* WaveGUI::getWaveTable()
{
    return &_pnTable;
}

unsigned int WaveGUI::getTableSize()
{
    return _pnTableSize;
}
