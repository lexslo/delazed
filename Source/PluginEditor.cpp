/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
delazedAudioProcessorEditor::delazedAudioProcessorEditor (delazedAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    
    MyBackground = ImageCache::getFromMemory(BinaryData::delayBackground2_jpg, BinaryData::delayBackground2_jpgSize);
    
    // about
    addAndMakeVisible (&about);
    about.setButtonText ("?");
    about.addListener (this);
    about.setClickingTogglesState(true);
    
    // delay time L
    delayTimeL.setRange(0.0, 2000.0, 1.0);
    delayTimeL.setSliderStyle(Slider::RotaryVerticalDrag);
    delayTimeL.setTextValueSuffix("ms");
    delayTimeL.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 20);
    delayTimeL.addListener(this);
    addAndMakeVisible(delayTimeL);
    // label design
    dtlLabel.setText("Left", dontSendNotification);
    dtlLabel.attachToComponent(&delayTimeL, false);
    dtlLabel.setFont(Font(15.0));
    dtlLabel.setJustificationType(Justification::centredTop);
    addAndMakeVisible(dtlLabel);
    
    // delay time R
    delayTimeR.setRange(0.0, 2000.0, 1.0);
    delayTimeR.setSliderStyle(Slider::RotaryVerticalDrag);
    delayTimeR.setTextValueSuffix("ms");
    delayTimeR.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 20);
    delayTimeR.addListener(this);
    addAndMakeVisible(delayTimeR);
    // label design
    dtrLabel.setText("Right", dontSendNotification);
    dtrLabel.attachToComponent(&delayTimeR, false);
    dtrLabel.setFont(Font(15.0));
    dtrLabel.setJustificationType(Justification::centredTop);
    addAndMakeVisible(dtrLabel);
    
    // output gain
    outGain.setRange(-12.0, 6.0, 0.1);
    outGain.setSliderStyle(Slider::RotaryVerticalDrag);
    outGain.setTextValueSuffix("dB");
    outGain.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    outGain.addListener(this);
    addAndMakeVisible(outGain);
    // label design
    oGLabel.setText("Out", dontSendNotification);
    oGLabel.attachToComponent(&outGain, false);
    oGLabel.setFont(Font(15.0));
    oGLabel.setJustificationType(Justification::centredTop);
    addAndMakeVisible(oGLabel);
    
    // input gain
    inGain.setRange(-12.0, 6.0, 0.1);
    inGain.setSliderStyle(Slider::RotaryVerticalDrag);
    inGain.setTextValueSuffix("dB");
    inGain.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    inGain.addListener(this);
    addAndMakeVisible(inGain);
    // label design
    iGLabel.setText("In", dontSendNotification);
    iGLabel.attachToComponent(&inGain, false);
    iGLabel.setFont(Font(15.0));
    iGLabel.setJustificationType(Justification::centredTop);
    addAndMakeVisible(iGLabel);
    
    // delay dry / wet mix
    dryWet.setRange(0.0, 100.0, 0.1);
    dryWet.setSliderStyle(Slider::RotaryVerticalDrag);
    dryWet.setTextValueSuffix("%");
    dryWet.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    dryWet.addListener(this);
    addAndMakeVisible(dryWet);
    // dry wet label design
    dwLabel.setText("Delay", dontSendNotification);
    dwLabel.attachToComponent(&dryWet, false);
    dwLabel.setFont(Font(15.0));
    dwLabel.setJustificationType(Justification::centredTop);
    addAndMakeVisible(dwLabel);
    
    // delay feedback
    fb.setRange(0.0, 101.0, 0.1);
    fb.setSliderStyle(Slider::RotaryVerticalDrag);
    fb.setTextValueSuffix("%");
    fb.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    fb.addListener(this);
    addAndMakeVisible(fb);
    // label design
    fbLabel.setText("Dly Feedback", dontSendNotification);
    fbLabel.attachToComponent(&fb, false);
    fbLabel.setFont(Font(15.0));
    fbLabel.setJustificationType(Justification::centredTop);
    addAndMakeVisible(fbLabel);
    
    // link button
    addAndMakeVisible (&linkButton);
    linkButton.setButtonText ("Link");
    linkButton.addListener (this);
    linkButton.setClickingTogglesState(true);
    
    // shimmer
    shimmer.setRange(0.0, 100.0, 0.1);
    shimmer.setSliderStyle(Slider::RotaryVerticalDrag);
    shimmer.setTextValueSuffix("%");
    shimmer.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    shimmer.addListener(this);
    addAndMakeVisible(shimmer);
    // label design
    shimLabel.setText("Shimmer", dontSendNotification);
    shimLabel.attachToComponent(&shimmer, false);
    shimLabel.setFont(Font(15.0));
    shimLabel.setJustificationType(Justification::centredTop);
    addAndMakeVisible(shimLabel);
    
    // darken
    darkenSlider.setRange(0.0, 100.0, 0.1);
    darkenSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    darkenSlider.setTextValueSuffix("%");
    darkenSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 20);
    darkenSlider.addListener(this);
    addAndMakeVisible(darkenSlider);
    // label design
    darkenLabel.setText("Darken", dontSendNotification);
    darkenLabel.attachToComponent(&darkenSlider, false);
    darkenLabel.setFont(Font(15.0));
    darkenLabel.setJustificationType(Justification::centredTop);
    addAndMakeVisible(darkenLabel);
    
    // chorus depth
    depth.setRange(0.0, 100.0, 0.1);
    depth.setSliderStyle(Slider::RotaryVerticalDrag);
    depth.setTextValueSuffix("%");
    depth.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    depth.addListener(this);
    addAndMakeVisible(depth);
    // label design
    depLabel.setText("Depth", dontSendNotification);
    depLabel.attachToComponent(&depth, false);
    depLabel.setFont(Font(15.0));
    depLabel.setJustificationType(Justification::centredTop);
    addAndMakeVisible(depLabel);
    
    // chorus rate
    rateSlider.setRange(0.0, 20.0, 0.001);
    rateSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    rateSlider.setTextValueSuffix(" Hz");
    rateSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    rateSlider.addListener(this);
    addAndMakeVisible(rateSlider);
    // label design
    rateLabel.setText("Rate", dontSendNotification);
    rateLabel.attachToComponent(&rateSlider, false);
    rateLabel.setFont(Font(15.0));
    rateLabel.setJustificationType(Justification::centredTop);
    addAndMakeVisible(rateLabel);
    
    // chrous feedback
    chorusFb.setRange(0.0, 100.0, 0.1);
    chorusFb.setSliderStyle(Slider::RotaryVerticalDrag);
    chorusFb.setTextValueSuffix("%");
    chorusFb.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    chorusFb.addListener(this);
    addAndMakeVisible(chorusFb);
    // label design
    chorusFbLabel.setText("Feedback", dontSendNotification);
    chorusFbLabel.attachToComponent(&chorusFb, false);
    chorusFbLabel.setFont(Font(14.0));
    chorusFbLabel.setJustificationType(Justification::centredTop);
    addAndMakeVisible(chorusFbLabel);
    
    // chrous dry wet mix
    chorusDw.setRange(0.0, 100.0, 0.1);
    chorusDw.setSliderStyle(Slider::RotaryVerticalDrag);
    chorusDw.setTextValueSuffix("%");
    chorusDw.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    chorusDw.addListener(this);
    addAndMakeVisible(chorusDw);
    // label design
    chorusDwLabel.setText("Chorus", dontSendNotification);
    chorusDwLabel.attachToComponent(&chorusDw, false);
    chorusDwLabel.setFont(Font(15.0));
    chorusDwLabel.setJustificationType(Justification::centredTop);
    addAndMakeVisible(chorusDwLabel);
    
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (808, 400);
    startTimer(100); //for the UI
}

