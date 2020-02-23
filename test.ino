#include <STM32_TM1637.h>

STM32_TM1637 tm(PB0,PB1);// CLK, DIO

float h=0.1;
byte p=1;

void setup(){
  Serial.begin(9600);   
  tm.brig(7); // ЯРКОСТЬ 0...7
}

void loop(){
   
   tm.print_float(h,p,  0,0,0,0); 
   delay(500);
  }

  /*
    
  tm.print_float(h,p,  h0,h1,h2,h3); 

  float h = -999...9999 | -0.99...0.999 | -9.99...99.99 | -99.9...999.9 
  byte p = 0...3 - число знаков после запятой
  
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
