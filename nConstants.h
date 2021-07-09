#ifndef NCONSTANTS_H
#define NCONSTANTS_H

#include <Arduino.h>

namespace network {
  static const int    httpPort = 80;
  static const String configFileName = "/netConf.ini";

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

  String convertToMIMEType(String fileName);
}

#endif // NCONSTANTS
