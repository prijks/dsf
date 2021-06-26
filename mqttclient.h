#ifndef _DSF_MQTTCLIENT_H
#define _DSF_MQTTCLIENT_H

#include <PubSubClient.h>

class DsfMqttClient
{
  private:
    bool shouldConnect;
    bool reconnect();

  public:
    DsfMqttClient();
    void setCallback(MQTT_CALLBACK_SIGNATURE);
    void connect();
    bool checkConnection();

};

#endif // _DSF_MQTTCLIENT_H
