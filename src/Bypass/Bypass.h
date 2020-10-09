#ifndef BYPASS_H
#define BYPASS_H

#include "DaisyDuino.h"

static size_t numChannels;

extern void BypassSetup(size_t pNumChannels);
extern void BypassCallback(float **in, float **out, size_t size);

#endif