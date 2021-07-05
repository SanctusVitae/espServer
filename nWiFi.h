#ifndef NETWORK_H
#define NETWORK_H

#include <ESP8266WiFi.h>
#include "FlashFile.h"

namespace network {
  static String nSsid = "not_conf";
  
  void configureIP();
  void disableWiFi();
  void enableWiFi(String ssid);
  void enableWiFi();

  void loadConfig(const FlashFile& configFile);
}

//String network::nSsid = "not_conf";

void network::configureIP() {
  IPAddress localIp(133,133,7,7);
  IPAddress gateway(133,133,7,7);
  IPAddress subnet(255,255,255,0);
  WiFi.softAPConfig(localIp, gateway, subnet);
}

void network::disableWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.mode(WIFI_STA);
}

void network::enableWiFi(String ssid) {
  WiFi.softAP(ssid);
}

void network::enableWiFi() {
  WiFi.softAP(nSsid);
}

void network::loadConfig(const FlashFile& configFile) {
  
}

#endif // NETWORK_H