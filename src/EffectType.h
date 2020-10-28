#ifndef EFFECT_TYPE_H
#define EFFECT_TYPE_H

/**
 * The rotary encoder is using Gray code, not standard hex.
 * The sequence of decimal numbers that it produces is as follows:
 * 0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 15, 14, 10, 11, 9, 8
 */

// Effect type enum
enum EffectType {
    Bypass1 = 0,
    MonoDelay1 = 1,

    // Possible future effects
    DoubleDelay = 3,
    Fuzz = 2,

    Unset = 99
};

#endif