#include <WiFi.h>
#include <PubSubClient.h>

#include "network.h"
#include "secrets.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
long lastReconnectAttempt = 0;

void DsfNetwork::initialize()
{
  network_state = NETWORK_STATE_WIFI_DOWN;
}

void DsfNetwork::checkStatus()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    if (network_state != NETWORK_STATE_WIFI_STARTING)
    {
      network_state = NETWORK_STATE_WIFI_DOWN;
    }
  }
  else
  {
    if (!wifiClient.connected() || !mqttClient.connected())
    {
      if (network_state != NETWORK_STATE_WIFI_UP_MQTT_STARTING)
      {
        network_state = NETWORK_STATE_WIFI_UP_MQTT_DOWN;
      }
    }
  }
}

void DsfNetwork::fixStatus()
{
  switch (network_state)
  {
  case NETWORK_STATE_WIFI_DOWN:
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifiSsid, wifiPassword);
    network_state = NETWORK_STATE_WIFI_STARTING;
    break;
  case NETWORK_STATE_WIFI_STARTING:
    break;
  case NETWORK_STATE_WIFI_UP_MQTT_DOWN:
    if (wifiClient.connect(mqttServer, mqttPort))
    {
      mqttClient.connect("dsfClient", mqttUser, mqttPassword);
      network_state = NETWORK_STATE_WIFI_UP_MQTT_STARTING;
    }
    break;
  case NETWORK_STATE_WIFI_UP_MQTT_STARTING:
    if (mqttClient.connected())
    {
      mqttClient.subscribe(insideTempTopic);
      mqttClient.subscribe(outsideTempTopic);
      mqttClient.subscribe(songTitleTopic);
      mqttClient.subscribe(songArtistTopic);
      mqttClient.subscribe(musicStatusTopic);
      //mqttClient.subscribe(motionTopic);
      network_state = NETWORK_STATE_WIFI_UP_MQTT_UP;
    }
    break;
  case NETWORK_STATE_WIFI_UP_MQTT_UP:
    break;
  }
}

uint16_t DsfNetwork::loop()
{
  checkStatus();
  fixStatus();
  if (network_state == NETWORK_STATE_WIFI_UP_MQTT_UP)
  {
    mqttClient.loop();
  }
  return network_state;
}

void DsfNetwork::setCallback(MQTT_CALLBACK_SIGNATURE)
{
  mqttClient.setCallback(callback);
}
