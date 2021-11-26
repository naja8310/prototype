#include <AM232X.h>
#include <BH1750FVI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4   //กำหนดขาที่จะเชื่อมต่อ Sensor 

AM232X AM2320;
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature PVtemperature(&oneWire);
void ds18b20(){
 PVtemperature.begin(); 
 PVtemperature.requestTemperatures(); 
 Serial.print("PV Temperature = ");
 Serial.print(PVtemperature.getTempCByIndex(0));
 Serial.println(" C");
}
void BH1750(){
 LightSensor.begin();
 uint16_t lux = LightSensor.GetLightIntensity(); 
 Serial.print("Light = ");
 Serial.print(lux);
 Serial.println(" Lux");
}
void readAirHumidity(){
 AM2320.begin();
 Serial.print("AirHumidity = ");
 Serial.print(AM2320.getHumidity(),2);
 Serial.println(" %");
}
void readAirTemperature(){
 AM2320.begin();
 Serial.print("AirTemperature = ");
 Serial.print(AM2320.getTemperature(),2);
 Serial.println(" C");
}
void setup() {
   Serial.begin(115200);
   //LightSensor.begin();
   //AM2320.begin();
   //PVtemperature.begin(); 
}
void loop() {
 readAirHumidity();
 readAirTemperature();
 BH1750();
 ds18b20();
 Serial.println("**********************************");
 delay(3000);
}