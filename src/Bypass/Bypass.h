#ifndef BYPASS_H
#define BYPASS_H

#include "DaisyDuino.h"
#include "../IEffect.h"
#include "../../PedalConfig.h"

class Bypass: public IEffect
{
    public:
        void Setup(size_t pNumChannels);
        void Cleanup();
        void AudioCallback(float **in, float **out, size_t size);
        void Loop();

    private:
        size_t numChannels;
};

#endif