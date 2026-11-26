#include <WiFi.h>
#include <FS.h>
#include <LittleFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Pins
const int
  // pin microphone MAX9814
  pinMicro = 4,
  // capteur ultrason HC-SR04
  pinTrigger = 14,  // pin trigger
  pinEcho = 12,     // pin echo
  // capteur température DS18B20
  pinTemp = 0,
  // capteurs infrarouge PIR HC-SR501
  pinPir1 = 13,
  pinPir2 = 0,
  pinPir3 = 0,
  pinPir4 = 0;

// Paramètres de connexion Wi-Fi
const char* ssid = "Monpointacces";
const char* password = "arduino1234";

// Création du serveur web sur le port 80
AsyncWebServer server(80);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);

  // 1. Initialisation du système de fichiers LittleFS
  if (!LittleFS.begin(true)) {
    Serial.println("Erreur : Impossible de monter LittleFS.");
    return;
  }
  Serial.println("LittleFS monté avec succès !");

  // 2. Connexion au réseau Wi-Fi
  Serial.print("Connexion en cours au Wi-Fi ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n Connecté au Wi-Fi !");
  Serial.print("Ouvrez ce lien sur votre téléphone : http://");
  Serial.println(WiFi.localIP());

  // 3. CONFIGURATION DES ROUTAGES (URLs)
  server.serveStatic("/", LittleFS, "/index.html");
  server.serveStatic("/style.css", LittleFS, "/style.css");
  server.serveStatic("/script.js", LittleFS, "/script.js");

  // Gestion des pages introuvables (Erreur 404)
  server.onNotFound([](AsyncWebServerRequest* request) {
    request->send(404, "text/plain", "Fichier introuvable.");
  });

  // Démarrage effectif du serveur web
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}
