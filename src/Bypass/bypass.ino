#include "DaisyDuino.h"

size_t numChannels;

void BypassSetup(size_t pNumChannels)
{
    numChannels = pNumChannels;
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