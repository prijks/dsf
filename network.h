#ifndef _DSF_NETWORK_H
#define _DSF_NETWORK_H

#include <PubSubClient.h>

#define NETWORK_STATE_WIFI_DOWN 0
#define NETWORK_STATE_WIFI_STARTING 1
#define NETWORK_STATE_WIFI_UP_MQTT_DOWN 2
#define NETWORK_STATE_WIFI_UP_MQTT_STARTING 3
#define NETWORK_STATE_WIFI_UP_MQTT_UP 4

class DsfNetwork
{
private:
  uint16_t network_state;
  void checkStatus();
  void fixStatus();

public:
  void initialize();
  void setCallback(MQTT_CALLBACK_SIGNATURE);
  //void connect();
  uint16_t loop();
};

#endif // _DSF_NETWORK_H
