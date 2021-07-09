#include "files.h"
#include "nWiFi.h"
#include "FlashFile.h"
#include "Server.h"

/*
void socketEventCallback() {
  EventType eType(E_TYPE);
  if (eType.isConnectionEvent()) {
    return;
  }
  if (eType.isTransferEvent()) {
    return;
  }
  // other event non-parse
}


socketServer.manage()
socketServer.showSite()

void SocketServer::manage() {
  }

void sendFileToClient(String filePath) {
  if (filePath.endsWith("/")) filePath += "index.html";
  
  if (SPIFFS.exists(String(filePath + ".gz"))) filePath += ".gz";

  if (SPIFFS.exists(filePath) {
    File file = SPIFFS.open(filePath, "r");
    server.streamFile(file, convertToMIMEType(filePath));
    file.close();                                        
  }
}

void socketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  char * charPayload = (char *) payload;
  switch(type) {
    case WStype_DISCONNECTED:
      //webSocketDisconnected(num);
      break;
    case WStype_CONNECTED:
      //webSocketConnected(num, charPayload);
      break;
    case WStype_TEXT:
      //webSocketGotText(num, charPayload);
      break;
  }
}
*/

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();

  FlashFile configFile(network::configFileName);
  if (configFile.existed())
    network::loadConfig(configFile);

  FlashFile logChat("/cont/chat.log");
  logChat.saveContent("", FlashFile::_WriteType::Append);
  
  network::disableWiFi();
  network::configureIP();
  network::enableWiFi("esp_wifi");

  network::http::configureResponses();
  network::http::startServerService();
  
  //webSocket.begin();
  //webSocket.onEvent(socketEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  //if (anyUsersConnected()) {
      //server.manageUserRequests();
  //}
}
