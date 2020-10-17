#ifndef PEDAL_CONFIG_H
#define PEDAL_CONFIG_H

#define DEBUG 1

#define initDebugPrint() {if(DEBUG) Serial.begin();}
#define debugPrint(msg) {if(DEBUG) Serial.println(msg);}

// Pin Definitions - Control App
const int hexSwitchPin1 = 0;
const int hexSwitchPin2 = 1;
const int hexSwitchPin4 = 2;
const int hexSwitchPin8 = 3;
const int controlLedPin = LED_BUILTIN; // Built in LED is LED_BUILTIN

// Pin Definitions - Effects
const int effectButtonPin1 = 27;
const int effectButtonPin2 = 28;
const int effectButtonPin3 = 29;
const int effectKnobPin1   = 21;
const int effectKnobPin2   = 20;
const int effectKnobPin3   = 19;
const int effectLedPin1    = 15;
const int effectLedPin2    = 16;
const int effectLedPin3    = 17;

#endif