// Socket dla chatu, ogólnie myślę by wrzucić tu drugi socket dla debuggera ale to większy projekt, nie chce mi się teraz pisać, też jestem już nad morzem
// Zrobiłem z tego podobnie jak z servera coś bardziej jak fasada mimo, że dziedzicząca z oryginalnej klasy i zachowująca jej metody. No staticów z racji callbackow się nie pozbędę

#ifndef NSOCKET_H
#define NSOCKET_H

#include <ESPAsyncWebServer.h>
#include <Vector.h>
#include "nConstants.h"
#include "FlashFile.h"

class ChatWebSocket : public AsyncWebSocket {
  public:
    ChatWebSocket(const String& url) : AsyncWebSocket(url) {
      this->onEvent(this->callbackEventProcessor);
    }

    static void updateChat(AsyncWebSocket* server, AsyncWebSocketClient* client, uint8_t* data);
    static void callbackEventProcessor(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len);
};

#endif // NSOCKET_H
