/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "math.h"

//==============================================================================
delazedAudioProcessor::delazedAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter (about = new AudioParameterFloat ("about", // parameterID
                                                  "About", // parameter name
                                                  NormalisableRange<float> (0.0f, 1.0f), //parameter range
                                                  1.0f)); // default value
    
    addParameter (delayTimeLUParam = new AudioParameterFloat ("delayTimeL", // parameterID
                                                              "L Delay Time", // parameter name
                                                              NormalisableRange<float> (0.0, 2000.0), //parameter range
                                                              300.0f)); // default value
    
    addParameter (delayTimeRUParam = new AudioParameterFloat ("delayTimeR", // parameterID
                                                              "R Delay Time", // parameter name
                                                              NormalisableRange<float> (0.0, 2000.0), //parameter range
                                                              300.0f)); // default value
    
    addParameter (dryWetUParam = new AudioParameterFloat ("dryWet", // parameterID
                                                         "Delay Mix", // parameter name
                                                         NormalisableRange<float> (0.0, 100.0f), //parameter range
                                                         30.0f)); // default value
    
    addParameter (oGainUParam = new AudioParameterFloat ("outGain", // parameterID
                                                             "Output Gain", // parameter name
                                                             NormalisableRange<float> (-12.0, 6.0f), //parameter range
                                                             0.0f)); // default value
    
    addParameter (iGainUParam = new AudioParameterFloat ("inGain", // parameterID
                                                         "Input Gain", // parameter name
                                                         NormalisableRange<float> (-12.0, 6.0f), //parameter range
                                                         0.0f)); // default value
    
    addParameter (fbUParam = new AudioParameterFloat ("feedback", // parameterID
                                                         "Delay Feedback", // parameter name
                                                         NormalisableRange<float> (0.0, 101.0f), //parameter range
                                                         0.0f)); // default value
    
    addParameter (link = new AudioParameterFloat ("link", // parameterID
                                                  "Link", // parameter name
                                                  NormalisableRange<float> (0.0f, 1.0f), //parameter range
                                                  1.0f)); // default value
    
    addParameter (shimmerUParam = new AudioParameterFloat ("shimmer", // parameterID
                                                         "Shimmer", // parameter name
                                                         NormalisableRange<float> (0.0, 100.0f), //parameter range
                                                         0.0f)); // default value
    
    addParameter (darken = new AudioParameterFloat ("darken", // parameterID
                                                           "Darken", // parameter name
                                                           NormalisableRange<float> (0.0, 100.0f), //parameter range
                                                           0.0f)); // default value
    
    addParameter (rate = new AudioParameterFloat ("rate", // parameterID
                                                   "Rate", // parameter name
                                                   NormalisableRange<float> (0.0, 20.0f), //parameter range
                                                   0.05f)); // default value
    
    addParameter (chorusFbUParam = new AudioParameterFloat ("ChorusFeedback", // parameterID
                                                  "Chorus Feedback", // parameter name
                                                  NormalisableRange<float> (0.0, 100.0f), //parameter range
                                                  0.0f)); // default value
    
    addParameter (depthUParam = new AudioParameterFloat ("depth", // parameterID
                                                            "Depth", // parameter name
                                                            NormalisableRange<float> (0.0, 100.0f), //parameter range
                                                            50.0f)); // default value
    
    addParameter (chorusDryWetUParam = new AudioParameterFloat ("ChorusMix", // parameterID
                                                         "Chorus Mix", // parameter name
                                                         NormalisableRange<float> (0.0, 100.0f), //parameter range
                                                         30.0f)); // default value

}

delazedAudioProcessor::~delazedAudioProcessor()
{
}

//==============================================================================
const String delazedAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool delazedAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool delazedAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool delazedAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double delazedAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int delazedAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int delazedAudioProcessor::getCurrentProgram()
{
    return 0;
}

void delazedAudioProcessor::setCurrentProgram (int index)
{
}

const String delazedAudioProcessor::getProgramName (int index)
{
    return {};
}

void delazedAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void delazedAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    fs = sampleRate; // samples per second
    leftDelayMsec = *delayTimeLUParam;
    rightDelayMsec = *delayTimeRUParam;

    // initialize cur/prev params
    curDelayL = delaySampsL;
    curDelayR = delaySampsR;
    prevDelayL = curDelayL;
    prevDelayR = curDelayR;
    curDepth = depthSamps;
    prevDepth = curDepth;
    curChorusL = chorusSampsL;
    curChorusR = chorusSampsR;
    prevChorusL = curChorusL;
    prevChorusR = curChorusR;
    
    // initialize maximum delay based on max delay time desired
    maxDelayInSamps = fs * 2; // 2 seconds (or 2000 ms) of maximum delay
    delayL.setMaximumDelay(maxDelayInSamps); // initializing delay
    delayR.setMaximumDelay(maxDelayInSamps); // initializing delay
    chorusDelayL.setMaximumDelay(maxDelayInSamps);
    chorusDelayR.setMaximumDelay(maxDelayInSamps);
    
    delayL.setDelay(maxDelayInSamps);
    delayR.setDelay(maxDelayInSamps);
    chorusDelayL.setDelay(maxDelayInSamps);
    chorusDelayR.setDelay(maxDelayInSamps);
    
    // LFO stuff
    LFOL.resetPhase();
    LFOR.resetPhase();
    LFOL.setFreq(*rate, fs);
    LFOR.setFreq(*rate, fs);
    
}

void delazedAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    
    // clear the delay line here to avoid leftover delay that creates pops
    // when starting or stopping playback
    for (int i = 0; i < maxDelayInSamps; i++) {
        delayL.tick(0.0); // tick through each sample and set delay to zero
        delayR.tick(0.0);
    }
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool delazedAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void delazedAudioProcessor::calcAlgorithmParams()
{
    // grab UI to alg variable
    leftDelayMsec = *delayTimeLUParam;
    rightDelayMsec = *delayTimeRUParam;
    
    if (*link == 0) {
        leftDelayMsec = rightDelayMsec; // link parameters when button is pressed
    } else {
        leftDelayMsec = *delayTimeLUParam;
        rightDelayMsec = *delayTimeRUParam;
    }

    // convert delay from ms to samples
    delaySampsL = calcDelaySampsFromMsec(leftDelayMsec); // converted to samples
    delaySampsR = calcDelaySampsFromMsec(rightDelayMsec); // converted to samples
    // chorus ms from user delay ms
    chorusMsecL = (leftDelayMsec * 0.015) + 10; // convert 0-2000 to 10-40 ms
    chorusMsecR = (rightDelayMsec * 0.015) + 10; // convert 0-2000 to 10-40 ms
    chorusSampsL = calcDelaySampsFromMsec(chorusMsecL);
    chorusSampsR = calcDelaySampsFromMsec(chorusMsecR);
    
    // set current delay
    curDelayL = delaySampsL;
    curDelayR = delaySampsR;
    curChorusL = chorusSampsL;
    curChorusR = chorusSampsR;
    
    depthSamps = calcDelaySampsFromMsec((*depthUParam) * 0.1); // convert depth from 0-100% to 0-10 ms to samples
    curDepth = depthSamps; // set current depth
    
    // LFO stuff
    LFOL.setFreq(*rate, fs);
    LFOR.setFreq(*rate, fs);
    
    fbAParam = *fbUParam * 0.01; // convert user % to 0 - 0.99
    chorusFbAParam = *chorusFbUParam * 0.01;
    
    // delay mix
    dryWetAParam = *dryWetUParam * 0.01; // convert user % to 0 - 1
    dGain = 1 - dryWetAParam; // if mix knob is 100%, dry = 0
    wGain = dryWetAParam; // if mix knob is 100%, wet = 1
    // chorus mix
    chorusDryWetParam = *chorusDryWetUParam * 0.01;
    chorusDry = 1 - chorusDryWetParam;
    chorusWet = chorusDryWetParam;
    
    // filter stuff
    float shelfCoeffs[5];
    float lowShelfCoeffs[5];
    float chorusCoeffs[5];
    float mainCoeffs[5];
    
    // user parameter conversions / thresholds for filters
    //shimmerAParam = (*shimmerUParam * 0.005); // 0 - 100% to 0 to +0.5 for gain dB
    shimmerBParam = (*shimmerUParam * -0.06); // 0 - 100% to 0 to -6 for reduction dB
    if (fbAParam >= 1.0) { // 100% or greater feedback gets entirely attenuated
        shimmerAParam = (*shimmerUParam * -0.005); // -0.5dB max
    }
    else if (fbAParam >= 0.92) { // no attenuation for fb 92% - 99.9%, no gain
        shimmerAParam = (*shimmerUParam * 0.0);
    } else { // increase highs on fb if below 92%
        shimmerAParam = (*shimmerUParam * 0.005); // 0 - 100% to 0 to +0.5 for gain dB
    }
    if (chorusFbAParam < 0.8) { // do nothing with filter until chorusFB > 80%
        chorusFilterGain = 0.0;
    } else {
        chorusFilterGain = (*chorusFbUParam - 80) * -0.15; // 90 - 100% to 0 to -3 for reduction dB
    }
    darkenParam = *darken * -0.09; // 0 - 100% to 0 to -9 dB
    
    // set high shelf frequency center at 1.2kHz
    FilterCalc::calcCoeffsHighShelf(shelfCoeffs, 1200.0, shimmerAParam, fs);
    filterL.setCoefficients(shelfCoeffs[0],shelfCoeffs[1],shelfCoeffs[2],shelfCoeffs[3],shelfCoeffs[4]);
    filterR.setCoefficients(shelfCoeffs[0],shelfCoeffs[1],shelfCoeffs[2],shelfCoeffs[3],shelfCoeffs[4]);
    // set low shelf fc at 1.2kHz, user reduces low shelf gain while increasing high shelf gain
    FilterCalc::calcCoeffsLowShelf(lowShelfCoeffs, 1200.0, shimmerBParam, fs);
    lowFilterL.setCoefficients(lowShelfCoeffs[0],lowShelfCoeffs[1],lowShelfCoeffs[2],lowShelfCoeffs[3],lowShelfCoeffs[4]);
    lowFilterR.setCoefficients(lowShelfCoeffs[0],lowShelfCoeffs[1],lowShelfCoeffs[2],lowShelfCoeffs[3],lowShelfCoeffs[4]);
    // set filter for chorus feedback center at 900Hz, increase in feedback = decrease in gain
    FilterCalc::calcCoeffsLowShelf(chorusCoeffs, 900.0, chorusFilterGain, fs);
    chFilterL.setCoefficients(chorusCoeffs[0],chorusCoeffs[1],chorusCoeffs[2],chorusCoeffs[3],chorusCoeffs[4]);
    chFilterR.setCoefficients(chorusCoeffs[0],chorusCoeffs[1],chorusCoeffs[2],chorusCoeffs[3],chorusCoeffs[4]);
    // high self on overall output, allow dB decrease after 300Hz
    FilterCalc::calcCoeffsHighShelf(mainCoeffs, 300.0, darkenParam, fs);
    mainFilterL.setCoefficients(mainCoeffs[0],mainCoeffs[1],mainCoeffs[2],mainCoeffs[3],mainCoeffs[4]);
    mainFilterR.setCoefficients(mainCoeffs[0],mainCoeffs[1],mainCoeffs[2],mainCoeffs[3],mainCoeffs[4]);
    
    // input and output gains using dB
    oGainAParam = pow(10.0,(*oGainUParam)/20.0); //convert user out dB gain to linear gain
    iGainAParam = pow(10.0,(*iGainUParam)/20.0); //convert user in dB gain to linear gain

}

//linear interpolation
float delazedAudioProcessor::linInterpolation(float start, float end, float fract) {
    return start + ( fract * (end - start)); //a - fract * ( b - a )
}

float delazedAudioProcessor::calcDelaySampsFromMsec (float msec) {
    return fs * (msec / 1000);
}

float delazedAudioProcessor::softClip(float sample)
{
    if (sample < -1.f) {
        return -softClipThreshold;
    }
    else if (sample > 1.f) {
        return softClipThreshold;
    }
    else {
        return sample - ((sample * sample * sample) / 3.f);
    }
}

void delazedAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    calcAlgorithmParams();
    const int numSamps = buffer.getNumSamples();

    float delOutL, delOutR;
    float tmpL, tmpR;
    float tmpChorL, tmpChorR;
    float tmp2L, tmp2R;
    float* leftChannel;
    float* rightChannel;
    float fract;
    float lfoAmpL, lfoAmpR;
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        if (channel == 0) { // left side
            leftChannel = channelData;
        } else if (channel == 1) { // right side
            rightChannel = channelData;
        }
        
        if (totalNumInputChannels < 2) { // check for mono
            rightChannel = leftChannel;
        }
    }
        // ..do something to the data...
            for (int i = 0; i < numSamps; ++i)
            {
                fract = ((float) i / (float) numSamps);
                
                if (curDelayL != prevDelayL) {
                    delaySampsL = linInterpolation(prevDelayL, curDelayL, fract);
                    chorusSampsL = linInterpolation(prevChorusL, curChorusL, fract);
                }
                
                if (curDelayR != prevDelayR) {
                    delaySampsR = linInterpolation(prevDelayR, curDelayR, fract);
                    chorusSampsR = linInterpolation(prevChorusR, curChorusR, fract);
                }
                
                if (curDepth != prevDepth) {
                    depthSamps = linInterpolation(prevDepth, curDepth, fract);
                }
                    //CHORUS process
                    lfoAmpL = 0.5 * (1 + LFOL.tick());
                    lfoAmpR = 0.5 * (1 + LFOR.tick());
                
                    tmpChorL = chorusSampsL + (depthSamps * lfoAmpL);
                    tmpChorR = chorusSampsR + (depthSamps * lfoAmpR);
                    chorusDelayL.setDelay(tmpChorL);
                    chorusDelayR.setDelay(tmpChorR);
                
                    tmp2L = (chorusDelayL.nextOut() * chorusFbAParam);
                    tmp2L = chFilterL.tick(tmp2L);
                    tmp2R = (chorusDelayR.nextOut() * chorusFbAParam);
                    tmp2R = chFilterR.tick(tmp2R);
                
                    leftChannel[i] *= iGainAParam;
                    // leftIn * dry + ((delayed leftIn + right fbck) * wet) * invert
                   leftChannel[i] = (leftChannel[i] * chorusDry) +
                                    ((chorusDelayL.tick(leftChannel[i] + tmp2R)) * chorusWet);
                    rightChannel[i] *= iGainAParam;
                   // rightIn * dry + ((delayed rightIn + left fbck) * wet) * invert
                    rightChannel[i] = (rightChannel[i] * chorusDry) +
                                    ((chorusDelayR.tick(rightChannel[i] + tmp2L)) * chorusWet);

                    // DELAY process
                    delayL.setDelay(delaySampsL);
                    delayR.setDelay(delaySampsR);
                    // filtered feedback (shimmer)
                    tmpL = lowFilterL.tick((delayL.nextOut() * fbAParam));
                    tmpL = filterL.tick(tmpL);
                    tmpR = lowFilterR.tick((delayR.nextOut() * fbAParam));
                    tmpR = filterL.tick(tmpR);

                    delOutL = delayL.tick(leftChannel[i] + tmpR); // dly in + R channel fb
                    leftChannel[i] = (leftChannel[i] * dGain) + (wGain * delOutL); // dry signal + wet signal
                
                    delOutR = delayR.tick(rightChannel[i] + tmpL); // dly in + L channel fb
                    rightChannel[i] = (rightChannel[i] * dGain) + (wGain * delOutR); // dry signal + wet signal
                
                    // prevent signal overload
                    if (chorusFbAParam >= 0.85) {
                        leftChannel[i] = softClip(leftChannel[i]);
                        rightChannel[i] = softClip(rightChannel[i]);
                    }
                    else if (fbAParam >= 0.99) {
                        leftChannel[i] = softClip(leftChannel[i]);
                        rightChannel[i] = softClip(rightChannel[i]);
                    }
                    else if (chorusFbAParam + fbAParam >= 1.0) {
                        leftChannel[i] = softClip(leftChannel[i]);
                        rightChannel[i] = softClip(rightChannel[i]);
                    }
                
                    // push entire signal through high shelf (darken)
                    leftChannel[i] = mainFilterL.tick(leftChannel[i]);
                    rightChannel[i] = mainFilterR.tick(rightChannel[i]);
                    // allow dB inc/dec after entire line
                    leftChannel[i] *= oGainAParam;
                    rightChannel[i] *= oGainAParam;
            }
        // set previous parameters here
        prevDelayL = curDelayL;
        prevDelayR = curDelayR;
        prevDepth = curDepth;
        prevChorusL = curChorusL;
        prevChorusR = curChorusR;
    }

