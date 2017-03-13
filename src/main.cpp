// Very basic Spiffs example, writing 10 strings to SPIFFS filesystem, and then read them back
// For SPIFFS doc see : https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md
// Compiled in Arduino 1.6.7. Runs OK on Wemos D1 ESP8266 board.
#include <arduino.h>
#include "FS.h"

String W_SSID,W_PASS,W_MQTT;

void setup() {
  Serial.begin(9600);
  Serial.println("\nVery basic Spiffs example, writing 10 lines to SPIFFS filesystem, and then read them back");
  bool ok = SPIFFS.begin();
  if (ok) {
    Serial.println("ok");
  }
  bool exist = SPIFFS.exists("/wific.txt");
  if (exist) {
    Serial.println("wific.txt found!");
  }
  // Next lines have to be done ONLY ONCE!!!!!When SPIFFS is formatted ONCE you can comment these lines out!!
  //Serial.println("Please wait 30 secs for SPIFFS to be formatted");
  //SPIFFS.format();
  //Serial.println("Spiffs formatted");
}

void Save_Wifi_Info(String SSID, String Password, String MQTT_Address)
{
  File f = SPIFFS.open("/wific.txt", "w");
  if (!f) {
      Serial.println("file open failed for write");
    }
    f.println(SSID);
    f.println(Password);
    f.println(MQTT_Address);
    f.close();
}

void Load_Wifi_Info(void)
{
  File f = SPIFFS.open("/wific.txt", "r");
  if (!f) {
      Serial.println("file open failed");
  }
  W_SSID = f.readStringUntil('\n');
  W_PASS = f.readStringUntil('\n');
  W_MQTT = f.readStringUntil('\n');
  //f.close();
}


void loop() {
// Save_Wifi_Info("TestAP", "TestPass", "TestMQTT");
 Load_Wifi_Info();
 Serial.println(W_SSID);
 Serial.println(W_PASS);
 Serial.println(W_MQTT);

 FSInfo fs_info;
 SPIFFS.info(fs_info);
 Serial.print("Total Size: ");Serial.println(fs_info.totalBytes);
 Serial.print("Used Size: ");Serial.println(fs_info.usedBytes);
  // wait a few seconds before doing it all over again
  delay(3000);

}
