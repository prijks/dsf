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
  // client.setServer(mqttServer, 1883);
  // client.setSocketTimeout(1);
  shouldConnect = true;  
}

bool DsfMqttClient::reconnect() {
  if (shouldConnect) {
    Serial.print("Current mqtt status: ");
    Serial.println(client.state());
    Serial.print("connecting to mqtt... ");
    if (wifiClient.connect(mqttServer, mqttPort)) {
      if (client.connect("dsfClient", mqttUser, mqttPassword)) {
        Serial.println("connected!");
        client.subscribe(insideTempTopic);
        client.subscribe(outsideTempTopic);
        client.subscribe(songTopic);
        client.subscribe(motionTopic);
      } else {
        Serial.println("mqtt failed to connect");
      }
    } else {
      Serial.print("wifi failed to connect");
    }
    if (!client.connected()) {
      
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
        return true;
      }
    }
    return false;
  } else {
    // Client connected

    Serial.println("preloop hmm");
    client.loop();
    Serial.println("postloop hmm");
    return true;
  }

  // return client.connected();
}

void DsfMqttClient::setCallback(MQTT_CALLBACK_SIGNATURE)
{  
  client.setCallback(callback);
}
