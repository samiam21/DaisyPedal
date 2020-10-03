#include <bitset>
#include "DaisyDuino.h"
#include "EffectType.h"
#include "Bypass/Bypass.ino"
#include "MonoDelay/MonoDelay.ino"

// Global variables
DaisyHardware hw;
size_t num_channels;

// Pin Definitions
const int hexSwitchPin1 = 6;
const int hexSwitchPin2 = 7;
const int hexSwitchPin4 = 8;
const int hexSwitchPin8 = 9;
const int ledPin = 15; // Built in LED is LED_BUILTIN

// Volatile parameters
volatile EffectType currentEffect = Unset;

void setup() 
{
    // Initialize Daisy at 96kHz
    hw = DAISY.init(DAISY_SEED, AUDIO_SR_96K);
    num_channels = hw.num_channels;

    // Initialize the hex switch pins
    pinMode(hexSwitchPin1, INPUT);
    pinMode(hexSwitchPin2, INPUT);
    pinMode(hexSwitchPin4, INPUT);
    pinMode(hexSwitchPin8, INPUT);

    // Initialize the LED
    pinMode(ledPin, OUTPUT);
}

void loop() 
{
    // Read the state of the hex switch pins
    std::bitset<4> pin1(digitalRead(hexSwitchPin1));
    std::bitset<4> pin2(digitalRead(hexSwitchPin2));
    std::bitset<4> pin4(digitalRead(hexSwitchPin4));
    std::bitset<4> pin8(digitalRead(hexSwitchPin8));

    // Get the combined hex value and convert it to an int
    std::bitset<4> combined = pin1 | (pin2 << 1) | (pin4 << 2) | (pin8 << 3);
    int readEffectState = (int)(combined.to_ulong());

    // Check if the state is new
    if (currentEffect != readEffectState)
    {
        // A new effect has been chosen, stop the old effect
        switch(currentEffect)
        {
            case MonoDelay:
                // Clean up the MonoDelay
                MonoDelayCleanup();
                break;
            case Bypass:
            default:
                break;
        }

        // Stop the current Daisy effect (not necessary?)
        //DAISY.end();

        // Start the new effect
        switch(readEffectState)
        {
            case MonoDelay:
                // Turn LED on
                digitalWrite(ledPin, HIGH);

                // Initialize MonoDelay and start Daisy
                MonoDelaySetup();
                DAISY.begin(MonoDelayCallback);

                break;
            case Bypass:
            default:
                // Turn LED off
                digitalWrite(ledPin, LOW);

                // Initialize Bypass and start Daisy
                BypassSetup(num_channels);
                DAISY.begin(BypassCallback);

                break;
        }

        // Update the current effect
        currentEffect = (EffectType)readEffectState;
    }
}
