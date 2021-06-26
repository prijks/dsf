// DSF - Desk Sixty Five
// Sketch to control the 64x32 LED Array from HackerBox 65
// For use on my desk
//
// Based on HackerBox 0065 sample code, SmartMatrix sample code

#include <WiFi.h>

#include "secrets.h"
#include "display.h"
#include "clock.h"
#include "mqttclient.h"

DsfDisplay dsfDisplay;
DsfClock dsfClock;
DsfMqttClient dsfMqttClient;

void setup()
{
  Serial.begin(115200);

  dsfDisplay.initialize();
  dsfClock.initialize();

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(wifiSsid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiSsid, wifiPassword);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  dsfMqttClient.setCallback(mqtt_callback);
  dsfMqttClient.connect();
}

void loop()
{
  char txtBuffer[12];

  dsfMqttClient.checkConnection();
  dsfDisplay.updateDisplay(WiFi.RSSI());

  delay(250);
}

char song[128];

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
    song[i] = (char)payload[i];
  }
  Serial.println();

  song[length] = '\0';
  dsfDisplay.setSong(song);
}
