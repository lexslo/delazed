/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class delazedAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Slider::Listener,
                                        public Button::Listener,
                                        public Timer
{
public:
    delazedAudioProcessorEditor (delazedAudioProcessor&);
    ~delazedAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider*) override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void timerCallback() override;

private:
    Slider delayTimeL;
    Label dtlLabel;
    
    Slider delayTimeR;
    Label dtrLabel;
    
    Slider outGain;
    Label oGLabel;
    
    Slider inGain;
    Label iGLabel;
    
    Slider dryWet;
    Label dwLabel;
    
    Slider fb;
    Label fbLabel;
    
    Slider shimmer;
    Label shimLabel;
    
    Slider darkenSlider;
    Label darkenLabel;
    
    Slider depth;
    Label depLabel;
    
    Slider rateSlider;
    Label rateLabel;
    
    Slider chorusFb;
    Label chorusFbLabel;
    
    Slider chorusDw;
    Label chorusDwLabel;
    
    TextButton linkButton;
    TextButton about;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    delazedAudioProcessor& processor;
    
    juce::Image MyBackground;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (delazedAudioProcessorEditor)
};
