#include "Server.h"
#include "FlashFile.h"

namespace network {
namespace http {
//===================================================
//=============Private functions here================
//===================================================
namespace { // private namespace
void retrieveIndexPage() { // routing "" should happen LAST
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request){
    request->send(SPIFFS, website::index);
  });
}

void retrieveConfPage() { // routing "" should happen LAST
  server.on("/confirm.html", HTTP_GET, [](AsyncWebServerRequest* request){
    request->send(SPIFFS, website::conf);
  });
}

void sendFileForDownloadOnRoute(String route, String fileName) {
  server.on(route.c_str(), HTTP_POST, [fileName](AsyncWebServerRequest* request) {
    //request->send(SPIFFS, fileName.c_str(), String(), true);
    Serial.println("Some message");
  });
}

void downloadFile() {
  server.on("/filename", HTTP_GET, [](AsyncWebServerRequest* request){
    String txt = "You are actually the";
    Serial.println(txt);
    request->send(SPIFFS, website::index);
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
    request->send(SPIFFS, website::chat);
    //FlashFile configFile(network::configFileName);
    //configFile.writeKeyValueToContent("ssid", request->arg("netSSID"));
    //configFile.writeKeyValueToContent("pass", request->arg("netPASS"));
  });
}

void restartEspDevice() {
  server.on("/restart", HTTP_POST, [](AsyncWebServerRequest* request){
    //ESP.restart();
  });
}

} // namespace private

//==================================================
//=============Public functions here================
//==================================================
void configureResponses() {
  retrieveIndexPage();
  retrieveConfPage();
  sendFileForDownloadOnRoute("/gettest", "/web/index.html");
  printMessageFromUser();
  //updateWifiNetworkConfig();
  //restartEspDevice();
  downloadFile();
  // routing error 404 page
}

void startServerService() {
  server.begin();
}

} // namespace http
} // namespace network
