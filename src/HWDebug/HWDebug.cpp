#include "HWDebug.h"

void HWDebugSetup(size_t pNumChannels)
{
    hwNumChannels = pNumChannels;

    // Initialize the LEDs and buttons
    pinMode(effectButtonPin1, INPUT);
    pinMode(effectButtonPin2, INPUT);
    pinMode(effectButtonPin3, INPUT);
    pinMode(effectLedPin1, OUTPUT);
    pinMode(effectLedPin2, OUTPUT);
    pinMode(effectLedPin3, OUTPUT);
}

void HWDebugCallback(float **in, float **out, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t chn = 0; chn < hwNumChannels; chn++)
        {
            out[chn][i] = in[chn][i];
        }
    }
}

void HWDebugLoop()
{
    // Button/LED 1
    if (digitalRead(effectButtonPin1) == HIGH)
    {
        digitalWrite(effectLedPin1, HIGH);
    }
    else
    {
        digitalWrite(effectLedPin1, LOW);
    }

    // Button/LED 2
    if (digitalRead(effectButtonPin2) == HIGH)
    {
        digitalWrite(effectLedPin2, HIGH);
    }
    else
    {
        digitalWrite(effectLedPin2, LOW);
    }

    // Button/LED 3
    if (digitalRead(effectButtonPin3) == HIGH)
    {
        digitalWrite(effectLedPin3, HIGH);
    }
    else
    {
        digitalWrite(effectLedPin3, LOW);
    }
}