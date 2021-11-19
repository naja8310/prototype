#include <LoRa.h>
#include <SPI.h>
#include <AM232X.h>
#include <BH1750FVI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 17 
// dsb pin
#define ss 32
#define rst 25
#define dio0 33
// define LoRa

AM232X AM2322;
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature PVtemperature(&oneWire);
byte localAddress = 0xFA;
byte destination = 0xFB;

float temp_env;
float humid_env;
int light_env;
float temp_pv;

void setdata(){
temp_env =random(30,40);
humid_env =random(1,100);
light_env =random(0,65535);
temp_pv =random(30,40);
Serial.print("AirTemperature = ");
Serial.println(temp_env);
Serial.print("AirHumidity = ");
Serial.println(humid_env);
Serial.print("Light = ");
Serial.println(light_env);
Serial.print("PV Temperature = ");;
Serial.println(temp_pv);
}

void setup(){
Serial.begin(115200);
setdata();
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
