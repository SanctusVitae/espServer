#ifndef FILES_H
#define FILES_H

#include <FS.h>
#include <ArduinoJson.h>
#include <Arduino.h>
/*
class fileManage {
  String ssid;
  String pass;
  public:
    fileManage(String Ssid, String Pass);
    void fileSave();
    bool fileRead();
};

fileManage::fileManage(String Ssid, String Pass) {
  SPIFFS.begin();
  ssid = Ssid;
  pass = Pass;
}

void fileManage::fileSave() {
  StaticJsonDocument<200> json;
  json["ssid"] = ssid;
  json["pass"] = pass;
  
  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    return;
  }
  serializeJson(json, configFile);
  configFile.close();
}

bool fileManage::fileRead() {
  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    return false;
  }
  
  size_t size = configFile.size();

  char *buf = new char[size];
  
  configFile.readBytes(buf, size);
  
  DynamicJsonDocument json(200);
  DeserializationError error = deserializeJson(json, buf);
  
  if (error) {
    delete buf;
    return false;
  }

  String ssid2 = json["ssid"];
  String pass2 = json["pass"];

  Serial.println("Read from file");
  Serial.println(ssid2);
  Serial.println(pass2);
  
  configFile.close();
  return true;
}
*/
#endif // FILES_H
