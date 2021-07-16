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

void network::wifi::apMode::enable(String ssid) {
  if (ssid == "") { ssid = nSsid; }
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid);
  dns::server.start(dns::port, "www.esp.loc", WiFi.softAPIP());
}

DNSServer network::dns::server = DNSServer();

void network::wifi::external::connect(String toSsid, String onPass) {
  WiFi.begin(toSsid, onPass);
  int connectionRetryTimes = 50;
  int time = 0;
  while ((WiFi.status() != WL_CONNECTED) && (time < connectionRetryTimes)) { delay(100); time++; }
}

void network::dns::processNextRequest() {
  server.processNextRequest();
}