delazedAudioProcessorEditor::~delazedAudioProcessorEditor()
{
}

//==============================================================================
void delazedAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.drawImageAt(MyBackground, 0, 0);
    g.setColour (Colours::white);
    getLookAndFeel().setColour (Slider::thumbColourId, Colours::violet);
    g.setFont (17.0f); // set delay time font size
    g.drawSingleLineText("Delay Time", 130, 120, Justification::centred);
    g.drawRect(26,140,209,180); // rectangle around delay time controls
    g.fillRect(254,212,282,1); // line dividing controls
    g.setFont(14.0f); // set chorus controls font size
    g.drawSingleLineText("Chorus Controls", 386, 230, Justification::centred);
    g.drawRect(566,73,95,301); // rectangle around mix controls
    g.setFont(20.0f); // set Mix & Gain font size
    g.drawSingleLineText("Mix", 613, 57, Justification::centred);
    g.drawRect(685,73,95,301); // rectangle around gain controls
    g.drawSingleLineText("Gains", 732, 57, Justification::centred);

}

void delazedAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    int x = 30; int y = 100; int w = 100; int h = 100;
    int sp = 30; // space variable
    
    // about button
    about.setBounds(10,375,20,20);
    
    // delay time controls
    delayTimeL.setBounds(x-5, y+10+(sp*2), w, h);
    delayTimeR.setBounds(x+w+5, y+10+(sp*2), w, h);
    linkButton.setBounds(x+w-20, y+10+h+(sp*2)+10, 46, 21); // between & below L and R
    
    // row 1, left to right
    fb.setBounds(x+((w+5)*2), y, w, h);
    shimmer.setBounds(x+((w+5)*3), y, w, h);
    darkenSlider.setBounds(x+((w+5)*4), y, w, h);
    
    // row 2, left to right
    depth.setBounds(x+((w+5)*2), y+h+(sp*2)+5, w, h);
    rateSlider.setBounds(x+((w+5)*3), y+h+(sp*2)+5, w, h);
    chorusFb.setBounds(x+((w+5)*4), y+h+(sp*2)+5, w, h);
    
    // dry wet column
    dryWet.setBounds(x+((w+5)*5), y, w+15, h+15);
    chorusDw.setBounds(x+((w+5)*5), y+h+15+sp, w+15, h+15);
    
    // gains column
    inGain.setBounds(25+(x-10)+((w+5)*6), y, w+15, h+15);
    outGain.setBounds(25+(x-10)+((w+5)*6), y+h+15+sp, w+15, h+15);

}

