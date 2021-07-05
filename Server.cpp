#include "Server.h"

namespace network {
namespace http {

namespace { // private namespace
void retrieveIndexPage() {
  server.on("", HTTP_GET, [](AsyncWebServerRequest* request){
    request->send(SPIFFS, "/web/index.html");
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

} // namespace private
void configureResponses() {
  retrieveIndexPage();
  sendFileForDownloadOnRoute("/gettest", "/web/index.html");
  printMessageFromUser();
}

void startServerService() {
  server.begin();
}
} // namespace http

} // namespace network
