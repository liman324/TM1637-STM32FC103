#include <STM32_TM1637.h>

STM32_TM1637::STM32_TM1637(){};

void STM32_TM1637::brig(byte br){
     qwer = br + CODE0;
  }

void STM32_TM1637::dec(byte dig){
         for(int i = 0; i < 8; i++) {
           pinMode(CLK, OUTPUT);
           delayMicroseconds(100);
         if (dig & 0x01)
           pinMode(DIO, INPUT);
         else
           pinMode(DIO, OUTPUT);
           delayMicroseconds(100);
           pinMode(CLK, INPUT);
           delayMicroseconds(100);
           dig = dig >> 1;
  }
           pinMode(CLK, OUTPUT);
           pinMode(DIO, INPUT);
           delayMicroseconds(100);
           pinMode(CLK, INPUT);
           delayMicroseconds(100);
           uint8_t ack = digitalRead(DIO);
         if (ack == 0)
           pinMode(DIO, OUTPUT);
           delayMicroseconds(100);
           pinMode(CLK, OUTPUT);
           delayMicroseconds(100);
  }
            
void STM32_TM1637::stop(){
           pinMode(DIO, OUTPUT);
           delayMicroseconds(100);
           pinMode(CLK, INPUT);
           delayMicroseconds(100);
           pinMode(DIO, INPUT);
           delayMicroseconds(100);
  }  

void STM32_TM1637::start(){
           pinMode(DIO, OUTPUT);
           delayMicroseconds(100);
  }

void STM32_TM1637::print_dec(int decimal, int pd,    int h0, int h1, int h2, int h3){
        start();dec(qwer);stop();start();dec(CODE1);stop();start();
      
        if(decimal<0){decimal = abs(decimal);if(pd>9){pd = pd - 10;}}
        int data0 = decimal/1000;
        int data1 = decimal/100%10;
        int data2 = decimal/10%10;
        int data3 = decimal%10;
        
        for(int n=0;n<4;n++){
        int data;
        if(n==0){data=data0;}
        if(n==1){data=data1;}
        if(n==2){data=data2;}
        if(n==3){data=data3;}
              
        switch(data){  // XGFEDCBA
        case 0:  data = 0b00111111;break;     // 0
        case 1:  data = 0b00000110;break;     // 1
        case 2:  data = 0b01011011;break;     // 2
        case 3:  data = 0b01001111;break;     // 3
        case 4:  data = 0b01100110;break;     // 4
        case 5:  data = 0b01101101;break;     // 5
        case 6:  data = 0b01111101;break;     // 6
        case 7:  data = 0b00000111;break;     // 7
        case 8:  data = 0b01111111;break;     // 8
        case 9:  data = 0b01101111;break;     // 9
        }
              
        if(n==0){data0=data;}
        if(n==1){data1=data;}
        if(n==2){data2=data;}
        if(n==3){data3=data;}
        }
        
        byte w;
        if(pd>9){pd = pd -10;w=0b00111111;}else{w=0b00000000;}
        if(decimal<1000&&decimal>99){data0 = w;}
        if(decimal<100&&decimal>9){data0 = w;data1 = w;}
        if(decimal<10){data0 = w; data1 = w; data2 = w;}
        
        switch(pd){
        case 0 : data0;data1;data2;data3;break;
        case 1 : data2 = data2+0b10000000;break;
        case 2 : data1 = data1+0b10000000;break;
        case 3 : data0 = data0+0b10000000;break;
        }
        
        if(h0>-1){data0 = h0;}
        if(h1>-1){data1 = h1;}
        if(h2>-1){data2 = h2;}
        if(h3>-1){data3 = h3;}
        
        dec(ADDR0);dec(data0);dec(data1);dec(data2);dec(data3);stop();
    }
