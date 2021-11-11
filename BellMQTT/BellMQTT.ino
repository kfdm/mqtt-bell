#include <Arduino.h>
#include "EspMQTTClient.h"
#include "settings.h"
#include "bell.h"

EspMQTTClient client(
  WIFI_SSID,
  WIFI_PASS,
  MQTT_BROKER,
  MQTT_USER,
  MQTT_PASS,
  MQTT_CLIENT,
  MQTT_PORT
);

Bell bell = Bell(12);

void setup()
{
  Serial.begin(115200);

  client.enableDebuggingMessages();
  //client.enableHTTPWebUpdater();
}

void onConnectionEstablished()
{
  client.subscribe("devices/bell/ring", [](const String & topic, const String & payload) {
    Serial.println(topic + ", payload: " + payload);
    bell.ring();
  });
}

void loop()
{
  client.loop();
}
