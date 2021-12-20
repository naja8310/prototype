#include "my_meas.h"
#include "Wire.h"
#define PCF8591 (0x48)
uint8_t adcvalue0, adcvalue1, adcvalue2, adcvalue3;
float  getCSolar(){
 Wire.begin();
 Wire.beginTransmission(PCF8591);
 Wire.write(0x04);
 Wire.endTransmission();
 Wire.requestFrom(PCF8591,5);
 adcvalue0=Wire.read();
 adcvalue0=Wire.read(); //CurrentSolar
 adcvalue1=Wire.read(); //voltageSolar
 adcvalue2=Wire.read(); //voltagebatt
 adcvalue3=Wire.read(); //Currentbatt
float  v = (adcvalue1 / 255.0)*4912.2093; // 7634.8 = 2535*1024/"ค่าเฉลี่ยที่อ่านได้ของA0""
  float  c = (v - 2485) / 185;
  return c;
 }
float  getCASolar() {
  int count = 1000;
  float  sum = 0;
  for (int i = 0; i < count; i++) {
    sum += getCSolar();
  }
  float  val = sum / count;
  return val;
}
float  getCABat() {
  int count = 1000;
  float  sum = 0;
  for (int i = 0; i < count; i++) {
    sum += getCBat();
  }
  float  val1 = sum / count;
  return val1;
}
float  getCBat() {
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
  float  o = (adcvalue0 / 255.0)* 7657.3451; // 7634.8 = 2535*1024/"ค่าเฉลี่ยที่อ่านได้ของA0""
  float  p = (o - 2535) / 185;
  return p;
}
float  getVolSolar(){
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
float  Solar = (adcvalue2 / 255.0)*21.2681; // 18=a1/1024 =31.524
return Solar;
}
float  getana() {
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
  float  sum = 0;
  for (int i = 0; i < count; i++) {
    sum += adcvalue1 ;
  }
  float  v = sum / count;
  return v;
}
float  getVolBat(){
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
float  Y = (adcvalue3 / 255.0)*29.1768; // 18=a1/1024 =31.524
return Y;
}
