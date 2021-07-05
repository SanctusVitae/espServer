#ifndef FLASHFILE_H
#define FLASHFILE_H

#include <FS.h>
#include <ArduinoJson.h>
#include <Arduino.h>

class FlashFile {
  File    mFile;
  String  mFilePath;

  bool    mExisted;
  
  static bool fileSystemStarted;
  static void flashSystemBegin();
  
  public:
  FlashFile(String filePath);
  ~FlashFile();

  bool    existed();
  
  File&   getSPIFileByReference();
  void    changeFilePath(String filePath);

  template <typename T>
  bool  writeKeyValueToContent(String key, T value);
  template <typename T>
  T     readKeyValueToContent(String key);
  
  bool    saveContent(const String content);
  String  loadContent();
};

#endif // FLASHFILE_H
