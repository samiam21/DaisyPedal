#include "DaisyDuino.h"

DaisyHardware hw;

size_t num_channels;
Switch button;

// One DelayLine of 24000 floats.
DelayLine<float, 24000> del_line;

void MyCallback(float **in, float **out, size_t size)
{
    //Debounce the button
    button.Debounce();

    for (size_t i = 0; i < size; i++)
    {
        float dry, wet;

        // Read Dry from I/O
        dry = in[1][i];

        // Read Wet from Delay Line
        wet = del_line.Read();

        // Write to Delay with some feedback
        del_line.Write((wet * 0.5) + dry);

        // Check if the button is pressed
        if (button.Pressed())
        {
            // Send only dry signal
            out[0][i] = dry;
        }
        else
        {
            // Mix Dry and Wet and send to I/O
            out[0][i] = wet * 0.707 + dry * 0.707;
        }
    }
}

void setup()
{
    float samplerate;
    // Initialize for Daisy pod at 96kHz
    hw = DAISY.init(DAISY_SEED, AUDIO_SR_96K);
    num_channels = hw.num_channels;

    //setup the button
    //update at 1kHz, no invert, on pin 28
    button.Init(1000, true, 28);

    // Init Delay Line
    del_line.Init();

    // Set Delay Time in Samples
    del_line.SetDelay(8000.0f);

    // Start Audio
    DAISY.begin(MyCallback);
}

void loop()
{
}
