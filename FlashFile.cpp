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

bool FlashFile::replaceImmediately(String& cutThis, String& pasteThis) {
  String content = this->loadContent();

  int keyIndex = content.indexOf(cutThis);
  if (keyIndex < 0)
    return false;

  String frontPartStr = content.substring(0, keyIndex);
  String backPartStr = content.substring(keyIndex + cutThis.length());
  this->saveContent(frontPartStr + pasteThis + backPartStr);
  return true;
}

bool FlashFile::writeKeyValue(String key, String value) {
  String content = loadContent();

  saveIniValue(content, key, value);

  saveContent(content);
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

  String replaceStr = content.substring(keyIndex, content.indexOf(endOfLine, keyIndex + 1) + 1);
  content.replace(replaceStr, keyValueLine);
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
