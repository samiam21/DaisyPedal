#ifndef EFFECT_TYPE_H
#define EFFECT_TYPE_H

#include "DaisyDuino.h"
#include "IEffect.h"
#include "../lib/HWTest/HWTest.h"
#include "../lib/ButtonTest/ButtonTest.h"
#include "../lib/KnobTest/KnobTest.h"
#include "../lib/SimpleBypass/SimpleBypass.h"

// Effect Objects
HWTest hwTest;
ButtonTest buttonTest;
KnobTest knobTest;
SimpleBypass simpleBypass;

/**
 * The rotary encoder is using Gray code, not standard hex.
 * The sequence of decimal numbers that it produces is as follows:
 * 0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 15, 14, 10, 11, 9, 8
 */
enum EffectType
{
    HWTEST = 0,
    BUTTONTEST = 1,
    KNOBTEST = 3,
    SIMPLEBYPASS = 2,

    // Add effect types here

    UNSET = 99
};

/**
 * Returns the effect object based on the passed in enum
 */
extern IEffect *GetEffectObject(EffectType type)
{
    switch (type)
    {
    case HWTEST:
        return (IEffect *)&hwTest;
    case BUTTONTEST:
        return (IEffect *)&buttonTest;
    case KNOBTEST:
        return (IEffect *)&knobTest;
    case SIMPLEBYPASS:
    case UNSET:
    default:
        return (IEffect *)&simpleBypass;
    }
};

#endif