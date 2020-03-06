#include <STM32_TM1637.h>

STM32_TM1637::STM32_TM1637(uint8_t clk, uint8_t dio){
         CLK = clk;
         DIO = dio;
};

void STM32_TM1637::brig(byte br){
     qwer = br + CODE0;
  }

void STM32_TM1637::del(){delayMicroseconds(100);}


void STM32_TM1637::dec(byte dig){
         for(int i = 0; i < 8; i++) {
           pinMode(CLK, OUTPUT);del();
         if (dig & 0x01)
           pinMode(DIO, INPUT);
         else
           pinMode(DIO, OUTPUT);del();
           pinMode(CLK, INPUT);del();
           dig = dig >> 1;
  }
           pinMode(CLK, OUTPUT);
           pinMode(DIO, INPUT);del();
           pinMode(CLK, INPUT);del();
           uint8_t ack = digitalRead(DIO);
         if (ack == 0)
           pinMode(DIO, OUTPUT);del();
           pinMode(CLK, OUTPUT);del();
  }
            
void STM32_TM1637::stop(){
           pinMode(DIO, OUTPUT);del();
           pinMode(CLK, INPUT);del();
           pinMode(DIO, INPUT);del();
  }  

void STM32_TM1637::start(){
           pinMode(DIO, OUTPUT);del();
  }

void STM32_TM1637::print_float(float decimal, byte pd,    byte h0, byte h1, byte h2, byte h3){
        start();dec(qwer);stop();start();dec(CODE1);stop();start();

        byte minus;
        int mn;
        
        switch(pd){
          case 0: mn = 1;break;
          case 1: mn = 10;break;
          case 2: mn = 100;break;
          case 3: mn = 1000;break;
          }
        
        if(decimal<0){decimal = abs(decimal); minus = 1;}else{minus = 0;}
        
        //if(decimal/1000>=1){pd = 0;}
        if(decimal/100>=1&&decimal/100<10){decimal = round(decimal*mn);}
        if(decimal/10>=1&&decimal/10<10){decimal = round(decimal*mn);}
        if(decimal>=0&&decimal<10){decimal = round(decimal*mn);}

        int data0 = (int)decimal/1000;
        int data1 = (int)decimal/100%10;
        int data2 = (int)decimal/10%10;
        int data3 = (int)decimal%10;
        
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
        
        if(minus==0){
        if(pd==3&&decimal<1000){data0 = 0b00111111;}
        if(pd==2&&decimal<100){data0 = 0b00000000;data1 = 0b00111111;}
        if(pd==2&&decimal<1000){data0 = 0b00000000;}
        if(pd==0&&decimal<10){data0 = 0b00000000;data1 = 0b00000000;data2 = 0b00000000;}
        if(pd==0&&decimal<100){data0 = 0b00000000;data1 = 0b00000000;}
        if(pd==0&&decimal<1000){data0 = 0b00000000;}
        if(pd==1&&decimal<1000){data0 = 0b00000000;}
        if(pd==1&&decimal<100){data0 = 0b00000000;data1 = 0b00000000;}
        if(pd==1&&decimal<10){data0 = 0b00000000;data1 = 0b00000000;data2 = 0b00111111;}
        if(decimal>9999){data0 = 0b01000000;data1 = 0b01000000;data2 = 0b01000000;data3 = 0b01000000;}
        }

        if(minus==1){
        if(pd==0&&decimal<10){data0 = 0b00000000;data1 = 0b00000000;data2 = 0b01000000;}
        if(pd==0&&decimal<100&&decimal>9){data0 = 0b00000000;data1 = 0b01000000;}
        if(pd==0&&decimal<1000&&decimal>99){data0 = 0b01000000;}
        if(pd==1&&decimal<100){data0 = 0b00000000;data1 = 0b01000000;}
        if(pd==1&&decimal<1000&&decimal>=100){data0 = 0b01000000;}
        if(pd==2&&decimal<1000){data0 = 0b01000000;}
        if(decimal>1000){data0 = 0b01000000;data1 = 0b01000000;data2 = 0b01000000;data3 = 0b01000000;}
        }
 
        switch(pd){
        case 1 : data2 = data2+0b10000000;break;
        case 2 : data1 = data1+0b10000000;break;
        case 3 : data0 = data0+0b10000000;break;
        }

        if(h0>0){data0 = h0;}
        if(h1>0){data1 = h1;}
        if(h2>0){data2 = h2;}
        if(h3>0){data3 = h3;}
        
        dec(ADDR0);dec(data0);dec(data1);dec(data2);dec(data3);stop();
    }

void STM32_TM1637::print_time(int t, byte pd_t){
        start();dec(qwer);stop();start();dec(CODE1);stop();start();
        
        int data0 = t/1000;
        int data1 = t/100%10;
        int data2 = t/10%10;
        int data3 = t%10;
        
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
        if(pd_t==1){data1=data1+0b10000000;}
        
        dec(ADDR0);dec(data0);dec(data1);dec(data2);dec(data3);stop();
}
