#include "nWiFi.h"
#include "FlashFile.h"
#include "nServer.h"
//#include "nSocket.h"

#include <ESPAsyncWebServer.h>

/*
void sendFileToClient(String filePath) {
  if (filePath.endsWith("/")) filePath += "index.html";
  
  if (SPIFFS.exists(String(filePath + ".gz"))) filePath += ".gz";

  if (SPIFFS.exists(filePath) {
    File file = SPIFFS.open(filePath, "r");
    server.streamFile(file, convertToMIMEType(filePath));
    file.close();                                        
  }
}
*/

HTTPWebServer server(80);
AsyncWebSocket ws("/ws");

void onClientConnect() {
  Serial.println("Client connected!");
}

void onClientDisconnect(AsyncWebSocketClient* client) {
  //os_printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
}

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len) {
  Serial.print("wsEvent! : ");
  if (type == WS_EVT_CONNECT) {
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
    client->printf("Hello Client %u :)", client->id());
    client->ping();
    return;
  }
  if (type == WS_EVT_DISCONNECT) {
    Serial.println("Disconnect recieved");
    onClientDisconnect(client);
    return;
  }
  if (type == WS_EVT_ERROR) { //error was received from the other end
    Serial.println("Error recieved");
    //os_printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
    return;
  }
  if (type == WS_EVT_PONG) { //pong message was received (in response to a ping request maybe)
    Serial.println("Pong recieved");
    os_printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (char*)data);
    return;
  }
  if (type == WS_EVT_DATA) {
    Serial.println("Data recieved");
    return;
  } else {
    Serial.println("Diff data type");
  }
}

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();

  //FlashFile configFile("/netConf.ini");
  //if (configFile.existed())
  //  network::loadConfig(configFile);

  //FlashFile logChat("/cont/chat.log");
  //logChat.saveContent("", FlashFile::_WriteType::Append);

  //FlashFile saveFile("/cont/myFile.ini");
  //saveFile.writeKeyValue("saved1", "yeah");
  //saveFile.writeKeyValueToContent("saved2", "ye");
  //String content = "ssid=vitae\npass=123";
  //saveFile.saveContent(content);
  
  
  network::wifi::apMode::disable();
  network::wifi::apMode::configure();
  network::wifi::apMode::enable("esp_wifi");

  network::wifi::external::connect("VitaeWork", "13376889");

  ws.onEvent(onWsEvent);
  server.getServer().addHandler(&ws);

  server.getServer().serveStatic("/", SPIFFS, "/").setDefaultFile("index.htm");
  server.getServer().serveStatic(network::website::netcfg.c_str(),
                                 SPIFFS, network::website::netcfg.c_str())
                                 .setDefaultFile(network::website::netcfg.c_str());
  
  server.configureResponses();
  server.startServerService();
}

void loop() {
  //network::dns::processRequests();
  // put your main code here, to run repeatedly:
  //if (anyUsersConnected()) {
      //server.manageUserRequests();
  //}
}
