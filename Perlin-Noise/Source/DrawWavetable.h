/*
  ==============================================================================

    DrawWavetable.h
    Created: 11 Mar 2021 2:15:39pm
    Author:  Lennart Krebs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DrawWavetable  : public juce::Component
{
public:
    DrawWavetable(const juce::AudioSampleBuffer& waveTableToDraw) : _buffer(waveTableToDraw)
    {
    }

    ~DrawWavetable() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        points.clear();
        g.fillAll(juce::Colours::grey);
        g.setColour(juce::Colours::white);
   
        for(int x = 0; x < getWidth(); ++x){
            float y = getBufferSample() * getHeight();
            points.push_back(juce::Point<float> (x, y));
        }
        
        for(int i = 0; i < points.size() - 1; ++i){
            juce::Line<float> line(points[i], points[i + 1]);
            g.drawLine(line, 2.0f);
        }
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }
    
    float getBufferSample(){
        
        tableDelta = (float) (_buffer.getNumSamples() - 1) / (float) getWidth();

        auto index0 = (unsigned int) currentIndex;
        auto index1 = index0 + 1;
        
        auto frac = currentIndex - (float) index0;
        
        auto* table = _buffer.getReadPointer(0);
        auto value0 = table[index0];
        auto value1 = table[index1];
        
        auto currentSample = value0 + frac * (value1 - value0);

        if ((currentIndex += tableDelta) > (float) (_buffer.getNumSamples() - 1)){
            currentIndex -= (float) (_buffer.getNumSamples() - 1);
        }

        return currentSample;
    }
    
    

private:
    const juce::AudioSampleBuffer& _buffer;
    float currentIndex = 0.0f, tableDelta = 0.0f;
    std::vector<juce::Point<float> > points;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrawWavetable)
};
