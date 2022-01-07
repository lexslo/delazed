# Delazed
## VST and Audio Unit Effect Plug-in
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

## About
Delazed is a digital audio effect I designed in order to create new and exciting sounds. I wanted to emulate analog tape delay and make use of the quirks of the digital environment to create purposeful "mistakes" that generate unique sounds.

## Table of Contents
* [Description](#description)
* [Layout](#layout)
* [Example](#example)
* [Installation](#installation)
* [Technical](#technical)
* [Questions](#questions)
* [License](#license)
* [Credits](#credits)


### Description
Delazed is a chorus effect that is fed into ping pong delay. I made use of soft clipping and filters in order to allow for lots of feedback from both the chorus and the delay.

These are the following parameters available and their corresponding ranges:
- Delay Time L: 0 - 2000ms
- Delay Time R: 0 - 2000ms
- Link: 0 or 1 (pressed or not pressed)
- Delay Feedback: 0 - 101%
- Shimmer: 0 - 100%
- Darken: 0 - 100%
- Depth: 0 - 100%
- Rate: 0.001 - 20 Hz
- Chorus Feedback: 0 - 100%
- Delay Mix: 0 - 100%
- Chorus Mix: 0 - 100%
- Input Gain: -12 to +6 dB
- Output Gain: -12 to +6 dB

I also included a [?] button for users to click whichs opens a new window with more information about the plug-in.

### Layout
![Delazed Default GUI](assets/images/delazed-default-gui.png)

### Example
Please download the included MP3 file titled "delazed-musical-example" located in assets/mp3. The following serves as a listening guide for that sample:

* 0:00 - Default Settings (see GUI screenshot p.1)
* 0:04 - L Delay Time increase from 300ms to 1758ms 
* 0:09 - R Delay Time increase from 300ms to 1670ms, decrease to 879ms
* 0:18 - Chorus Mix increase to 100% over 4 seconds
* 0:22 - Delay Mix increase to 91% over 5 seconds
* 0:27 - Chorus Feedback increase to 100% over 5 seconds
* 0:32 - Chorus Depth increase to 100% over 4 seconds 
* 0:40 - Chorus Rate increase to 17 Hz, then decrease to 0.61 Hz
* 0:47 - Delay Feedback increase to 101%      
* 1:03 - Shimmer increase to 100%
* 1:15 - Shimmer decrease to 41%
* 1:21 - Input Gain to +6dB
* 1:24 - Link Button pressed; L and R delay time now linked
* 1:30 - R Delay Time rapid change back and forth 
    - Shimmer decrease to 0%
* 1:32 - Delay Feedback decrease to 52%
* 1:34 - Input Gain decrease to +0 dB
* 1:39 - Delay Mix to 0%, solo Chorus
* 1:46 - Chorus Depth decrease to 23%
* 1:48 - Chorus Feedback decrease to 35%
* 1:53 - Chorus Mix decrease to 45%

### Installation
* Mac OS
    - Download the delazed.component file (this will run as an audio unit) and/or the delazed.vst3 file. 
    - Click out to your desktop. Hold the Option key on your keyboard, and click the Go menu at the top of the screen. With the Go menu open, you'll notice that pressing and releasing Option will display or hide the Library choice in this menu. Select Library from the Go menu (while holding down Option) to access the hidden folder.
    - Open the Audio folder. Open Plug-ins. Drag the .component file to the components folder and/or drag the .vst3 file to the VST3 folder.
    - Open your DAW (or restart if it is already open). The loading process will scan your computer for audio units and VSTs. Once open, you will find Delazed as an effect plug-in option for Audio Unit and/or VST3 depending on which one(s) you installed.

* Windows
    - Coming soon!


### Technical
I really wanted to achieve self-oscillation through the delay feedback, so I set a threshold where if feedback > 99%, the signal will be processed through the softClip function. The same is true for chorus feedback. In order to avoid signal overload from having two feedback instances, I set another threshold so that if the delay feedback + chorus feedback >= 1.0, the entire signal would be process through the softClip function.

I liked the idea of having some control over the timbre, so I added the shimmer and darken parameters. Shimmer sends the signal through a low shelf filter then through a high shelf filter. The center frequency for both filters is 1.2 kHz. For the most part, the range 0 - 100% is converted to 0 to -6 dB for the low shelf and 0 to +0.5 dB for the high shelf simultaneously. To avoid overload, I set a threshold so that if the delay feedback is above 92%, the high shelf gain maxes out at 0.0 dB (or no gain); if the delay feedback is 100% or more, the high shelf actually starts attenuating 0 to -1 dB. Darken sends the entire signal chain though a low shelf filter at the end. The center frequency is 300 Hz and the user defines the gain; 0 - 100% converts to 0 to -9 dB.

The chorus feedback is also being processed through a filter — only after the chorus feedback exceeds 80%. From 80% to 100%, the user is controlling the filter attenuation along with the chorus feedback. The frequency center is static (900 Hz) and the 80% to 100% becomes a range of 0 to -3 dB. I implemented this filter because the timbre of the chorus feedback through soft clipping was a bit overwhelming, but I still wanted the user to be able to crank it to 100%. This way the signal doesn’t overload, nor does it take over the sound with soft clipped chorus feedback.

I like having ambiguous parameter names like “shimmer” and “darken” because it forces the user to use their ears more than their eyes. Since the names and ranges are a bit ambiguous, I included a [ ? ] button that opens a window with a brief explanation. The window looks like this:

<img src="./assets/images/question.png" alt="Question Mark" width="240" height="260" />

### Questions
Please reach out if you have any questions or want to collaborate on future projects! Feel free to email me at lexi.slovik@gmail.com and connect with me on [LinkedIn](https://www.linkedin.com/in/lex-slovik-018979186/)

## License
This application is covered under the GPLv3 license.

[Read about GPL v3 License](https://www.gnu.org/licenses/gpl-3.0)

## Credits
This application was made using [Projucer](https://juce.com/get-juce). I actively developed this plug-in while a student at University of Oregon in 2018.

[Juce-Distortion](https://github.com/juce-distortion)
