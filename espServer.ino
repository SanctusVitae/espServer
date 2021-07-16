// Hej! Program mam nadzieję jak najbardziej czytelny nawet bez komentarzy. Opiszę bardziej jak działa...
// Komentarze do czytania tylko w plikach .h kod dość czytelny i bez nich
// Jest po otwarciu strony okno czatu, pisząc w konsoli portu szeregowego wysyłamy message do klientów od servera
// Gdy pisze klient wysyłamy message do servera, który zapisuje sie do chatlogu i jest wysyłany do wszystkich klientów
// Nie robiłem wysyłania wiadomość po wiadomości bo nie chcę walczyć z javascriptem, już to było problematyczne dla mnie, pierwszy raz go widzę na oczy
// Wysyłam cały content pliku, mało efektywne ale za mało info jest by się przejmować.

// Funkcja configureConnections() miała nie istnieć, to wszystko miało się dziać wewnętrznie w nWiFi i namespaceach
// Byłoby bardziej widoczne w setupie jednak nie chce mi się już tego teraz poprawiać! Wakacje!

#include "nWiFi.h"
#include "FlashFile.h"
#include "nServer.h"
#include "nSocket.h"

void updateChatWithSerialInput();

HTTPWebServer server(80);
ChatWebSocket chatSocket("/ws");

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();

  FlashFile logChat(network::chatLogFileName);
  logChat.saveContent("");

  configureConnection();

  server.handleSocket(chatSocket);

  server.setStaticWebsites();
  server.setupResponses();
  server.begin();
}

void loop() {
  network::dns::processNextRequest();
  chatSocket.cleanupClients();
  updateChatWithSerialInput();
}

void configureConnection() {
  // Zostawiam jako czyste stringi bo już nie chce mi się aktualizować wszędzie constów, kończę program
  String externalSSID = "";
  String externalPASS = "";
  String apSSID = "";
  
  FlashFile configFile(network::configFileName);
  if (configFile.existed()) {
    apSSID = configFile.readKeyValue("apssid");
    externalSSID = configFile.readKeyValue("netssid");
    externalPASS = configFile.readKeyValue("netpass");
  }
  
  network::wifi::apMode::disable();
  network::wifi::apMode::configure();
  network::wifi::apMode::enable(apSSID);

  network::wifi::external::connect(externalSSID, externalPASS);
}

void updateChatWithSerialInput() {
  if (Serial.available() <= 0) return;

  String serverMsg = "SERVER: " + Serial.readString();
  
  FlashFile logChat(network::chatLogFileName);
  logChat.saveContent(serverMsg, FlashFile::_WriteType::Append);
  chatSocket.textAll(logChat.loadContent());
}
