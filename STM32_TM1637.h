//  STM32_TM1637 v2.0
//  Alexander Liman
//  liman324@yandex.ru
//  rcl-radio.ru

#ifndef  STM32_TM1637_H
#define  STM32_TM1637_H

#include <Arduino.h>

#define CODE0    0b10001000
#define CODE1    0x40
#define ADDR0    0xC0

class  STM32_TM1637
  {
    public:

  STM32_TM1637(uint8_t, uint8_t);
  void print_float(float decimal, byte pd,      byte h0, byte h1, byte h2, byte h3);
  void print_time(int t, byte pd_t); 
  void brig(byte br);
  
    private:
  
  void dec(byte dig);
  void stop();
  void start();
  void del();
  byte qwer;
  uint8_t DIO;
  uint8_t CLK;
  };
#endif
