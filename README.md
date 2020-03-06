# TM1637-STM32FC103
STM32 + TM1637 (Arduino)
Автор: Александр Лиман
liman324@yandex.ru
Описание библиотеки и примеры - https://rcl-radio.ru/?p=75892


#include <STM32_TM1637.h>

STM32_TM1637 tm(CLK, DIO);

void setup(){
tm.brig(7); // ЯРКОСТЬ 0...7
}

void loop(){
 // вывод времени или int
 tm.print_time(int, pd); // int 0...9999 pd 0...1 (двоеточие)
 // вывод float
 tm.print_float(h,p,  h0,h1,h2,h3); 
 
/*  ВЫВОД FLOAT
  float h = -999...9999 | 0.000...0.999 | -9.99...99.99 | -99.9...999.9 
  byte p = 0...3 - число знаков после запятой
  h0,h1,h2,h3 = 0 - неактивно
  
      A
     ---
  F |   | B
     -G-
  E |   | C
     ---
      D

 h0 h1 h2 h3 
 -----------
   XGFEDCBA (X - запятая)
 0b00000000 
 */
 }
