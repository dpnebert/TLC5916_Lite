/*
 * TLC5916_Lite.h
 *
 * Created: 5/9/2021 11:49:09 AM
 *  Author: Daniel Nebert
 *     Rev: 1.0.0
 */ 
  
#include "Arduino.h"

#ifndef TLC5916_LITE_H_
#define TLC5916_LITE_H_

#define ALL_ON      255
#define ALL_OFF     0

#define STSM_OE     29
#define STSM_LE     8

#define STNM_OE     29
#define STNM_LE     0

#define WCC_OE      255
#define WCC_LE      128
#define WCC_FULL_BRIGHT 255

#define DATA_NULL   0

#define PACKET_FULL   8
#define PACKET_MODE   5



class TLC5916_Lite
{
  public:
    TLC5916(uint8_t sdi, uint8_t clk, uint8_t oe, uint8_t le, uint8_t sdo);
    void transmit(uint8_t p, uint8_t c, bool l);
    void enableOutput();
    void disableOutput();
    void allOn(uint8_t n);
    void allOff(uint8_t n);
    
    void switchToSpecialMode();
    void switchToNormalMode();
    
    void writeConfiguration(uint8_t c);
    uint8_t readErrorCodeStatus();
    
  private:
    uint8_t readBits();
    void sendBits(uint8_t d, uint8_t o, uint8_t l, uint8_t c);
    void pulseLatch();
    void latchHigh();
    void latchLow();
    void generateErrorCodeStatus();

    uint8_t SDI;
    uint8_t CLK;
    uint8_t OE;
    uint8_t LE; 
    uint8_t SDO;   
  protected:
    
  
};




#endif /* TLC5916_LITE_H_ */