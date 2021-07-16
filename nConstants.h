#ifndef NCONSTANTS_H
#define NCONSTANTS_H

#include <Arduino.h>

namespace network {
  const int    httpPort = 80;
  const String configFileName = "/netConf.ini";
  const String chatLogFileName = "/cont/chat.log";

  namespace website {
    const String index  = "/index.htm";
    const String chat   = "/chat.html";
    const String files  = "/files.html";
    const String files_r= "/files_raw.html";
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

  String convertToMIMEType(const String fileName);
}

#endif // NCONSTANTS
