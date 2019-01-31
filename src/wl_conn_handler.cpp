#include"wl_conn_handler.h"



WiFiEventHandler gotIpEventHandler, disconnectedEventHandler;


class myMQTTBroker: public uMQTTBroker
{
public:
    virtual bool onConnect(IPAddress addr, uint16_t client_count) {
      Serial.println(addr.toString()+" connected");
      return true;
    }
    
    virtual bool onAuth(String username, String password) {
      Serial.println("Username/Password: "+username+"/"+password);
      return true;
    }
    
    virtual void onData(String topic, const char *data, uint32_t length) {
      char data_str[length+1];
      os_memcpy(data_str, data, length);
      data_str[length] = '\0';
      String msg=data_str;
  
    if(topic.equals("base/app/handshake")){
 Serial.println("HANDSHAKE topic '"+topic+"' with data '"+(String)data_str+"'");
mesh.sendBroadcast(msg,false);
      
    }else if(topic.equals("base/app/cmd")){

Serial.println("COMMAND topic '"+topic+"' with data '"+(String)data_str+"'");
uint32_t nodeid=json_extract_node_id(msg);
mesh.sendSingle(nodeid,msg);
    }
     
     
      
    }
};
myMQTTBroker myBroker;



void receivedCallback(const uint32_t &from, const String &msg)
{
  uint32_t messegeid = json_extract_messege_id(msg);
  switch (messegeid)
  {
  case 500:
    myBroker.publish("base/node/handshake", msg.c_str(), 0);
    
    Serial.print("\n -----------------------------------------MESH----------------------------------------------\n");
    Serial.printf(" \n FROM = %d \n", from);
    Serial.print("\n ------------------------------------------------------------------------------------------\n");
    /* code */
    break;

  default:
    break;
  }
}




void conn_handler_init(void){
mesh_init(receivedCallback);

 gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP& event)
  {
   
   Serial.print("My COde Station connected, IP: ");
 

  // Move the cursor to the next line and print
 


  
myBroker.init();
myBroker.subscribe("#");
    Serial.println(WiFi.localIP());
     if (MDNS.begin("dark")) {  //Start mDNS with name esp8266
      Serial.println("MDNS started");
      MDNS.addService("darkblue","tcp",4500);
      MDNS.addServiceTxt("_darkblue","_tcp","work","?");
    
    
    }
   
  });

  disconnectedEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected& event)
  {
   Serial.println("My COde Station disconnected");
  });

}