//This gets called whenever the user moves a slider
void delazedAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    // make an additional "else if" for each slider
    if (slider == &delayTimeL) {
        processor.delayTimeLUParam->beginChangeGesture();
        *processor.delayTimeLUParam = (float) delayTimeL.getValue();
        processor.delayTimeLUParam->endChangeGesture();
    }
    
    else if (slider == &delayTimeR) {
        processor.delayTimeRUParam->beginChangeGesture();
        *processor.delayTimeRUParam = (float) delayTimeR.getValue();
        processor.delayTimeRUParam->endChangeGesture();
    }
    
    else if (slider == &outGain) {
        processor.oGainUParam->beginChangeGesture();
        *processor.oGainUParam = (float) outGain.getValue();
        processor.oGainUParam->endChangeGesture();
    }
    
    else if (slider == &inGain) {
        processor.iGainUParam->beginChangeGesture();
        *processor.iGainUParam = (float) inGain.getValue();
        processor.iGainUParam->endChangeGesture();
    }
    
    else if (slider == &dryWet) {
        processor.dryWetUParam->beginChangeGesture();
        *processor.dryWetUParam = (float) dryWet.getValue();
        processor.dryWetUParam->endChangeGesture();
    }
    
    else if (slider == &fb) {
        processor.fbUParam->beginChangeGesture();
        *processor.fbUParam = (float) fb.getValue();
        processor.fbUParam->endChangeGesture();
    }
    
    else if (slider == &shimmer) {
        processor.shimmerUParam->beginChangeGesture();
        *processor.shimmerUParam = (float) shimmer.getValue();
        processor.shimmerUParam->endChangeGesture();
    }
    
    else if (slider == &darkenSlider) {
        processor.darken->beginChangeGesture();
        *processor.darken = (float) darkenSlider.getValue();
        processor.darken->endChangeGesture();
    }

    else if (slider == &chorusDw) {
        processor.chorusDryWetUParam->beginChangeGesture();
        *processor.chorusDryWetUParam = (float) chorusDw.getValue();
        processor.chorusDryWetUParam->endChangeGesture();
    }

    else if (slider == &depth) {
        processor.depthUParam->beginChangeGesture();
        *processor.depthUParam = (float) depth.getValue();
        processor.depthUParam->endChangeGesture();
    }

    else if (slider == &rateSlider) {
        processor.rate->beginChangeGesture();
        *processor.rate = (float) rateSlider.getValue();
        processor.rate->endChangeGesture();
    }

    else if (slider == &chorusFb) {
        processor.chorusFbUParam->beginChangeGesture();
        *processor.chorusFbUParam = (float) chorusFb.getValue();
        processor.chorusFbUParam->endChangeGesture();
    }
}

void delazedAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    if (buttonThatWasClicked == &linkButton)
    {
        processor.link->beginChangeGesture();
        *processor.link = (float) linkButton.getToggleState(); //alternates between 0 and 1.
        processor.link->endChangeGesture();
        //show user that something happened.
        if (*processor.link == 1) {
            linkButton.setButtonText ("Link");
        } else {
            linkButton.setButtonText ("Unlink");
        }
    }
    
    if (buttonThatWasClicked == &about)
    {
        AlertWindow::showMessageBox(AlertWindow::NoIcon, TRANS("Delazed and Confused?"),"Shimmer: Squeezes the delay feedback \nthrough 2 filters, both with\n a center frequency of 1.2kHz. \nReduces the lows while increasing the highs.\nIf delay feedback is 100% or more, increasing this\n parameter will \"simmer\" the self-oscillation\nNote: Shimmer is less effective on low frequency signals.\n\nDarken: Attenuates the highs of the overall output\n0 to 100% = 0 to -9 dB \n\n Link: Slaves the right delay time to the left delay time.\nBonus! Try tweaking the right delay time when\n link is pressed for some freaky sounds.\n\n100%+ Feedback made possible by buosseph's \njuce-distortion code from GitHub.\nhttps://github.com/buosseph/juce-distortion  \n\n\nApplication version 2.0 Beta\n Developed by:  Lexi Slovik" );
    }
}

//This gets called every N msec so that sliders can update their value if the host changed them using parameter automation
void delazedAudioProcessorEditor::timerCallback()
{
    //Update the value of each slider to match the value in the Processor
    if (*processor.link == 1) {
        delayTimeL.setValue(*processor.delayTimeLUParam, dontSendNotification);
        delayTimeR.setValue(*processor.delayTimeRUParam, dontSendNotification);
    } else {
        delayTimeL.setValue(*processor.delayTimeLUParam, dontSendNotification);
        delayTimeR.setValue(*processor.delayTimeLUParam, dontSendNotification);
    }
//    delayTimeL.setValue(*processor.delayTimeLUParam, dontSendNotification);
//    delayTimeR.setValue(*processor.delayTimeRUParam, dontSendNotification);
    outGain.setValue(*processor.oGainUParam, dontSendNotification);
    inGain.setValue(*processor.iGainUParam, dontSendNotification);
    dryWet.setValue(*processor.dryWetUParam, dontSendNotification);
    fb.setValue(*processor.fbUParam, dontSendNotification);
    linkButton.setToggleState(*processor.link, dontSendNotification);
    shimmer.setValue(*processor.shimmerUParam, dontSendNotification);
    darkenSlider.setValue(*processor.darken, dontSendNotification);
    chorusDw.setValue(*processor.chorusDryWetUParam, dontSendNotification);
    depth.setValue(*processor.depthUParam, dontSendNotification);
    rateSlider.setValue(*processor.rate, dontSendNotification);
    chorusFb.setValue(*processor.chorusFbUParam, dontSendNotification);
    //someOtherSlider->setValue(processor.someOtherUserParameter->getActualValue(), dontSendNotification);
}

