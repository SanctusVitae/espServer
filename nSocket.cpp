#include "nSocket.h"

String getSocketDataById(String& data, String id) {
  const String extendedId = "\"" + id + "\":\"";
  int idIndex = data.indexOf(extendedId);
  if (idIndex < 0)
    return "";

  data = data.substring(idIndex + extendedId.length());
  if (data.indexOf("\",\"") >= 0)
    return data.substring(0, data.indexOf("\""));
  else
    return data.substring(0, data.indexOf("\"}"));
}

String stringifyIP(IPAddress IP) {
  return String(IP[0]) + "." + String(IP[1]) + "." + String(IP[2]) + "." + String(IP[3]);
}

void ChatWebSocket::updateChat(AsyncWebSocket* server, AsyncWebSocketClient* client, uint8_t* data) {
  String dataStr((char*)data);
  String clientMsg = stringifyIP(client->remoteIP()) + ": " + getSocketDataById(dataStr, "chat") + "\n";

  FlashFile logChat(network::chatLogFileName);
  logChat.saveContent(clientMsg, FlashFile::_WriteType::Append);
  server->textAll(logChat.loadContent());
}

void ChatWebSocket::callbackEventProcessor(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len) {
  // AsyncWebSocketBasicMessage* msg = new AsyncWebSocketBasicMessage("testMsg", 7);
  switch(type) {
    case WS_EVT_CONNECT: break;
    case WS_EVT_DISCONNECT: break;
    case WS_EVT_DATA: updateChat(server, client, data); break;
    case WS_EVT_PONG: Serial.println("Pong"); break;
     default: Serial.println("unexpected event"); break;
  }
}
