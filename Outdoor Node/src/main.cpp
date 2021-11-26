#include <LoRa.h>
#include <SPI.h>
#include <AM232X.h>
#include <BH1750FVI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4 
// dsb pin
#define ss 32
#define rst 25
#define dio0 33
// define LoRa

AM232X AM2320;
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature PVtemperature(&oneWire);
byte localAddress = 0xFA;
byte destination = 0xFB;

float temp_env;
float humid_env;
int light_env;
float temp_pv;

void pv_temp(){
PVtemperature.begin(); 
PVtemperature.requestTemperatures(); 
Serial.print("PV Temperature = ");
Serial.print(PVtemperature.getTempCByIndex(0));
Serial.println(" C");
}
void env_light(){
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

void setup(){
Serial.begin(115200);
pv_temp();
env_light();
readAirHumidity();
readAirTemperature();
delay(100);
Serial.println("LoRa Tx");
LoRa.setPins(ss, rst, dio0);  
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
}
String outgoing = String(temp_env)+String(humid_env)+String(light_env)+String(temp_pv);
LoRa.beginPacket();
LoRa.write(destination);
LoRa.write(localAddress);
LoRa.write(outgoing.length());
LoRa.write(temp_env);
LoRa.write(humid_env);
LoRa.write(light_env);
LoRa.write(temp_pv);
LoRa.endPacket();
Serial.println("Sent");
esp_sleep_enable_timer_wakeup(10e6); //10sec
esp_deep_sleep_start();
}

void loop (){
}
