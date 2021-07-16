// Tutaj miały być obsługi JSONów jednak ostatecznie zdecydowałem się na coś w stylu plików .ini
// Dlaczego otwieranie i zamykanie plików w każdej funkcji? Wyczytałem w połowie robienia programu, że złym pomysłem jest trzymanie otwartego kontekstu pliku w SPIFFS
// Ponoć wytwarza sporo błędów i ciągnie pamięć. Jako, że operacji na plikach nie ma dużo to zostawiam jak jest

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
    //void    changeFilePath(String filePath);
    bool    replaceImmediately(String& cutThis, String& pasteThis);
  
    bool    writeKeyValue(String key, String value);
    String  readKeyValue(String key);
    
    bool    saveContent(const String content, _WriteType writeType = _WriteType::Override);
    String  loadContent();

  private:
    File    mFile;
    String  mFilePath;
    bool    mExisted;

    template <typename T>
    bool    saveIniValue(String& content, const String& key, const T& value);
    String  loadIniValue(const String& content, const String& key) const;
    
    static bool fileSystemStarted;
    static void flashSystemBegin();
};

#endif // FLASHFILE_H
