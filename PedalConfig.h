#ifndef PEDAL_CONFIG_H
#define PEDAL_CONFIG_H

#define DEBUG 1

#define initDebugPrint() {if(DEBUG) Serial.begin();}
#define debugPrint(msg) {if(DEBUG) Serial.println(msg);}

const int controlLedPin = LED_BUILTIN; // Built in LED is LED_BUILTIN

// Pin Definitions - Selector
const int effectSelectorPin1 = 0;
const int effectSelectorPin2 = 1;
const int effectSelectorPin3 = 2;
const int effectSelectorPin4 = 3;

// Pin Definitions - SPST
const int effectButtonPin1 = 27;
const int effectButtonPin2 = 28;
const int effectButtonPin3 = 29;
const int effectButtonPin4 = -1;

// Pin Definitions - SPDT
const int effectSPDT1Pin1 = -1;
const int effectSPDT1Pin2 = -1;
const int effectSPDT2Pin1 = -1;
const int effectSPDT2Pin2 = -1;

// Pin Definitions - POT
const int effectKnobPin1   = 21;
const int effectKnobPin2   = 20;
const int effectKnobPin3   = 19;
const int effectKnobPin4   = -1;

// Pin Definitions - LED
const int effectLedPin1    = 15;
const int effectLedPin2    = 16;
const int effectLedPin3    = 17;
const int effectLedPin4    = -1;

#endif