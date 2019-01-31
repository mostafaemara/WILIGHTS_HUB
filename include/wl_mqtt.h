#include"uMQTTBroker.h"
#define MQTT_SERVER_PORT 1883
#define MQTT_SERVER_MAX_CLIENTS 10
#define MQTT_SERVER_MAX_TOPICS 10


void mqtt_broker_start(MqttDataCallback mqttdatacb);

void mqtt_broker_publish(uint8_t *topic,uint8_t *data);

void mqtt_broker_stop(void);



