/*
 * TCL5916 Lite Driver
 * 
 * Example: Current Gain Demo
 *
 * Created: 5/9/2021 11:49:09 AM
 *  Author: Daniel Nebert
 *  Documentation: http://www.danielnebert.com/tlc5916-lite-arduino-driver-library/
 */ 

#include "TLC5916.h"
#define SDI       5
#define CLK       4
#define LE        3
#define SDO       9
#define OE        8

TLC5916 tlc = TLC5916(SDI, CLK, OE, LE, SDO);
uint8_t brightness;
void setup() {
  brightness = 255;
}

void loop() {
  tlc.switchToSpecialMode();
  tlc.writeConfiguration(brightness);
  if(brightness == 255) {
    brightness = 0;
  } else {
    brightness = 255;
  }
  tlc.switchToNormalMode();
  tlc.allOn(1);
  tlc.enableOutput();
  delay(1000);
}
