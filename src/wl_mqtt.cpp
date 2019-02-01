#include"wl_mqtt.h"
MQTT_Client mqttClient;

void mqtt_broker_start(MqttDataCallback mqttdatacb){

MQTT_server_onData(mqttdatacb);
MQTT_server_start(MQTT_SERVER_PORT, MQTT_SERVER_MAX_CLIENTS,MQTT_SERVER_MAX_TOPICS);
MQTT_local_subscribe((uint8_t*)MQTT_ALL_TOPICS,0);

}
static String getNodeIdAsString(void){

 char nodeid[32];
  sprintf(nodeid, "%d", ESP.getChipId());
  return nodeid;



}

void mqtt_broker_publish(const char* topic,const char* data){
    uint16_t data_len=strlen(data);
MQTT_local_publish((uint8_t*)topic,(uint8_t*)data,data_len,0,0);


}

void mqtt_broker_stop(void){


MQTT_server_cleanupClientCons();

}

void mqtt_client_init(MqttCallback connectcb,MqttCallback disconnectedcb,MqttCallback publishcb,MqttDataCallback datacb)
{
    MQTT_InitConnection(&mqttClient,(u8_t*) MQTT_CLIENT_HOST, MQTT_CLIENT_PORT,0);
     String nodeid;
  nodeid=getNodeIdAsString();
if ( !MQTT_InitClient(&mqttClient,(u8_t*) nodeid.c_str(), (u8_t*)MQTT_CLIENT_USER,(u8_t*) MQTT_CLIENT_PASS, MQTT_KEEPALIVE, MQTT_CLIENT_CLEAN_SESSION) )
  {
  MQTT_INFO("\n MQTT: FAILD TO INIT MQTT CLIENT \n");
    return;
  }
 // MQTT_InitLWT(&mqttClient, "/lwt", "offline", 0, 0);
  MQTT_OnConnected(&mqttClient, connectcb);
  MQTT_OnDisconnected(&mqttClient, disconnectedcb);
  MQTT_OnPublished(&mqttClient, publishcb);
  MQTT_OnData(&mqttClient, datacb);

}
void mqtt_client_connect(void){

 MQTT_Connect(&mqttClient);

}
void mqtt_client_publish(const char* topic,const char* data){
uint32_t data_len=strlen(data);

MQTT_Publish(&mqttClient,topic,data,data_len,0,0);

}
void mqtt_client_disconnect(void){

 MQTT_Disconnect(&mqttClient);

}