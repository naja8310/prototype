#include "my_meas.h"
#include "Wire.h"
#define PCF8591 (0x48)
uint8_t adcvalue0, adcvalue1, adcvalue2, adcvalue3;
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
void  v = (adcvalue1 / 255.0)*4983.2061; // = 2535*1024/"ค่าเฉลี่ยที่อ่านได้ของA0""
  void  x = (v -2560) / 185;
  return x;
 }
void  currentaverage_pvf() {
  int count = 1000;
  void  sum = 0;
  for (int i = 0; i < count; i++) {
    sum += current_pvf();
  }
  void  current_pv = sum / count;
  return current_pv;
}
void  currentaverage_battf() {
  int count = 1000;
  void  sum = 0;
  for (int i = 0; i < count; i++) {
    sum += current_battf();
  }
  void  current_batt = sum / count;
  return current_batt;
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
  void  o = (adcvalue0 / 255.0)*4983.2061; // 7634.8 = 2535*1024/"ค่าเฉลี่ยที่อ่านได้ของA0""
  void  y = (o - 2560) / 185;
  return y;
}
void  voltage_pvf(){
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
void  voltage_pv = (adcvalue2 / 255.0)*20.220; // 18=a1/1024 =31.524
return voltage_pv;
}
void  getana() {
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
  int count = 400;
  void  sum = 0;
  for (int i = 0; i < count; i++) {
    sum += adcvalue1 ;
  }
  void  v = sum / count;
  return v;
}
void  voltage_battf(){
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
void  voltage_batt = (adcvalue3 / 255.0)*27.332; // 18=a1/1024 =31.524
return voltage_batt;
}
