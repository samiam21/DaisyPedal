#include <bitset>
#include "DaisyDuino.h"
#include "src/EffectType.h"
#include "PedalConfig.h"
#include "src/Bypass/Bypass.h"
#include "src/MonoDelay/MonoDelay.h"

// Global variables
DaisyHardware hw;
size_t num_channels;

// Volatile parameters
volatile EffectType currentEffect = Unset;

void setup() 
{
    // Initialize the serial debug output
    initDebugPrint();
    debugPrint("Starting DaisyPedal...");

    // Initialize Daisy at 96kHz
    hw = DAISY.init(DAISY_SEED, AUDIO_SR_96K);
    num_channels = hw.num_channels;

    // Initialize the hex switch pins
    pinMode(hexSwitchPin1, INPUT_PULLDOWN);
    pinMode(hexSwitchPin2, INPUT_PULLDOWN);
    pinMode(hexSwitchPin3, INPUT_PULLDOWN);
    pinMode(hexSwitchPin4, INPUT_PULLDOWN);

    // Initialize the control LED
    pinMode(controlLedPin, OUTPUT);
}

void loop() 
{
    // Read the state of the hex switch pins
    std::bitset<4> pin1(digitalRead(hexSwitchPin1));
    std::bitset<4> pin2(digitalRead(hexSwitchPin2));
    std::bitset<4> pin3(digitalRead(hexSwitchPin3));
    std::bitset<4> pin4(digitalRead(hexSwitchPin4));    

    // Get the combined hex value and convert it to an int
    std::bitset<4> combined = pin1 | (pin2 << 1) | (pin3 << 2) | (pin4 << 3);
    int readEffectState = (int)(combined.to_ulong());

    // Check if the state is new and switch to the new state
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
                BypassCleanup();
                break;
            default:
                break;
        }

        // Start the new effect
        switch(readEffectState)
        {
            case MonoDelay:
                debugPrint("Switching to MonoDelay");

                // Turn LED on
                digitalWrite(controlLedPin, HIGH);

                // Initialize MonoDelay and start Daisy
                MonoDelaySetup();
                DAISY.begin(MonoDelayCallback);

                break;
            case Bypass:
            default:
                debugPrint("Switching to Bypass");

                // Turn LED off
                digitalWrite(controlLedPin, LOW);

                // Initialize Bypass and start Daisy
                BypassSetup(num_channels);
                DAISY.begin(BypassCallback);

                break;
        }

        // Update the current effect
        currentEffect = (EffectType)readEffectState;
    }

    // Execute the effect loop commands
    switch (currentEffect)
    {
        case MonoDelay:
            MonoDelayLoop();
            break;
        case Bypass:
            BypassLoop();
            break;
        default:
            break;
    }
}
