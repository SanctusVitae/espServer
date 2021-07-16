#include "nServer.h"
#include "FlashFile.h"

#include <Vector.h>

String vectorStorage[100];

Vector<String> getFileList(const String& dirPath) {
  Dir root = SPIFFS.openDir(dirPath);
  
  Vector<String> fileList;
  fileList.setStorage(vectorStorage);
  
  while (root.next())
    fileList.push_back(root.fileName());

  return fileList;
}

//===================================================
//=============Private functions here================
//===================================================
void HTTPWebServer::loadBasePages() {
  on(network::website::files.c_str(), HTTP_GET, [](AsyncWebServerRequest* request){
    request->send(SPIFFS, network::website::files);
  });
}

/* void HTTPWebServer::sendFileForDownloadOnRoute(String route, String fileName) {
  on(route.c_str(), HTTP_POST, [fileName](AsyncWebServerRequest* request) {
    request->send(SPIFFS, fileName.c_str(), String(), true);
    Serial.println("Some message");
  });
}*/

void HTTPWebServer::updateNetworkConfig() {
  on("/netcfgset", HTTP_POST, [](AsyncWebServerRequest* request){
    request->send(SPIFFS, network::website::netcfg);
    
    FlashFile configFile(network::configFileName);
    if (request->arg("apssid") != "") {
      configFile.writeKeyValue("apssid", request->arg("apssid"));
    }
    configFile.writeKeyValue("appass", request->arg("appass"));
    if (request->arg("apip") != "") {
      configFile.writeKeyValue("apip", request->arg("apip"));
    }
    configFile.writeKeyValue("netssid", request->arg("netssid"));
    configFile.writeKeyValue("netpass", request->arg("netpass"));
    Serial.println("Value is: " + configFile.readKeyValue("apssid"));
    Serial.println("Value is: " + configFile.readKeyValue("appass"));
    Serial.println(configFile.loadContent());
  });
}

void HTTPWebServer::listFilesForDownload(const String& dirPath) {
  Vector<String> filesList = getFileList(dirPath);
  
  String replaceContent = "";
  String replaceMarker = "REPLACE_HERE";
  String linkFront = "<a href=\"";
  String linkMiddle = "\" download>";
  String linkBack = "<br></a>";

  FlashFile filesHtml(network::website::files_r);
  String htmlContent = filesHtml.loadContent();

  for (String fileName : filesList) {
    replaceContent += linkFront + fileName + linkMiddle + fileName + linkBack;
    on(fileName.c_str(), HTTP_POST, [fileName](AsyncWebServerRequest* request) {
      request->send(SPIFFS, fileName.c_str(), String(), true);
    });
  }

  FlashFile tempFilesHtml(network::website::files);
  tempFilesHtml.saveContent(htmlContent);
  tempFilesHtml.replaceImmediately(replaceMarker, replaceContent);
}

void HTTPWebServer::restoreDefaultNetcfg() {
  on("/restoreDef", HTTP_POST, [](AsyncWebServerRequest* request){
    FlashFile configFile(network::configFileName);
    configFile.saveContent("");
  });
}

void HTTPWebServer::restartEspDevice() {
  AsyncWebServer* lambdaServer = this;
  on("/restartDev", HTTP_POST, [lambdaServer](AsyncWebServerRequest* request){
    lambdaServer->reset();
    ESP.restart();
  });
}

//==================================================
//=============Public functions here================
//==================================================
void HTTPWebServer::handleSocket(AsyncWebSocket& socket) {
  addHandler(&socket);
}

void HTTPWebServer::setStaticWebsites() {
  serveStatic("/", SPIFFS, "/").setDefaultFile("index.htm");
  serveStaticShort(network::website::netcfg);
}

void HTTPWebServer::serveStaticShort(const String& path) {
  serveStatic(path.c_str(), SPIFFS, path.c_str()).setDefaultFile(path.c_str());
}

void HTTPWebServer::setupResponses() {
  //sendFileForDownloadOnRoute("/ftp/testFile.txt", "/ftp/testFile.txt");
  listFilesForDownload("/ftp");
  updateNetworkConfig();
  restoreDefaultNetcfg();
  restartEspDevice();
  loadBasePages();
}
