// Obsługa wifi, dnsa, zewnętrznego neta itp. Namespace bo nie jestem fanem singletonów, nadal trwają dyskusje czy to antypattern

#ifndef NETWORK_H
#define NETWORK_H

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include "FlashFile.h"

namespace network {
namespace wifi {
namespace apMode {
  const String nSsid = "not_conf";
  
  void configure(IPAddress thisDevIP = IPAddress(133,133,7,7));
  void disable();
  void enable(String ssid);
} // namespace apMode

namespace external {
  void connect(String toSsid, String onPass);
} // namespace external
} // namespace wifi

namespace dns {
  const  int       port = 53;
  extern DNSServer server;

  void processNextRequest();
} // namespace dns
} // namespace network

#endif // NETWORK_H
