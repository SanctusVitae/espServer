#ifndef NCONSTANTS_H
#define NCONSTANTS_H

#include <Arduino.h>
/*
namespace network {
  class RouteToElement {
      //String& mRoute;
      String& mElement;
    public:
      RouteToElement(String& element) : mElement(element) {}
      String& getRoute()    { return mRoute; }
      String& getElement()  { return mElement; }
  };
} // namespace network
*/
namespace network {
  const int    httpPort = 80;
  const String configFileName = "/netConf.ini";

  namespace website {
    const String index  = "/index.htm";
    const String chat   = "/chat.html";
    const String files  = "/files.html";
    const String netcf  = "/netcf.html";
    const String comm   = "/comm.html";
    const String netcfg = "/netcfg.html";
  } // website

  namespace respCode {
    const int ok        = 200;
    const int notFound  = 404;
  } // responseCode

  namespace mimeType {
    const String text   = "text/plain";
    const String html   = "text/html";
    const String css    = "text/css";
    const String js     = "application/javascript";
    const String gz     = "application/x-gzip";
  } // mimeType
/*
  namespace pageRoute {
    const RouteToElement index  =
    const RouteToElement chat   =
  }*/

  String convertToMIMEType(String fileName);
}

#endif // NCONSTANTS
