#include "DaisyDuino.h"
#include "Bypass/bypass.ino"
#include "MonoDelay/MonoDelay.ino"

// Global variables
DaisyHardware hw;
size_t num_channels;

void setup() {
    // Initialize Daisy at 96kHz
    hw = DAISY.init(DAISY_SEED, AUDIO_SR_96K);
    num_channels = hw.num_channels;

    // Initialize Bypass and start
    BypassSetup(num_channels);
    DAISY.begin(BypassCallback);

    // Initialize MonoDelay and start
    // MonoDelaySetup();
    // DAISY.begin(MonoDelayCallback);
}

void loop() {
}
