#include "DaisyDuino.h"
#include "PedalConfig.h"
#include "../../TempoArray.h"

// Constant parameters
const int tapTempoButtonPin = effectButtonPin1;
const int audioInChannel = 0;
const int audioOutChannel = 0;
const size_t delayMaxSize = 96000;
const long debounce = 400;

// Mutable parameters
volatile size_t tempoBpm = 90;
volatile unsigned long tapTempoTime = 0;
TempoArray tempoArray;

// TEMPO NOTES:
//  - Max delay size is based on audio rate, currently 96kHz
//  - Tempo = Max is equal to "slowest" delay
//    - 96000 => 30bpm
//    - 48000 => 60bpm
//    - 24000 => 120bpm
//    - Formula: 96000 / (bpm) * 30
//
//  - Timespan (between beats) -> Samples
//    - 2000ms = 96000
//    - 1000ms = 48000
//    - 500ms = 24000
//    - Formula: (96000 * t) / 2000

// Declare the DelayLine
DelayLine<float, delayMaxSize> del_line;

// Initialize the delay
void MonoDelaySetup()
{
    // Init Delay Line
    del_line.Init();

    // Set Delay Time in Samples
    size_t tempoSamples = (96000 / tempoBpm) * 30;
    del_line.SetDelay(tempoSamples);

    // Initialize the tap tempo button and led pins
    pinMode(tapTempoButtonPin, INPUT);
}

// Clean up the parameters for mono delay
void MonoDelayCleanup()
{
    del_line.Reset();
}

// Audio callback when audio input occurs
void MonoDelayCallback(float **in, float **out, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        float dry, wet;

        // Read Dry from I/O
        dry = in[audioInChannel][i];

        // Read Wet from Delay Line
        wet = del_line.Read();

        // Write to Delay with some feedback
        del_line.Write((wet * 0.5) + dry);

        // Mix Dry and Wet and send to I/O
        out[audioOutChannel][i] = wet * 0.707 + dry * 0.707;
    }
}

// Logic for mono delay to add into the main loop
void MonoDelayLoop()
{
    // Read the tap tempo button
    int reading = digitalRead(tapTempoButtonPin);

    // Debounce the button and check for it pressed
    if (reading == HIGH && millis() - tapTempoTime > debounce)
    {
        debugPrint("button pressed");

        // Calculate the duration (ignore a duration longer than 2 seconds)
        unsigned long duration = millis() - tapTempoTime;
        if (duration < 2000)
        {
            debugPrint();
            debugPrint("---------");
            debugPrint(duration);

            // Add the duration to the tempo array
            tempoArray.push(duration);

            // Calculate the average duration of the items in the array
            unsigned long avg = tempoArray.average();

            debugPrint(avg);
            debugPrint("---------");
            debugPrint();
        } 

        // Update the time
        tapTempoTime = millis();
    }
}