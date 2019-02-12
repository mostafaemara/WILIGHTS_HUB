#include "wl_conn_handler.h"

WLConnection WLConnectionManger;

void WLConnection::meshInit(void)
{
  led_start_blink(500);
  String nodeid;
  nodeid=getNodeIdAsString();
  Serial.printf(nodeid.c_str());
 
  String ssid = eeprom_read_ssid();
  String pwd = eeprom_read_password();
  mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION); // set before init() so that you can see startup messages

  mesh.init(nodeid.c_str(),nodeid.c_str(), MESH_PORT, WIFI_AP_STA, 6);
  mesh.onReceive(meshReceivedCb);

  mesh.stationManual(ssid.c_str(), pwd.c_str());
  mesh.setRoot(true);
}

void WLConnection::meshUpdate(void){



  if (esptouch_done())
  {
    mesh.update();
         nodes=mesh.getNodeList();

if(nodes.size()!=0){
if(flag){
led_start_blink(2000);
flag=false;
}
}else{
if(flag==false){
led_start_blink(500);
flag=true;
}

}
  }



}
String WLConnection::getNodeIdAsString(void){




 char nodeid[32];
  sprintf(nodeid, "%d", ESP.getChipId());
  return nodeid;




}
void WLConnection::mqttBrokerStart(void){

MQTT_server_onData(mqttBrokerDataCb);
MQTT_server_start(MQTT_SERVER_PORT, MQTT_SERVER_MAX_CLIENTS,MQTT_SERVER_MAX_TOPICS);
MQTT_local_subscribe((uint8_t*)MQTT_ALL_TOPICS,0);

}
void WLConnection::mqttBrokerPublish(const char* topic,const char* data){
    uint16_t data_len=strlen(data);
MQTT_local_publish((uint8_t*)topic,(uint8_t*)data,data_len,0,0);


}
void WLConnection::mqttBrokerStop(void){


MQTT_server_cleanupClientCons();

}
void WLConnection::mqttClientInit(void)
{
    MQTT_InitConnection(&wlMqttClient,(u8_t*) MQTT_CLIENT_HOST, MQTT_CLIENT_PORT,0);
     String nodeid;
  nodeid=getNodeIdAsString();
if ( !MQTT_InitClient(&wlMqttClient,(u8_t*) nodeid.c_str(), (u8_t*)MQTT_CLIENT_USER,(u8_t*) MQTT_CLIENT_PASS, MQTT_KEEPALIVE, MQTT_CLIENT_CLEAN_SESSION) )
  {
  MQTT_INFO("\n MQTT: FAILD TO INIT MQTT CLIENT \n");
    return;
  }
 // MQTT_InitLWT(&mqttClient, "/lwt", "offline", 0, 0);
  MQTT_OnConnected(&wlMqttClient, mqttClientConnectedCb);
  MQTT_OnDisconnected(&wlMqttClient,mqttClientdisconnectedCb);
  MQTT_OnPublished(&wlMqttClient, mqttClientPublishedCb);
  MQTT_OnData(&wlMqttClient, mqttClientDataCb);

}
void WLConnection::mqttClientConnect(void){

 MQTT_Connect(&wlMqttClient);

}
void WLConnection::mqttClientPublish(const char* topic,const char* data){
uint32_t data_len=strlen(data);

MQTT_Publish(&wlMqttClient,topic,data,data_len,0,0);

}
void WLConnection::mqttClientDisconnect(void){

 MQTT_Disconnect(&wlMqttClient);

}
void WLConnection::mqttBrokerDataCb(uint32_t *client /* we can ignore this */, const char *topic, uint32_t topic_len, const char *data, uint32_t lengh){


    char topic_str[topic_len + 1];
    os_memcpy(topic_str, topic, topic_len);
    topic_str[topic_len] = '\0';

    char data_str[lengh + 1];
    os_memcpy(data_str, data, lengh);
    data_str[lengh] = '\0';
    String sdata = data_str;
    if ((strcmp(TOPIC_APP_HANDSHAKE, topic_str)) == 0)
    {
uint32_t messegeid = json_extract_messege_id(sdata);
if(messegeid==MESSEGE_ID_HANDSHAKE){
        mesh.sendBroadcast(sdata, false);
}
    }
    else if ((strcmp(TOPIC_APP_COMMAND, topic_str)) == 0)
    {

        uint32_t nodeid = json_extract_node_id(sdata);
        mesh.sendSingle(nodeid, sdata);
    }

  

}

void WLConnection::mqttClientDataCb(uint32_t *args, const char* topic, uint32_t topic_len, const char *data, uint32_t data_len)
{
  
 
    char topic_str[topic_len + 1];
    os_memcpy(topic_str, topic, topic_len);
    topic_str[topic_len] = '\0';

    char data_str[data_len + 1];
    os_memcpy(data_str, data, data_len);
    data_str[data_len] = '\0';
    String sdata = data_str;
    if ((strcmp(TOPIC_APP_HANDSHAKE, topic_str)) == 0)
    {
uint32_t messegeid = json_extract_messege_id(sdata);
if(messegeid==MESSEGE_ID_HANDSHAKE){
        mesh.sendBroadcast(sdata, false);
}
    }
    else if ((strcmp(TOPIC_APP_COMMAND, topic_str)) == 0)
    {

        uint32_t nodeid = json_extract_node_id(sdata);
        mesh.sendSingle(nodeid, sdata);
    }

  
}
void WLConnection::mqttClientConnectedCb(uint32_t *args)
{
  MQTT_Client* client = (MQTT_Client*)args;

  MQTT_Subscribe(client,MQTT_TOPIC_APP_HANDSHAKE, 0);

  MQTT_Subscribe(client,MQTT_TOPIC_APP_COMMAND, 0);
 
 




}

void WLConnection::mqttClientdisconnectedCb(uint32_t *args)
{
    MQTT_Client* client = (MQTT_Client*)args;




}

 void WLConnection::mqttClientPublishedCb(uint32_t *args)
{
  MQTT_Client* client = (MQTT_Client*)args;

}





void WLConnection::meshReceivedCb(const uint32_t &from, const String &msg)
{
    uint32_t messegeid = json_extract_messege_id(msg);
    switch (messegeid)
    {
    case MESSEGE_ID_NODE_INFO:
WLConnectionManger.mqttBrokerPublish(TOPIC_NODE_HANDSHAKE, msg.c_str());
       
     WLConnectionManger.mqttClientPublish(TOPIC_NODE_HANDSHAKE,msg.c_str());

        
        /* code */
        break;

    default:
        break;
    }
}
