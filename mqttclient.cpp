#include <WiFi.h>
#include <PubSubClient.h>

#include "mqttclient.h"
#include "secrets.h"

WiFiClient wifiClient;
PubSubClient client(wifiClient);
long lastReconnectAttempt = 0;

DsfMqttClient::DsfMqttClient()
{
  shouldConnect = false;
}

void DsfMqttClient::connect()
{
  client.setServer(mqttServer, 1883);
  shouldConnect = true;  
}

bool DsfMqttClient::reconnect() {
  if (shouldConnect) {
    Serial.print("connecting to mqtt... ");
    if (client.connect("dsfClient", mqttUser, mqttPassword)) {
      Serial.println("connected!");
      client.subscribe("house/basement/desk/music/#");
    }
    if (!client.connected()) {
      Serial.println("failed to connect");
    }
    return client.connected();
  } else {
    return false;
  }
}

bool DsfMqttClient::checkConnection()
{
  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected

    client.loop();
  }

  return client.connected();
}

void DsfMqttClient::setCallback(MQTT_CALLBACK_SIGNATURE)
{  
  client.setCallback(callback);
}
