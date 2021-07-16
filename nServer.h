#ifndef NSERVER_H
#define NSERVER_H

#include <ESPAsyncWebServer.h>
#include "nConstants.h"

class HTTPWebServer : public AsyncWebServer{
    void loadBasePages();
    void listFilesForDownload(const String& dirPath);
    void updateNetworkConfig();
    void restoreDefaultNetcfg();
    void restartEspDevice();

    //void sendFileForDownloadOnRoute(String route, String fileName);

    public:
      HTTPWebServer(int port) : AsyncWebServer(port) { }

      void handleSocket(AsyncWebSocket& socket);
      void setStaticWebsites();
      void serveStaticShort(const String& path);
      void setupResponses();
};

#endif // NSERVER_H
