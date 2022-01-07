//
//  LFO.h
//
//  Created by Luke Dahl on 3/4/15.

// LFO is a low-frequency oscillator with basic functionality.
// The LFO outputs a sinusoidal waveform, which is created by interpolating
// a 1024-sample wavetable.

#ifndef __basic_basicLFO__
#define __basic_basicLFO__
#include <stdio.h>
#endif /* defined(__basic_basicLFO__) */


class basicLFO {
public:
    basicLFO();                             // Constructor
    void setFreq(float freq, float fs);     // Set the frequency of the oscillator.
    float tick();                           // Generate a sample of output and update the state
    void resetPhase();                      // Set the oscillator phase to 0
    
private:
    static const int N = 1024;      // size of the wavetable
    float table[N];                 // the wavetable
    float phase_inc;                // amount to increment phase each tick
    float phase;                    // current index into the wavetable
};
