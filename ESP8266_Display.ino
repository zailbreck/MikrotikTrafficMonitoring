#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <Wire.h>  
#include "SSD1306Wire.h" 

//Set SSID and Wifi Password
#ifndef STASSID
#define STASSID "SSID"
#define STAPSK  "PASS"
#endif

SSD1306Wire  display(0x3c, D3, D5);
// D3 -> SDA
// D5 -> SCL
const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "<PROJECT-ID>.firebaseio.com"; //Firebase Url
const int httpsPort = 443; //https Port

const char fingerprint[] PROGMEM = "03 D6 42 23 03 D1 0C 06 73 F7 E2 BD 29 47 13 C3 22 71 37 1B"; //Fingerprint Firebase.io


void setup() {
  Serial.begin(115200);

  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  

  display.init();
}

//Show Display
void displayShow(String rx,String tx,String tRx,String tTx){
    display.clear();
    display.flipScreenVertically();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(10, 0, "Mikrotik Traffic");
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 15, "Download : "+rx);
    display.drawString(0, 25, "Upload : "+tx);
    display.drawString(0, 35, "Total Down : "+tTx);
    display.drawString(0, 45, "Total Up : "+tRx);
    
    display.display();
    delay(50);
}
float valueX[4];
float value;
String sizeW;

//Function to Convert byte to K, M, G byte
String getsize(float value){
  if (value > 1023)
  {
    value /= 1024.00;
    sizeW = String(" KB");
    if(value > 1023){
      value /= 1024.00;
      sizeW = String(" MB");
      if(value > 1023){
        value /= 1024.00;
      sizeW = String(" GB");
      }
    }
  }
  return String(value) + sizeW;
}

void loop() {
  WiFiClientSecure client;
  client.setFingerprint(fingerprint);
  
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  //Select Device
  String url = "/Mikrotik/Device_1.json";

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  //Check Client Connection
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println();
      break;
    }
  }
  String line = client.readStringUntil('\n');

  //Decode Json to Array
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(line);

  valueX[0] = root["RealDownload"]; //bit
  valueX[1] = root["RealUpload"];   //bit
  valueX[2] = root["TotalDownload"];//byte
  valueX[3] = root["TotalUpload"];  //byte

  //Some data is bit , so just divide 8 before
  displayShow(getsize(valueX[0]/8),getsize(valueX[1]/8),getsize(valueX[2]),getsize(valueX[3]));
}
