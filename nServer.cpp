#include "nServer.h"
#include "FlashFile.h"

//===================================================
//=============Private functions here================
//===================================================
void HTTPWebServer::retrieveIndexPage() { // routing "" should happen LAST
  mServer.on("/", HTTP_GET, [](AsyncWebServerRequest* request){
    request->send(SPIFFS, network::website::index);
  });
}

void HTTPWebServer::retrieveConfPage() { // routing "" should happen LAST
  mServer.on("/confirm.html", HTTP_GET, [](AsyncWebServerRequest* request){
    request->send(SPIFFS, network::website::netcfg);
  });
}

void HTTPWebServer::sendFileForDownloadOnRoute(String route, String fileName) {
  mServer.on(route.c_str(), HTTP_POST, [fileName](AsyncWebServerRequest* request) {
    //request->send(SPIFFS, fileName.c_str(), String(), true);
    Serial.println("Some message");
  });
}

void HTTPWebServer::downloadFile() {
  mServer.on("/filename", HTTP_GET, [](AsyncWebServerRequest* request){
    String txt = "You are actually the";
    Serial.println(txt);
    request->send(SPIFFS, network::website::index);
  });
}

void HTTPWebServer::printMessageFromUser() {
  mServer.on("/send", HTTP_POST, [](AsyncWebServerRequest* request){
    String txt = "You are actually the";
    Serial.println(txt);
  });
}

void HTTPWebServer::updateNetworkConfig() {
  mServer.on("/netcfg", HTTP_POST, [](AsyncWebServerRequest* request){
    request->send(SPIFFS, network::website::netcfg);
    
    FlashFile configFile(network::configFileName);
    if (request->arg("apssid") != "") {
      configFile.writeKeyValue("apssid", request->arg("apssid"));
    }
    if (request->arg("apssid") != "") {
      configFile.writeKeyValue("apssid", request->arg("apssid"));
    }
    if (request->arg("apssid") != "") {
      configFile.writeKeyValue("apssid", request->arg("apssid"));
    }
    if (request->arg("apssid") != "") {
      configFile.writeKeyValue("apssid", request->arg("apssid"));
    }
    if (request->arg("apssid") != "") {
      configFile.writeKeyValue("apssid", request->arg("apssid"));
    }
  });
}

void HTTPWebServer::restartEspDevice() {
  AsyncWebServer* lambdaServer = &mServer;
  mServer.on("/restartDev", HTTP_POST, [lambdaServer](AsyncWebServerRequest* request){
    lambdaServer->reset();
    ESP.restart();
  });
}

//==================================================
//=============Public functions here================
//==================================================
void HTTPWebServer::configureResponses() {
  //retrieveIndexPage();
  retrieveConfPage();
  sendFileForDownloadOnRoute("/gettest", "/web/index.htm");
  printMessageFromUser();
  updateNetworkConfig();
  restartEspDevice();
  downloadFile();
  // routing error 404 page
}

void HTTPWebServer::startServerService() {
  //server.onNotFound(onRequest);
  //server.onFileUpload(onUpload);
  //server.onRequestBody(onBody);
  mServer.begin();
}
