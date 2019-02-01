#include "wl_conn_handler.h"
WiFiEventHandler gotIpEventHandler, disconnectedEventHandler;

void data_callback(uint32_t *client /* we can ignore this */, const char *topic, uint32_t topic_len, const char *data, uint32_t lengh)
{
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



void receivedCallback(const uint32_t &from, const String &msg)
{
    uint32_t messegeid = json_extract_messege_id(msg);
    switch (messegeid)
    {
    case MESSEGE_ID_NODE_INFO:

        mqtt_broker_publish(TOPIC_NODE_HANDSHAKE, msg.c_str());
        

        
        /* code */
        break;

    default:
        break;
    }
}

void conn_handler_init(void)
{
    mesh_init(receivedCallback);

    gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP &event) {
        

        mqtt_broker_start(data_callback);

        Serial.println(WiFi.localIP());
      mdns_start();
    });

    disconnectedEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected &event) {
    
    });
}