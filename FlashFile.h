#ifndef FLASHFILE_H
#define FLASHFILE_H

#include <FS.h>
#include <ArduinoJson.h>
#include <Arduino.h>

class FlashFile {
  public:
    enum class _WriteType : int {
      Append = 0,
      Override = 1
    };

  public:
    FlashFile(String filePath);
    ~FlashFile();
  
    bool    existed();
    File&   getSPIFileByReference();
    void    changeFilePath(String filePath);
  
    template <typename T>
    bool    writeKeyValueToContent(String key, T value);
    String  readKeyValueToContent(String key) const;
    
    bool    saveContent(const String content, _WriteType writeType = _WriteType::Override);
    String  loadContent();

  private:
    File    mFile;
    String  mFilePath;
    bool    mExisted;
    
    static bool fileSystemStarted;
    static void flashSystemBegin();
};

#endif // FLASHFILE_H
