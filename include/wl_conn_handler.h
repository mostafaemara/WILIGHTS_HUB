#ifndef WL_CONN_HANDLER_H
#define WL_CONN_HANDLER_H

#include"wl_mesh.h"
#include"wl_mqtt.h"
#include "wl_mdns.h"
#include "wl_debug.h"
#include"wl_led.h"

#if defined(CONN_HANDLER_DEBUG_ON)
#define CONN_HANDLER_INFO(format, ...) Serial.printf(format, ##__VA_ARGS__)
#else
#define CONN_HANDLER_INFO(format, ...)
#endif
void conn_handler_init(void);
#endif
class WLConnection{

private:
MQTT_Client wlMqttClient;
painlessMesh wlMesh;
WiFiEventHandler gotIpEventHandler, disconnectedEventHandler;
bool flag=true;

SimpleList<uint32_t> nodes;
String getNodeIdAsString(void);
static void mqttBrokerDataCb(uint32_t *client /* we can ignore this */, const char *topic, uint32_t topic_len, const char *data, uint32_t lengh);
static void meshReceivedCb(const uint32_t &from, const String &msg);
static void mqttClientDataCb(uint32_t *args, const char* topic, uint32_t topic_len, const char *data, uint32_t data_len);
static void mqttClientConnectedCb(uint32_t *args);
static void mqttClientdisconnectedCb(uint32_t *args);
static void mqttClientPublishedCb(uint32_t *args);
public:

void mqttBrokerStart(void);
void mqttBrokerPublish(const char*topic,const char*data);
void mqttBrokerStop(void);
void mqttClientInit(void);
void mqttClientConnect(void);
void mqttClientDisconnect(void);
void mqttClientPublish(const char* topic,const char* data);
void meshInit(void);
void meshUpdate(void);





};
extern WLConnection WLConnectionManger;