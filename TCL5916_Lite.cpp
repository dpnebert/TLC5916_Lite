/*
 * TCL5916_Lite.c
 *
 * Created: 5/9/2021 11:49:09 AM
 *  Author: Daniel Nebert
 *     Rev: 1.0.0
 */ 

#include "TLC5916_Lite.h"

/*
 * Public methods
 * 
 * You can call these to do work for you
 */

TLC5916::TLC5916(uint8_t sdi, uint8_t clk, uint8_t oe, uint8_t le, uint8_t sdo) {
  SDI = sdi;
  CLK = clk;
  OE = oe;
  LE = le;
  SDO = sdo;
  
  pinMode(SDI, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LE, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(SDO, INPUT);

  digitalWrite(SDI, LOW);
  digitalWrite(CLK, LOW);
  digitalWrite(LE, LOW);
  digitalWrite(OE, HIGH);
}

void TLC5916::transmit(uint8_t p, uint8_t c, bool l) {
	sendBits(p, 0, 0, c);
	if(l) pulseLatch();
}

void TLC5916::enableOutput() {
	digitalWrite(OE, LOW);
}
void TLC5916::disableOutput() {
	digitalWrite(OE, HIGH);
}

void TLC5916::allOn(uint8_t n) {
	for(int i = 0; i < n - 1; i++) {
		transmit(ALL_ON, PACKET_FULL, false);
	}	
	transmit(ALL_ON, PACKET_FULL, true);
}
void TLC5916::allOff(uint8_t n) {
	
	for(int i = 0; i < n - 1; i++) {
		transmit(ALL_OFF, PACKET_FULL, false);
	}	
	transmit(ALL_OFF, PACKET_FULL, true);
}

void TLC5916::switchToSpecialMode() {
	sendBits(DATA_NULL, STSM_OE, STSM_LE, PACKET_MODE);
}

void TLC5916::switchToNormalMode() {	
	sendBits(DATA_NULL, STNM_OE, STNM_LE, PACKET_MODE);
}

void TLC5916::writeConfiguration(uint8_t c) {
	sendBits(c, WCC_OE, WCC_LE, PACKET_FULL);
}

uint8_t TLC5916::readErrorCodeStatus() {	
	uint8_t reading = 0;	
	generateErrorCodeStatus();
	digitalWrite(CLK, HIGH);
	disableOutput();
	if( digitalRead(SDO) ) {
		reading++;
	}
	digitalWrite(CLK, LOW);  
	for(uint8_t i = 0; i < 7; i++) {		
    reading = reading << 1;    
    digitalWrite(CLK, HIGH);    
		if(  digitalRead(SDO) ) {
			reading++;
		}
		digitalWrite(CLK, LOW);
	}
	return reading;
}


/*
 * Private methods
 * 
 * These methods are better left alone.  Should find all you need above.
 */

void TLC5916::sendBits(uint8_t d, uint8_t o, uint8_t l, uint8_t c) {
  uint8_t bitMask = 1;
  for(uint8_t i = 0; i < c; i++) {
  
    digitalWrite(SDI, (d & bitMask) > 0);
    digitalWrite(OE, (o & bitMask) > 0);
    digitalWrite(LE, (l & bitMask) > 0);
    bitMask = bitMask << 1;
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
  digitalWrite(SDI, LOW);
}

void TLC5916::pulseLatch() {
  digitalWrite(LE, HIGH);
  digitalWrite(LE, LOW);
}

void TLC5916::latchHigh() {
  digitalWrite(LE, HIGH);
}
void TLC5916::latchLow() {
  digitalWrite(LE, LOW);
}
void TLC5916::generateErrorCodeStatus() {
  sendBits(0, 1, 0, 8);
}
