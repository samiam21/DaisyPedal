#include "Bypass.h"

void BypassSetup(size_t pNumChannels)
{
    numChannels = pNumChannels;

    // Initialize the LEDs and buttons
    pinMode(effectButtonPin1, INPUT);
    pinMode(effectButtonPin2, INPUT);
    pinMode(effectButtonPin3, INPUT);
    pinMode(effectKnobPin1, INPUT);
    pinMode(effectKnobPin2, INPUT);
    pinMode(effectKnobPin3, INPUT);
    pinMode(effectLedPin1, OUTPUT);
    pinMode(effectLedPin2, OUTPUT);
    pinMode(effectLedPin3, OUTPUT);
}

void BypassCallback(float **in, float **out, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t chn = 0; chn < numChannels; chn++)
        {
            out[chn][i] = in[chn][i];
        }
    }
}

void BypassCleanup()
{
    // Turn off the LEDs
    debugPrint("Turning off LEDs");
    digitalWrite(effectLedPin1, LOW);
    digitalWrite(effectLedPin2, LOW);
    digitalWrite(effectLedPin3, LOW);
}

void BypassLoop()
{
    // Button1 turns on LED 1
    if (digitalRead(effectButtonPin1) == HIGH)
    {
        digitalWrite(effectLedPin1, HIGH);
    }
    else
    {
        digitalWrite(effectLedPin1, LOW);
    }

    // Button 2 turns on LED 2
    if (digitalRead(effectButtonPin2) == HIGH)
    {
        digitalWrite(effectLedPin2, HIGH);
    }
    else
    {
        digitalWrite(effectLedPin2, LOW);
    }

    // Knob 3 controls intensity of LED 3
    // Turn on the LED, at the level dictated by the knob
    //  (map the 10bit input value to an 8 bit PWM output)
    analogWrite(effectLedPin3, analogRead(effectKnobPin3) / 4);
}