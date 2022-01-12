#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "data.h"
ESP8266WebServer server(80);

const char* ssid = "rexulec";
const char* password = "rexulec1357";

void mainpage() {
  Serial.print("Log | Open => Main Page");
  server.send(200, "text/html", webpageCode);
  digitalWrite(14, HIGH);
  delay(1000);
  digitalWrite(14, LOW);
  delay(100);
}

void stats() {
  Serial.print("Opened | Status Page");
  DynamicJsonDocument doc(512);
  doc["status"] = "on";
  String buf;
  serializeJson(doc, buf);
  server.send(200, "application/json", buf);
  delay(100);
}
 
void setup () {

  pinMode(12, OUTPUT); 
  pinMode(14, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("IP Adress: ");
  Serial.print(WiFi.localIP());
  server.on("/", mainpage);
  server.on("/status", stats);
 
  server.begin();
}
 
void loop() {
  server.handleClient();
  digitalWrite(12, HIGH);
  delay(1000);
}
