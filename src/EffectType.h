#ifndef EFFECT_TYPE_H
#define EFFECT_TYPE_H

// Effect type enum
enum EffectType {
    Bypass = 0,
    MonoDelay = 1,

    // Possible future effects
    DoubleDelay = 2,
    Fuzz = 3,

    Unset = 99
};

#endif