#ifndef HWTEST_H
#define HWTEST_H

#include "DaisyDuino.h"
#include "../../include/IEffect.h"
#include "../../include/PedalConfig.h"
#include "../Inputs/Button.h"
#include "../Inputs/Knob.h"
#include "../Inputs/NFNToggle.h"

/**********************************************
 * HWTest Effect
 * 
 * SPST 1 - 
 * SPST 2 - 
 * SPST 3 - 
 * SPST 4 - 
 * 
 * SPDT 1 - 
 * SPDT 2 - 
 * 
 * Knob 1 - 
 * Knob 2 - 
 * Knob 3 - 
 * Knob 4 - 
 * 
 * LED 1 - 
 * LED 2 - 
 * LED 3 - 
 * LED 4 - 
 **********************************************/

class HWTest : public IEffect
{
public:
    void Setup(size_t pNumChannels);
    void Cleanup();
    void AudioCallback(float **in, float **out, size_t size);
    void Loop();
    String GetEffectName();

private:
    void Button3Interrupt();

    size_t numChannels;
    const int LED_MAX_VALUE = 256;
    const int LED_MIN_VALUE = 0;

    bool isLed3On = false;
    float led1Value = 0.0f;
    float led2Value = 0.0f;
    float volumeBoost = 1.0f;

    Button button1;
    Button button2;
    Button button3;

    Knob knob1;
    Knob knob2;
    Knob knob3;

    NFNToggle toggle;
};

#endif