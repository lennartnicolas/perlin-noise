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
        g.setColour(juce::Colours::white);
        for(int x = 0; x < getWidth(); ++x){
            int sampleIndex = x % _buffer.getNumSamples();
            float y = (1.f - _buffer.getSample(0, sampleIndex)) * getHeight();
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

private:
    const juce::AudioSampleBuffer& _buffer;
    std::vector<juce::Point<float> > points;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrawWavetable)
};
