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

  Serial.println("hmm1");
  dsfMqttClient.checkConnection();
  Serial.println("hmm2");
  dsfDisplay.updateDisplay(WiFi.RSSI());
  Serial.println("hmm3");

  dsfDisplay.setTime(dsfClock.getTime());

  Serial.println("hmm4");
  delay(250);
}

char msg[128];

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
    msg[i] = (char)payload[i];
  }
  Serial.println();

  msg[length] = '\0';

  if (strcmp(topic, insideTempTopic) == 0)
  {
    dsfDisplay.setInsideTemp(msg);
  }
  else if (strcmp(topic, outsideTempTopic) == 0)
  {
    dsfDisplay.setOutsideTemp(msg);
  }
  else if (strcmp(topic, songTopic) == 0)
  {
    dsfDisplay.setSong(msg);
  }
  else if (strcmp(topic, motionTopic) == 0)
  {
    dsfDisplay.setMotion(msg);
  }

  Serial.println("hmmmmmmm callback hmm");
}
