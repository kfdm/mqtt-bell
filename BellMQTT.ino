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
  client.subscribe("pomodoro/+/nag", [](const String & topic, const String & payload) {
    Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);

    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);    
  });
}

void loop()
{
  client.loop();
}
