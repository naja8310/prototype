// Firebase 
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#define API_KEY "AIzaSyBhcFEpWcPHmzXkyXMa6vN6OExju50fMwk"
#define DATABASE_URL "solardash-7e30b-default-rtdb.asia-southeast1.firebasedatabase.app"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
#define user_email "admin@solar.com"
#define user_pass "admin12345"
// autoconnect wifi manager
#include <WebServer.h>     
#include <AutoConnect.h>
WebServer Server;          
AutoConnect Portal(Server);
#define led 2
// LoRa
#include <LoRa.h>
#include <SPI.h>
const int ss = 32;
#define rst 25
#define dio0 33
String incoming;
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
// SD card
#include "FS.h"
#include "SD.h"
#define SD_CS 5
String dataMessage;
//Define data struct
float temp_env;
float humid_env;
int light_env;
float temp_pv;
float voltage_pv;
float current_pv;
float voltage_batt;
float current_batt;
void rootPage() {
  char content[] = "Wifi Connected nothing to do here";
  Server.send(200, "text/plain", content);
}
// Write to the SD card (DON'T MODIFY THIS FUNCTION)
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}
// Append data to the SD card (DON'T MODIFY THIS FUNCTION)
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}
void logSDCard() {
  dataMessage = String(Date) + "," + String(Time) + "," + String(temp_env) + "," + String(humid_env) + "," + 
                String(light_env) + "," + String(temp_pv) + "," + String(voltage_pv) + "," + 
                String(current_pv) + "," + String(voltage_batt) + "," + String(current_batt) + "\r\n";
  Serial.print("Save data: ");
  Serial.println(dataMessage);
  appendFile(SD, "/logs.csv", dataMessage.c_str());
}
void setup(){
  Serial.begin(115200);
  buttonState = digitalRead(buttonPin);
  pinMode(led,OUTPUT);
  pinMode(buttonPin, INPUT);
  if (buttonState == 1) {
    Server.on("/", rootPage);
  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
    }
  }
   if (WiFi.status() == WL_CONNECTED){
    digitalWrite(led,HIGH);
  }
// Lora init
  Serial.println("LoRa Rx");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(915E6)) {
  Serial.println("Starting LoRa failed!");
  while (1);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
// RTC init 
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    abort();
  }
  if (rtc.lostPower()) {
    Serial.println("RTC is NOT initialized, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //set first time or reset time once compile
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2021, 10, 24, 4, 25, 0));
  }
  rtc.start();
// OlED init 
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)){ // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    while(1);
  }
// SD init
  SD.begin(SD_CS);  
  if(!SD.begin(SD_CS)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }
  Serial.println("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("ERROR - SD card initialization failed!");
    return;    // init failed
  }
  // If the logs.txt file doesn't exist Create a file on the SD card and write the data labels
  File file = SD.open("/logs.csv");
  if(!file) {
    Serial.println("File doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/logs.csv", "Date, Time, Temperature Env, Humidity Env, Light Env, Temperature PV, Voltage PV, Current PV, Voltage Battery, Current Battery\r\n");
  }
  else {
    Serial.println("File already exists");  
  }
  file.close();
// Firebase init
  /* Assign the api key (required) */
  config.api_key = API_KEY;
  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;
  //auth Firebase
  auth.user.email = user_email;
  auth.user.password = user_pass;
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}
void loop(){
  buttonState = digitalRead(buttonPin);
  Portal.handleClient();
  DateTime now = rtc.now();
  Date = now.timestamp(DateTime::TIMESTAMP_DATE);
  Time = now.timestamp(DateTime::TIMESTAMP_TIME);
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
    oled.print("Voltage Battery:");
    oled.println(voltage_batt);
    oled.setCursor(0,50);
    oled.print("Current Battery:");
    oled.println(current_batt);
    oled.display();
  }
  // Lora Read Value
  int packetSize = LoRa.parsePacket ();
  if (packetSize==0) return;
  temp_env = LoRa.read();
  humid_env = LoRa.read();
  light_env = LoRa.read();
  temp_pv = LoRa.read();
  incoming = String(temp_env)+String(humid_env)+String(light_env)+String(temp_pv);
  if ((millis() - sendDataPrevMillis > 60000 || sendDataPrevMillis == 0)){ //sent data to server if new packet come in
  sendDataPrevMillis = millis();
  logSDCard();
  Firebase.RTDB.setFloat(&fbdo,"outdoor/temp_env",temp_env);
  Firebase.RTDB.setFloat(&fbdo,"outdoor/humid_env",humid_env);
  Firebase.RTDB.setInt(&fbdo,"outdoor/light_env",light_env);
  Firebase.RTDB.setFloat(&fbdo,"outdoor/temp_pv",temp_pv);
  Firebase.RTDB.setFloat(&fbdo,"indoor/voltage_pv",voltage_pv);
  Firebase.RTDB.setFloat(&fbdo,"indoor/current_pv",current_pv);
  Firebase.RTDB.setFloat(&fbdo,"indoor/voltage_batt",voltage_batt);
  Firebase.RTDB.setFloat(&fbdo,"indoor/current_batt",current_batt);
  Firebase.RTDB.setString(&fbdo,"timestamp/date",now.timestamp(DateTime::TIMESTAMP_DATE));
  Firebase.RTDB.setString(&fbdo,"timestamp/time",now.timestamp(DateTime::TIMESTAMP_TIME));
  }
}

