#include "Server.h"
#include "FlashFile.h"

namespace network {
namespace http {
//===================================================
//=============Private functions here================
//===================================================
namespace { // private namespace
void retrieveIndexPage() {
  server.on("", HTTP_GET, [](AsyncWebServerRequest* request){
    request->send(SPIFFS, "/web/chat.html");
  });
}

void sendFileForDownloadOnRoute(String route, String fileName) {
  server.on(route.c_str(), HTTP_GET, [&fileName](AsyncWebServerRequest* request) {
    request->send(SPIFFS, fileName.c_str(), String(), true);
  });
}

void printMessageFromUser() {
  server.on("/send", HTTP_POST, [](AsyncWebServerRequest* request){
    String txt = "You are actually the";
    Serial.println(txt);
  });
}

void updateWifiNetworkConfig() {
  server.on("/newwifi", HTTP_POST, [](AsyncWebServerRequest* request){
    //FlashFile configFile(network::configFileName);
   // configFile.writeKeyValueToContent("ssid", request->arg("netSSID"));
    //configFile.writeKeyValueToContent("pass", request->arg("netPASS"));
    request->send(SPIFFS, "/web/chat.html");
  });
}

void restartEspDevice() {
  server.on("/restart", HTTP_POST, [](AsyncWebServerRequest* request){
    ESP.restart();
  });
}

} // namespace private

//==================================================
//=============Public functions here================
//==================================================
void configureResponses() {
  retrieveIndexPage();
  sendFileForDownloadOnRoute("/gettest", "/web/index.html");
  printMessageFromUser();
  //updateWifiNetworkConfig();
  restartEspDevice();
}

void startServerService() {
  server.begin();
}

} // namespace http
} // namespace network
