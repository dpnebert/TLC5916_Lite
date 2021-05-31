/*
 * TCL5916 Lite Driver
 * 
 * Example: Binary Counter Demo
 *
 * Created: 5/9/2021 11:49:09 AM
 *  Author: Daniel Nebert
 *  Documentation: http://www.danielnebert.com/tlc5916-lite-arduino-driver-library/
 */ 




#include "TLC5916_Lite.h"

#define SDI       5
#define CLK       4
#define LE        3
#define SDO       9
#define OE        8

TLC5916_Lite tlc = TLC5916_Lite(SDI, CLK, OE, LE, SDO);

uint8_t count;

void setup() {

  count = 0;
    
  tlc.switchToNormalMode();
  tlc.allOn(1);
  tlc.enableOutput();
  delay(3000);
}

void loop() {
  tlc.transmit(count++, 8, true);
  delay(500);
}
