#ifndef PEDAL_CONFIG_H
#define PEDAL_CONFIG_H

#define DEBUG 1

#define initDebugPrint() {if(DEBUG) Serial.begin();}
#define debugPrint(msg) {if(DEBUG) Serial.println(msg);}

#endif