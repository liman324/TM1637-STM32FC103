//  STM32_TM1637 v1.1
//  Alexander Liman
//  liman324@yandex.ru
//  rcl-radio.ru

#ifndef  STM32_TM1637_H
#define  STM32_TM1637_H

#include <Arduino.h>

#define CLK      PB0
#define DIO      PB1
#define CODE0    0b10001000
#define CODE1    0x40
#define ADDR0    0xC0

class  STM32_TM1637
{
  public:
     STM32_TM1637();
     
void print_dec(int decimal, int pd, int h0, int h1, int h2, int h3);
void brig(byte br);
  
  private:
  
void dec(byte dig);
void stop();
void start();
byte qwer;
};
#endif
