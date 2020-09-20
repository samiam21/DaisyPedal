#include "DaisyDuino.h"

DaisyHardware hw;

// Constant parameters
size_t num_channels;
const int buttonPin = 6;
const int ledPin = LED_BUILTIN; // Built in LED
const int audioInChannel = 0;
const int audioOutChannel = 1;

// Volatile parameters
volatile bool addDelay = true;
volatile float tempo = 14000.0f;
int buttonState = 0;

// One DelayLine of 24000 floats.
DelayLine<float, 24000> del_line;

// Audio callback when audio input occurs
void MyCallback(float **in, float **out, size_t size)
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

        // Check if the button is pressed
        if (addDelay)
        {
            // Mix Dry and Wet and send to I/O
            out[audioOutChannel][i] = wet * 0.707 + dry * 0.707;
        }
        else
        {
            // Send only dry signal
            out[audioOutChannel][i] = dry;
        }
    }
}

void setup()
{
    float samplerate;
    // Initialize for Daisy pod at 96kHz
    hw = DAISY.init(DAISY_SEED, AUDIO_SR_96K);
    num_channels = hw.num_channels;

    // Initialize button input
    pinMode(buttonPin, INPUT);

    // Init Delay Line
    del_line.Init();

    // Set Delay Time in Samples
    del_line.SetDelay(tempo);

    // Start Audio
    DAISY.begin(MyCallback);
}

void loop()
{
  // Read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // Check if the pushbutton is pressed
  if (buttonState == HIGH)
  {
    // Turn LED on
    digitalWrite(ledPin, HIGH);

    // Enable the delay
    addDelay = true;
  }
  else
  {
    // Turn LED off
    digitalWrite(ledPin, LOW);

    // Disable the delay
    addDelay = false;
  }
}