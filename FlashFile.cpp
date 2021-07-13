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

bool FlashFile::writeKeyValue(String key, String value) {
  File mFile = SPIFFS.open(mFilePath, "a+");
  if (!mFile) {
    return false;
  }
  
  String content = "";
  while (mFile.available())
    content += mFile.readString();

  saveIniValue(content, key, value);
  
  mFile.write(content.c_str());
  mFile.close();
  return true;
}

template <typename T>
bool FlashFile::saveIniValue(String& content, const String& key, const T& value) {
  if (key == "") { return false; }

  String endOfLine = "\n";
  String keyValueLine = key + "=" + String(value) + endOfLine;

  int keyIndex = content.indexOf(key);
  if (keyIndex < 0) {
    content += keyValueLine;
    return true;
  }

  String frontPartStr = content.substring(0, keyIndex);
  String backPartStr = content.substring(content.indexOf(endOfLine) + 1);
  content = frontPartStr + keyValueLine + backPartStr;
  
  return true;
}

String FlashFile::readKeyValue(const String key) {
  String content = loadContent();

  if (content.indexOf(key) < 0)
    return "";

  String returnVal = loadIniValue(content, key);
  return returnVal;
}

String FlashFile::loadIniValue(const String& content, const String& key) const {
  String returnValue = content.substring(content.indexOf(key));
  returnValue = returnValue.substring(0, returnValue.indexOf("\n"));
  returnValue = returnValue.substring(returnValue.indexOf("=") + 1);
  returnValue.trim();
  return returnValue;
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
    return "";

  File file = SPIFFS.open(mFilePath, "r");
  if (!file) 
    return "";

  String returnString = "";
  while (file.available())
    returnString += file.readString();

  file.close();
  return returnString;
}
