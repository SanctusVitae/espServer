/*
#include "nSocket.h"

void onClientConnect() {
  Serial.println("Client connected!");
}

void onClientDisconnect(AsyncWebSocketClient* client) {
  //os_printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
}

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len) {
  Serial.println("Something happened!");
  if (type == WS_EVT_CONNECT) {
    Serial.println("Client connected!");
    return;
  }
  if (type == WS_EVT_DISCONNECT) {
    onClientDisconnect(client);
    return;
  }
  if (type == WS_EVT_ERROR) { //error was received from the other end
    //os_printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
    return;
  }
  if (type == WS_EVT_PONG) { //pong message was received (in response to a ping request maybe)
    //os_printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");
    return;
  }
  if (type == WS_EVT_DATA) {
    return;
  } else {
    Serial.println("Diff data type");
  }
}*/
