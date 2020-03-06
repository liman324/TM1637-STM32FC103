#include <Wire.h>
#include <STM32_TM1637.h> // http://forum.rcl-radio.ru/misc.php?action=pan_download&item=403&download=1
#include <uRTCLib.h>//https://github.com/Naguissa/uRTCLib.git
   STM32_TM1637 tm(PB0,PB1);// CLK, DIO
   uRTCLib rtc(0x68);       
 
   // PB7 = SDA DS1307 (DS3231) 
   // PB6 = SCL DS1307 (DS3231)
   // PB0 = CLK TM1637
   // PB1 = DIO TM1637
 
float h;
int i;
 
void setup(){  
  tm.brig(7); // ЯРКОСТЬ 0...7
   Wire.begin();
  // rtc.set(30, 37, 23, 2, 17, 12, 19);
  // RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
}
 
void loop(){
   rtc.refresh();// опрос времни
   h = rtc.hour()*100 + rtc.minute();
   tm.print_time(h, 0);
   delay(500);
   tm.print_time(h, 1);
   delay(500);
i++;
if(i==10){i=0;tm.print_float(rtc.temp()/100,0 ,0b1111000,0,0,0);delay(2000);}// вывод температуры DS3231
    
  }
