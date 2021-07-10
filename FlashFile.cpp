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
}

FlashFile::~FlashFile() {
  mFile.close();
  SPIFFS.gc();
}

bool FlashFile::existed() {
  return mExisted;
}

File& FlashFile::getSPIFileByReference() {
  return mFile;
}

template <typename T>
bool FlashFile::writeKeyValueToContent(String key, T value) {
  StaticJsonDocument<200> json;
  json[key] = value;
  
  File mFile = SPIFFS.open(mFilePath, "a+");
  if (!mFile) {
    return false;
  }
  serializeJson(json, mFile);
  mFile.close();
  return true;
}

String FlashFile::readKeyValueToContent(String key) const {
  File mFile = SPIFFS.open(mFilePath, "r");
  
  size_t size = mFile.size();
  char* buf = new char[size];
  mFile.readBytes(buf, size);
  
  //DynamicJsonDocument json(200);
  //DeserializationError error = deserializeJson(json, buf);

  String value = "some_wifi";
  
  mFile.close();
  delete buf;
  return value;
}

bool FlashFile::saveContent(const String content, _WriteType writeType) {
  if (writeType == _WriteType::Override)
    SPIFFS.remove(mFilePath);
  File file = SPIFFS.open(mFilePath, "a+");
  if (!file)
    return false;
  file.write(content.c_str());
  file.close();
  return true;
}

String FlashFile::loadContent() {
  if (!SPIFFS.exists(mFilePath))
    return "NoFile: " + mFilePath;

  File file = SPIFFS.open(mFilePath, "r");
  if (!file) 
    return "CannotReadFile: " + mFilePath;
  
  while (file.available())
    Serial.write(file.read());

  file.close();
  return "";
}
