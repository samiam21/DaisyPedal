#ifndef HWDEBUG_H
#define HWDEBUG_H

#include "DaisyDuino.h"
#include "../../PedalConfig.h"

static size_t hwNumChannels;

extern void HWDebugSetup(size_t pNumChannels);
extern void HWDebugCallback(float **in, float **out, size_t size);
extern void HWDebugLoop();

#endif