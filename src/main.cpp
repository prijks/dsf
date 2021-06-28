// DSF - Desk Sixty Five
// Sketch to control the 64x32 LED Array from HackerBox 65
// For use on my desk
//
// Based on HackerBox 0065 sample code, SmartMatrix sample code

#include <WiFi.h>

#include "secrets.h"
#include "display.h"
#include "clock.h"
#include "network.h"

DsfDisplay dsfDisplay;
DsfClock dsfClock;
DsfNetwork dsfNetwork;

void setup()
{
  Serial.begin(115200);

  dsfDisplay.initialize();
  dsfClock.initialize();

  dsfNetwork.initialize();
  dsfNetwork.setCallback(mqtt_callback);
}

void loop()
{
  uint16_t network_state = dsfNetwork.loop();
  dsfDisplay.setNetworkState(network_state);
  dsfDisplay.setTime(dsfClock.getTime());
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
  else if (strcmp(topic, songTitleTopic) == 0)
  {
    dsfDisplay.setSongTitle(msg);
  }
  else if (strcmp(topic, songArtistTopic) == 0)
  {
    dsfDisplay.setSongArtist(msg);
  }
  else if (strcmp(topic, musicStatusTopic) == 0)
  {
    dsfDisplay.setMusicStatus(msg);
  }
  else if (strcmp(topic, motionTopic) == 0)
  {
    dsfDisplay.setMotion(msg);
  }
}
