#include "Wire.h"
#include <Arduino.h>
#define PCF8591 (0x48)
uint8_t adcvalue0, adcvalue1, adcvalue2, adcvalue3;
float voltage_pv;
void  voltage_pvf(){
Wire.begin();
Wire.beginTransmission(PCF8591);
Wire.write(0x04);
Wire.endTransmission();
Wire.requestFrom(PCF8591,5);
adcvalue0=Wire.read();
adcvalue0=Wire.read(); //CurentSolar
adcvalue1=Wire.read(); //voltageSolar
adcvalue2=Wire.read(); //voltagebatt
adcvalue3=Wire.read(); //Currentbatt
voltage_pv = (adcvalue2 / 255.0)*20.220; // 18=a1/1024 =31.524
return;
}
void setup(){
  Serial.begin(115200);
}
void loop ()
{
voltage_pvf();
Serial.println(voltage_pv);
delay(5000);
}
