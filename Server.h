#ifndef SERVER_H
#define SERVER_H

#include <ESPAsyncWebServer.h>
#include "nConstants.h"

namespace network {
  static AsyncWebSocket ws("/ws");

namespace http {
  static AsyncWebServer server(httpPort);
  
  void configureResponses();
  void startServerService();
} // namespace http
  
} // namespace network

#endif // SERVER_H
