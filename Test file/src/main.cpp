// RTC
#include "RTClib.h"
RTC_PCF8563 rtc;
String Date;
String Time;
// OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 oled (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const int buttonPin = 4;
int buttonState =0;
int screenPages =0;
// LoRa
#include <LoRa.h>
#include <SPI.h>
//Define LoRa
#define ss 32
#define rst 25
#define dio0 33
byte localAddress = 0xFB;
int recipient;
byte sender;
byte incomingLength;
//Define data struct
float temp_env;
float humid_env;
int light_env;
float temp_pv;
float voltage_pv;
float current_pv;
float voltage_batt;
float current_batt;

void setvalue(){
  voltage_pv =random(1,24);
  current_pv =random(1,5);
  voltage_batt =random(1,12);
  current_batt =random(1,5);
}
void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
  // Lora init
  Serial.println("LoRa Rx");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(915E6)) {
  Serial.println("Starting LoRa failed!");
  while (1);
  }
  // OLED init
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)){ // Address 0x3D for 128x64
  Serial.println(F("SSD1306 allocation failed"));
  while(1);
  }
  // RTC init
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
  if (rtc.lostPower()) {
    Serial.println("RTC is NOT initialized, let's set the time!");
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //set first time or reset time once compile
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2021, 10, 24, 4, 25, 0));
  }
  rtc.start();
 
}

void loop() {
  buttonState = digitalRead(buttonPin);
  DateTime now = rtc.now();
  Date = now.timestamp(DateTime::TIMESTAMP_DATE);
  Time = now.timestamp(DateTime::TIMESTAMP_TIME);
  //Serial.println(buttonState);
  if (buttonState == 1) {
    if (screenPages < 2) {
      screenPages = screenPages + 1;
    }
    else {
      screenPages = 0;
      }
    //delay a little to avoid bouncing
    delay(500);
    }
  if (screenPages == 0) {
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setTextSize(2);
    oled.setCursor(8,15);
    oled.print(Date);
    oled.setCursor(15,40);
    oled.print(Time);
    oled.display();
  }
  else if (screenPages == 1) {
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setTextSize(2);
    oled.setCursor(20,0);
    oled.println("Outdoor");
    oled.setTextSize(1);
    oled.setCursor(0,20);
    oled.print("Temperature: ");
    oled.println(temp_env);
    oled.setCursor(0,30);
    oled.print("Humidity: ");
    oled.println(humid_env);
    oled.setCursor(0,40);
    oled.print("Light Density: ");
    oled.println(light_env);
    oled.setCursor(0,50);
    oled.print("Temperature PV: ");
    oled.println(temp_pv);
    oled.display();
  }
  else if (screenPages == 2) {
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setTextSize(2);
    oled.setCursor(30,0);
    oled.println("Indoor");
    oled.setTextSize(1);
    oled.setCursor(0,20);
    oled.print("Voltage PV: ");
    oled.println(voltage_pv);
    oled.setCursor(0,30);
    oled.print("Current PV: ");
    oled.println(current_pv);
    oled.setCursor(0,40);
    oled.print("Voltage Battery: ");
    oled.println(voltage_batt);
    oled.setCursor(0,50);
    oled.print("Current Battery: ");
    oled.println(current_batt);
    oled.display();
  }
  // Lora Read Value
  int packetSize = LoRa.parsePacket ();
  String incoming = String(temp_env)+String(humid_env)+String(light_env)+String(temp_pv);
  if (packetSize==0) return;
  recipient=LoRa.read();
  sender = LoRa.read();
  incomingLength = LoRa.read();
  temp_env = LoRa.read();
  humid_env = LoRa.read();
  light_env = LoRa.read();
  temp_pv = LoRa.read();

  if (recipient != localAddress) {
    Serial.println("This message is not for me.");
    return;
  } //lora receive
  setvalue();
}