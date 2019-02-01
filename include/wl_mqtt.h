#ifndef WL_MQTT_H
#define WL_MQTT_H

#include"uMQTTBroker.h"
#include"wl_debug.h"
#define MQTT_SERVER_PORT 1883
#define MQTT_SERVER_MAX_CLIENTS 10
#define MQTT_SERVER_MAX_TOPICS 10
#define MQTT_TOPIC_NODE_HANDSHAKE "base/node/handshake"
#define MQTT_TOPIC_APP_HANDSHAKE "base/app/handshake"
#define MQTT_TOPIC_APP_COMMAND "base/app/command"
#define MQTT_ALL_TOPICS "#"
#if defined(MQTT_DEBUG_ON)
#define MQTT_INFO( format, ... ) Serial.printf( format, ## __VA_ARGS__ )
#else
#define MQTT_INFO( format, ... )
#endif

void mqtt_broker_start(MqttDataCallback mqttdatacb);

void mqtt_broker_publish(const char*topic,const char*data);

void mqtt_broker_stop(void);

#endif

