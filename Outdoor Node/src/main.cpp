// Library
#include <LoRa.h>
#include <SPI.h>
#include <AM232X.h>
#include <BH1750FVI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
// PV temp DSB Pin
#define ONE_WIRE_BUS 4 
// LoRa Pin
#define ss 32
#define rst 25
#define dio0 33
AM232X AM2320;
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature PVtemperature(&oneWire);
float temp_env;
float humid_env;
int light_env;
float temp_pv;
void pv_temp(){
PVtemperature.begin(); 
PVtemperature.requestTemperatures(); 
temp_pv = PVtemperature.getTempCByIndex(0);
Serial.print("PV Temperature = ");
Serial.print(temp_pv);
Serial.println(" C");
}
void env_light(){
LightSensor.begin();
light_env =LightSensor.GetLightIntensity(); 
Serial.print("Light = ");
Serial.print(light_env);
Serial.println(" Lux");  
}
void env_tempNhumid(){
 AM2320.begin();
 temp_env = AM2320.getTemperature(),2;
 humid_env = AM2320.getHumidity(),2;
 Serial.print("AirTemperature = ");
 Serial.print(temp_env);
 Serial.println(" C");
 Serial.print("AirHumidity = ");
 Serial.print(humid_env);
 Serial.println(" %");
}
void setup(){
Serial.begin(115200);
AM2320.begin();
pv_temp();
env_light();
env_tempNhumid();
Serial.println("LoRa Tx");
LoRa.setPins(ss, rst, dio0);  
if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
}
LoRa.setSyncWord(0xA5);
Serial.println("LoRa Initializing OK!");
String outgoing = String(temp_env)+String(humid_env)+String(light_env)+String(temp_pv);
LoRa.beginPacket();
LoRa.write(temp_env);
LoRa.write(humid_env);
LoRa.write(light_env);
LoRa.write(temp_pv);
LoRa.endPacket();
Serial.println("Sent");
esp_sleep_enable_timer_wakeup(300e6); //10sec
esp_deep_sleep_start();
}
void loop (){
}
