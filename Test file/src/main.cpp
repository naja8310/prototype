// LoRa
#include <LoRa.h>
#include <SPI.h>
//Define LoRa
#define ss 32
#define rst 25
#define dio0 33
byte localAddress = 0xFB;
int recipient;
String incoming;
byte sender;
byte incomingLength;
//Define data struct
float temp_env;
float humid_env;
int light_env;
float temp_pv;

void setup(){
  Serial.begin(115200);

// Lora init
  Serial.println("LoRa Rx");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(915E6)) {
  Serial.println("Starting LoRa failed!");
  while (1);
  }
}
void loop(){
  // Lora Read Value
  int packetSize = LoRa.parsePacket ();
  if (packetSize==0) return;
  recipient=LoRa.read();
  sender = LoRa.read();
  incomingLength = LoRa.read();
  temp_env = LoRa.read();
  humid_env = LoRa.read();
  light_env = LoRa.read();
  temp_pv = LoRa.read();
  incoming = String(temp_env)+String(humid_env)+String(light_env)+String(temp_pv);
  if (recipient != localAddress) {
    Serial.println("This message is not for me.");
    return;
  } 
  Serial.println(temp_env);
  Serial.println(humid_env);
  Serial.println(light_env);
  Serial.println(temp_pv);
}
