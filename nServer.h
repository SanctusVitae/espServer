#pragma once

#include <ESPAsyncWebServer.h>
#include "nConstants.h"

class HTTPWebServer {
    AsyncWebServer mServer;

    void retrieveIndexPage();
    void retrieveConfPage();
    void sendFileForDownloadOnRoute(String route, String fileName);
    void downloadFile();
    void printMessageFromUser();
    void updateNetworkConfig();
    void restartEspDevice();

    public:
      HTTPWebServer(int port) : mServer(AsyncWebServer(port)) { }

      AsyncWebServer& getServer() { return mServer; }

      void configureResponses();
      void startServerService();
};
