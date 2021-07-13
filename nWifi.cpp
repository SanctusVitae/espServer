#include "nWiFi.h"

void network::wifi::apMode::configure(IPAddress thisDevIP) {
  IPAddress subnet(255,255,255,0);
  WiFi.setHostname("espdomain");
  WiFi.softAPConfig(thisDevIP, thisDevIP, subnet);
}

void network::wifi::apMode::disable() {
  WiFi.disconnect();
  delay(100);
  WiFi.mode(WIFI_AP_STA);
}

void network::wifi::apMode::enable(String ssid = nSsid) {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid);
  dns::server.start(dns::port, "www.esp.loc", WiFi.softAPIP());
}

DNSServer network::dns::server = DNSServer();

void network::wifi::external::connect(String ssid, String pass) {
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) { delay(1); }
}
/*
void network::loadConfig(const FlashFile& configFile) {
  nSsid = configFile.readKeyValueToContent("ssid");
}
*/
/*
void network::dns::processRequests() {
  // make this run in a while dnsRequests avail...
  server.processNextRequest();
}*/
