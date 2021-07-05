#include "FlashFile.h"

bool FlashFile::fileSystemStarted = false;

void FlashFile::flashSystemBegin() {
  if (fileSystemStarted)
    return; 
  SPIFFS.begin();
  fileSystemStarted = true;
}

FlashFile::FlashFile(String filePath) : mFilePath(filePath), mExisted(false) {
  if (!SPIFFS.exists(mFilePath))
    mExisted = true;
  /*
  File mFile = SPIFFS.open(mFilePath, "rw");
  if (!mFile) {
    return;
  }*/
}

FlashFile::~FlashFile() {
  mFile.close();
  SPIFFS.gc();
  //SPIFFS.end();
}

bool FlashFile::existed() {
  return mExisted;
}

File& FlashFile::getSPIFileByReference() {
  return mFile;
}

template <typename T>
bool FlashFile::writeKeyValueToContent(String key, T value) {
  return true;
}

template <typename T>
T FlashFile::readKeyValueToContent(String key) {
  return static_cast<T>(key);
}

bool FlashFile::saveContent(const String content) {
  return true;
}

String FlashFile::loadContent() {
  if (!SPIFFS.exists(mFilePath)) return "NoFile: " + mFilePath;

  File file = SPIFFS.open(mFilePath, "r");
  if (!file) { return "CannotReadFile: " + mFilePath; }
  
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
  return "";
}
