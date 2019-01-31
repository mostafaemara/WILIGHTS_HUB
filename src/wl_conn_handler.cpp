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

        mesh.sendBroadcast(sdata, false);
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
    case 500:

        mqtt_broker_publish(TOPIC_NODE_HANDSHAKE, msg.c_str());
        

        Serial.print("\n -----------------------------------------MESH----------------------------------------------\n");
        Serial.printf(" \n FROM = %d \n", from);
        Serial.print("\n ------------------------------------------------------------------------------------------\n");
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
        Serial.print("My COde Station connected, IP: ");

        // Move the cursor to the next line and print

        //myBroker.init();
        //myBroker.subscribe("#");
        mqtt_broker_start(data_callback);

        Serial.println(WiFi.localIP());
        if (MDNS.begin("dark"))
        { //Start mDNS with name esp8266
            Serial.println("MDNS started");
            MDNS.addService("darkblue", "tcp", 4500);
            MDNS.addServiceTxt("_darkblue", "_tcp", "work", "?");
        }
    });

    disconnectedEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected &event) {
        Serial.println("My COde Station disconnected");
    });
}