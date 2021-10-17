#include <Arduino.h>
#include "EspMQTTClient.h"
#include "settings.h"

#define LED_PIN 32

EspMQTTClient client(
  WIFI_SSID,
  WIFI_PASS,
  MQTT_BROKER,
  MQTT_USER,
  MQTT_PASS,
  MQTT_CLIENT,
  MQTT_PORT
);

void setup()
{
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  client.enableDebuggingMessages();
  //client.enableHTTPWebUpdater();
}

void onConnectionEstablished()
{
  client.subscribe("devices/bell/ring", [](const String & topic, const String & payload) {
    Serial.println(topic + ", payload: " + payload);

    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);    
  });

  client.subscribe("devices/bell/timer", [](const String & topic, const String & payload) {
    Serial.println(topic + ", payload: " + payload);
    // For future work  
  });
}

void loop()
{
  client.loop();
}
