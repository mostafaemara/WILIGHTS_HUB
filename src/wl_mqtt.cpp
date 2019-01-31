#include"wl_mqtt.h"


void mqtt_broker_start(MqttDataCallback mqttdatacb){

MQTT_server_onData(mqttdatacb);
MQTT_server_start(MQTT_SERVER_PORT, MQTT_SERVER_MAX_CLIENTS,MQTT_SERVER_MAX_TOPICS);
MQTT_local_subscribe((uint8_t*)MQTT_ALL_TOPICS,0);

}

void mqtt_broker_publish(const char* topic,const char* data){
    uint16_t data_len=strlen(data);
MQTT_local_publish((uint8_t*)topic,(uint8_t*)data,data_len,0,0);


}

void mqtt_broker_stop(void){


MQTT_server_cleanupClientCons();

}