//==============================================================================
bool delazedAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* delazedAudioProcessor::createEditor()
{
    return new delazedAudioProcessorEditor (*this);
}

//==============================================================================
void delazedAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    //for multiple vars.
    std::unique_ptr<XmlElement> xml (new XmlElement ("DelayLParams"));
    xml->setAttribute ("delayTimeL", (double) *delayTimeLUParam);
    copyXmlToBinary (*xml, destData);
    
    (new XmlElement ("DelayRParams"));
    xml->setAttribute ("delayTimeR", (double) *delayTimeRUParam);
    copyXmlToBinary (*xml, destData);
    
    (new XmlElement ("outGain"));
    xml->setAttribute ("outGain", (double) *oGainUParam);
    copyXmlToBinary (*xml, destData);
    
    (new XmlElement ("inGain"));
    xml->setAttribute ("inGain", (double) *iGainUParam);
    copyXmlToBinary (*xml, destData);
    
    (new XmlElement ("dryWet"));
    xml->setAttribute ("dryWet", (double) *dryWetUParam);
    copyXmlToBinary (*xml, destData);
    
    (new XmlElement ("feedback"));
    xml->setAttribute ("feedback", (double) *fbUParam);
    copyXmlToBinary (*xml, destData);
    
    (new XmlElement ("shimmer"));
    xml->setAttribute ("shimmer", (double) *shimmerUParam);
    copyXmlToBinary (*xml, destData);
    
    (new XmlElement ("darken"));
    xml->setAttribute ("darken", (double) *darken);
    copyXmlToBinary (*xml, destData);
    
    (new XmlElement ("depth"));
    xml->setAttribute ("depth", (double) *depthUParam);
    copyXmlToBinary (*xml, destData);
    
    (new XmlElement ("rate"));
    xml->setAttribute ("rate", (double) *rate);
    copyXmlToBinary (*xml, destData);
    
    (new XmlElement ("chorusFeedback"));
    xml->setAttribute ("chorusFeedback", (double) *chorusFbUParam);
    copyXmlToBinary (*xml, destData);
    
    (new XmlElement ("chorusMix"));
    xml->setAttribute ("chorusMix", (double) *chorusDryWetUParam);
    copyXmlToBinary (*xml, destData);
    
}

void delazedAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    //for multiple vars
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName ("DelayLParams"))
            *delayTimeLUParam = xmlState->getDoubleAttribute ("delayTimeL", 300.0);
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName ("DelayRParams"))
            *delayTimeRUParam = xmlState->getDoubleAttribute ("delayTimeR", 300.0);
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName ("outGain"))
            *oGainUParam = xmlState->getDoubleAttribute ("outGain", 0.0);
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName ("inGain"))
            *iGainUParam = xmlState->getDoubleAttribute ("inGain", 0.0);
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName ("dryWet"))
            *dryWetUParam = xmlState->getDoubleAttribute ("dryWet", 30.0);
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName ("feedback"))
            *fbUParam = xmlState->getDoubleAttribute ("feedback", 0.0);
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName ("shimmer"))
            *shimmerUParam = xmlState->getDoubleAttribute ("shimmer", 0.0);
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName ("darken"))
            *darken = xmlState->getDoubleAttribute ("darken", 0.0);
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName ("depth"))
            *depthUParam = xmlState->getDoubleAttribute ("depth", 50.0);
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName ("rate"))
            *rate = xmlState->getDoubleAttribute ("rate", 0.05);
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName ("chorusFeedback"))
            *chorusFbUParam = xmlState->getDoubleAttribute ("chorusFeedback", 0.0);
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName ("chorusMix"))
            *chorusDryWetUParam = xmlState->getDoubleAttribute ("chorusMix", 30.0);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new delazedAudioProcessor();
}
