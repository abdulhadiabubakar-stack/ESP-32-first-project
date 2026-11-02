#include <Arduino.h>
#include <WiFi.h>
#include "secrets.h"

void connectToWifi() {
  Serial.println("Initializing WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  const unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("WiFi status: ");
    Serial.println(WiFi.status());

    if (millis() - startTime > 20000UL) {
      Serial.println("Timed out waiting for WiFi connection.");
      return;
    }

    delay(500);
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  connectToWifi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected, retrying...");
    connectToWifi();
  }

  delay(5000);
}