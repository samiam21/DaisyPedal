#include "Knob.h"

void Knob::Init(uint32_t pin, uint32_t pMode)
{
    Init(pin, pMode, minValue, maxValue);
}

void Knob::Init(uint32_t pin, uint32_t pMode, float pMinValue, float pMaxValue)
{
    // Set the pin to read
    knobPin = pin;

    // Update the new min and max values
    minValue = pMinValue;
    maxValue = pMaxValue;

    // Initialize the pin and set the initial knob reading
    pinMode(pin, pMode);
    knobReading = analogRead(knobPin);
}

void Knob::SetNewValue(float &valueToSet)
{
    // Read the knob
    int newKnobReading = analogRead(knobPin);

    // Account for jitter so we aren't constantly changing the value
    if (newKnobReading > (knobReading + knobJitter) || newKnobReading < (knobReading - knobJitter))
    {
        // Check for min value, accounting for jitter
        if (newKnobReading <= (minKnobReadingValue + knobJitter))
        {
            // Set the reading to min
            knobReading = minKnobReadingValue;
            debugPrintln("MIN!");
        }
        // Check for max value, accounting for jitter
        else if (newKnobReading >= (maxKnobReadingValue - knobJitter))
        {
            // Set the reading to max
            knobReading = maxKnobReadingValue;
            debugPrintln("MAX!");
        }
        // Standard reading
        else
        {
            knobReading = newKnobReading;
            debugPrintln(newKnobReading);
        }

        // Set the new value
        if (knobReading == maxKnobReadingValue)
        {
            valueToSet = maxValue;
        }
        else if (knobReading == minKnobReadingValue)
        {
            valueToSet = minValue;
        }
        else
        {
            valueToSet = ((float)knobReading / (float)maxKnobReadingValue) * maxValue;
        }
    }
}