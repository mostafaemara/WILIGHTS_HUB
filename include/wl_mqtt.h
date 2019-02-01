#ifndef WL_MQTT_H
#define WL_MQTT_H

#include"uMQTTBroker.h"
#include"MQTT.h"
#include"wl_debug.h"
#define MQTT_SERVER_PORT 1883
#define MQTT_SERVER_MAX_CLIENTS 10
#define MQTT_SERVER_MAX_TOPICS 10
#define MQTT_TOPIC_NODE_HANDSHAKE "base/node/handshake"
#define MQTT_TOPIC_APP_HANDSHAKE "base/app/handshake"
#define MQTT_TOPIC_APP_COMMAND "base/app/cmd"
#define MQTT_ALL_TOPICS "#"
#define MQTT_CLIENT_HOST "m20.cloudmqtt.com"
#define MQTT_CLIENT_PORT 15228
#define MQTT_CLIENT_ID "DarkBlue"
#define MQTT_CLIENT_USER "lrcpeafb"
#define MQTT_CLIENT_PASS "wOGwP2ntRAso"
#define MQTT_CLIENT_KEEPALIVE "60"
#define MQTT_CLIENT_CLEAN_SESSION 1
#if defined(MQTT_DEBUG_ON)
#define MQTT_INFO( format, ... ) Serial.printf( format, ## __VA_ARGS__ )
#else
#define MQTT_INFO( format, ... )
#endif

void mqtt_broker_start(MqttDataCallback mqttdatacb);

void mqtt_broker_publish(const char*topic,const char*data);

void mqtt_broker_stop(void);
void mqtt_client_init(MqttCallback connectcb,MqttCallback disconnectedcb,MqttCallback publishcb,MqttDataCallback datacb);
void mqtt_client_connect(void);
void mqtt_client_disconnect(void);
void mqtt_client_publish(const char* topic,const char* data);

#endif

