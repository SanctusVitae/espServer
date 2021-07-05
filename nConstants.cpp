#include "nConstants.h"

namespace network {
String convertToMIMEType(String fileName) { 
  if (fileName.endsWith(".html")) return mimeType::html;
  if (fileName.endsWith(".css")) return mimeType::css;
  if (fileName.endsWith(".js")) return mimeType::js;
  if (fileName.endsWith(".gz")) return mimeType::gz;
  return mimeType::text;
}
}
