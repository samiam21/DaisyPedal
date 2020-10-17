#ifndef MONO_DELAY
#define MONO_DELAY

#include "DaisyDuino.h"
#include "../../PedalConfig.h"
#include "TempoArray.h"

/**********************************************
 * Mono Delay Effect
 * 
 * Button 1 - Tap Tempo
 * Button 2 - N/U
 * Button 3 - N/U
 * 
 * Knob 1 - Effect Level
 * Knob 2 - Decay
 * Knob 3 - Mix
 * 
 * LED 1 - N/U
 * LED 2 - N/U
 * LED 3 - N/U
 **********************************************/

// Pin renaming
static const int tapTempoButtonPin = effectButtonPin1;
static const int levelKnobPin = effectKnobPin1;
static const int decayKnobPin = effectKnobPin2;

// Constant parameters
static const int audioInChannel = 0;
static const int audioOutChannel = 0;
static const size_t delayMaxSize = 96000;

// Mutable parameters
static DelayLine<float, delayMaxSize> del_line;

// Tap tempo constants
static const long tapTempoDebounce = 300;

// Tap tempo mutables
static size_t tempoBpm = 90;
static unsigned long tapTempoTime = 0;
static TempoArray tempoArray;

// Decay constants
static const int decayKnobFlutter = 10;
static const int minDecayKnobValue = 0;
static const int maxDecayKnobValue = 1024;
static const float maxDecayValue = 0.75f;

// Decay mutables
static int decayKnobReading = 0;
static float decayValue = 0.5f;

// Level constants
static const int levelKnobFlutter = 10;
static const int minLevelKnobValue = 0;
static const int maxLevelKnobValue = 1024;
static const float maxLevelValue = 1.0f;

// Level mutables
static int levelKnobReading = 0;
static float levelValue = 0.5f;

// Function definitions
extern void MonoDelaySetup();
extern void MonoDelayCleanup();
extern void MonoDelayCallback(float **in, float **out, size_t size);
extern void MonoDelayLoop();

// "Internal" function definitions
void TapTempoLoopControl();
void DecayLoopControl();
void SetDecayValue(int knobReading);
void LevelLoopControl();
void SetLevelValue(int knobReading);

#endif