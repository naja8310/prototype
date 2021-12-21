#include "my_meas.h"
#include "Wire.h"
#define PCF8591 (0x48)
uint8_t adcvalue0, adcvalue1, adcvalue2, adcvalue3;
float x,y;
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
float voltage_pv = (adcvalue2 / 255.0)*20.220; // 18=a1/1024 =31.524
return ;
}
void  voltage_battf(){
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
float voltage_batt = (adcvalue3 / 255.0)*27.332; // 18=a1/1024 =31.524
return;
}
void  current_pvf(){
Wire.begin();
Wire.beginTransmission(PCF8591);
Wire.write(0x04);
Wire.endTransmission();
Wire.requestFrom(PCF8591,5);
adcvalue0=Wire.read();
adcvalue0=Wire.read(); //CuurentSolar
adcvalue1=Wire.read(); //voltageSolra
adcvalue2=Wire.read(); //vlotagebatt
adcvalue3=Wire.read(); //Currentbatt
float  voltCurrent = (adcvalue1 / 255.0)*4983.2061; // = 2535*1024/"ค่าเฉลี่ยที่อ่านได้ของA0""
float  calculatedCurrent = (v -2560) / 185;
return;
}
void  currentaverage_pvf() {
int count = 1000;
float  sum = 0;
for (int i = 0; i < count; i++) {
  sum += calculatedCurrent;
}
float  current_pv = sum / count;
return;
}
void  current_battf() {
Wire.begin();
Wire.beginTransmission(PCF8591);
Wire.write(0x04);
Wire.endTransmission();
Wire.requestFrom(PCF8591,5);
adcvalue0=Wire.read();
adcvalue0=Wire.read(); //CuurentSolar
adcvalue1=Wire.read(); //voltageSolra 
adcvalue2=Wire.read(); //vlotagebatt
adcvalue3=Wire.read(); //Currentbatt
float  voltCurrentBatt = (adcvalue0 / 255.0)*4983.2061; // 7634.8 = 2535*1024/"ค่าเฉลี่ยที่อ่านได้ของA0""
float  calculatedCurrentBatt = (o - 2560) / 185;
return;
}
void  currentaverage_battf() {
int count = 1000;
float  sum2 = 0;
for (int i = 0; i < count; i++) {
  sum2 += calculatedCurrentBatt;
}
 float  current_batt = sum2 / count;
 return;
}
