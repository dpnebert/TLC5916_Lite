/*
 * TCL5916 Lite Driver
 * 
 * Example: Open Circuit Error Detection Demo
 *
 * Created: 5/9/2021 11:49:09 AM
 *  Author: Daniel Nebert
 *  Documentation: http://www.danielnebert.com/TLC5916_Lite-lite-arduino-driver-library/
 */ 

#include "TLC5916_Lite.h"

#define SDI       5
#define CLK       4
#define LE        3
#define SDO       9
#define OE        8

TLC5916_Lite tlc = TLC5916_Lite(SDI, CLK, OE, LE, SDO);

void setup() {
  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  tlc.switchToSpecialMode();
  uint8_t reading = tlc.readErrorCodeStatus();

  Serial.println(reading);

  tlc.switchToNormalMode();    
  tlc.enableOutput();
  tlc.allOn(1);
  
  delay(10);
}
