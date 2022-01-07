/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "stk/DelayL.h"
#include "filterCalc/FilterCalc.h"
#include "stk/BiQuad.h"
#include "basicLFO/basicLFO.h"

//==============================================================================
/**
*/
class delazedAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    delazedAudioProcessor();
    ~delazedAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //Add a public pointer for each user parameter
    AudioParameterFloat* about;
    AudioParameterFloat* delayTimeLUParam;
    AudioParameterFloat* delayTimeRUParam;
    AudioParameterFloat* oGainUParam;
    AudioParameterFloat* iGainUParam;
    AudioParameterFloat* dryWetUParam;
    AudioParameterFloat* fbUParam;
    AudioParameterFloat* link;
    AudioParameterFloat* shimmerUParam;
    AudioParameterFloat* darken;
    AudioParameterFloat* rate;
    AudioParameterFloat* chorusFbUParam;
    AudioParameterFloat* depthUParam;
    AudioParameterFloat* chorusDryWetUParam;

private:
    
    void calcAlgorithmParams();
    
    // gain params
    float oGainAParam; // calculation of out gain parameter
    float iGainAParam; // calculation of gry gain parameter
    
    // delay params
    float dryWetAParam; // dry and wet knob
    float dGain; // variable to hold dry gain value
    float wGain; // variable to hold wet gain value
    float fbAParam; // delay.nextOut() * fbGain
    float fbGL, fbGR; // variables to hold left and right feedback
    
    // special params
    float shimmerAParam;
    float shimmerBParam;
    float chorusFilterGain;
    float softClip(float sample); // handles overload from two feedbacks
    float softClipThreshold = 2.f / 3.f;
    float darkenParam;
    
    // chorus params
    float chorusFbAParam;
    float depthSamps;
    float chorusDryWetParam;
    float chorusDry;
    float chorusWet;
    float chorusSampsL, chorusSampsR;
    float chorusMsecL, chorusMsecR;
    
    // calc params
    float fs; // need sample rate ro calculate delay
    float calcDelaySampsFromMsec(float msec); // function to be used for conversion
    float leftDelayMsec, rightDelayMsec;
    float delaySampsL, delaySampsR; // variable to store our delay in samples
    int maxDelayInSamps; // max amount of memory to store delay
    
    // objects
    stk::DelayL delayL, delayR, chorusDelayL, chorusDelayR; // delay objects
    
    stk::BiQuad filterL, filterR,
                lowFilterL, lowFilterR,
                chFilterL, chFilterR,
                mainFilterL, mainFilterR; // filter objects for high shelf
    
    basicLFO LFOL, LFOR; // LFO objects for chorus rate
    
    // interpolation stuff
    float curDelayL, prevDelayL,
            curDelayR, prevDelayR,
            curDepth, prevDepth,
            curChorusL, curChorusR,
            prevChorusL, prevChorusR;
    float linInterpolation(float start, float end, float fract); // linear interpolation function
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (delazedAudioProcessor)
};
