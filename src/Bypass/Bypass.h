#ifndef BYPASS_H
#define BYPASS_H

#include "DaisyDuino.h"
#include "../../PedalConfig.h"

static size_t numChannels;

extern void BypassSetup(size_t pNumChannels);
extern void BypassCleanup();
extern void BypassCallback(float **in, float **out, size_t size);
extern void BypassLoop();

#endif