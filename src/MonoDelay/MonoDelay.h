#ifndef MONO_DELAY
#define MONO_DELAY

#include "DaisyDuino.h"
#include "../../PedalConfig.h"
#include "TempoArray.h"

// Constant parameters
static const int tapTempoButtonPin = effectButtonPin1;
static const int audioInChannel = 0;
static const int audioOutChannel = 0;
static const size_t delayMaxSize = 96000;
static const long debounce = 400;

// Mutable parameters
static size_t tempoBpm = 90;
static unsigned long tapTempoTime = 0;
static TempoArray tempoArray;
static DelayLine<float, delayMaxSize> del_line;

// Function definitions
extern void MonoDelaySetup();
extern void MonoDelayCleanup();
extern void MonoDelayCallback(float **in, float **out, size_t size);
extern void MonoDelayLoop();

#endif