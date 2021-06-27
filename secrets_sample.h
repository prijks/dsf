// rename to "secrets.h" and adjust to your needs

#ifndef _DSF_SECRETS_H
#define _DSF_SECRETS_H

static const char *wifiSsid = "YOURSSID";
static const char *wifiPassword = "YOURWIFIPASSWORD";

static const char *ntpServer = "your.ntp.server";

static const char *mqttServer = "your.mqtt.server";
static const int mqttPort = 1883;
static const char *mqttUser = "YOURMQTTUSER";
static const char *mqttPassword = "YOURMQTTPASSWORD";

static const char *insideTempTopic = "path/to/inside/temperature";
static const char *outsideTempTopic = "path/to/outside/temperature";
static const char *songTopic = "path/to/song/info";
static const char *motionTopic = "path/to/motion/detector";

#endif // _DSF_SECRETS_H
