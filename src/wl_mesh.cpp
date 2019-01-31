#include"wl_mesh.h"
painlessMesh  mesh;

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
void mqtt_init(void){


     myBroker.init();
myBroker.subscribe("#");

}

void receivedCallback( const uint32_t &from, const String &msg ) {
uint32_t messegeid=json_extract_messege_id(msg);
switch (messegeid)
{
  case 500:
  myBroker.publish("base/node/handshake",msg.c_str(),0);
  Serial.print("\n -----------------------------------------MESH----------------------------------------------\n");
    Serial.printf(" \n FROM = %d \n",from);
    Serial.print("\n ------------------------------------------------------------------------------------------\n");
    /* code */
    break;

  default:
    break;
} 
 


 

}
void mesh_init(void){
    char nodeid[32];
 sprintf(nodeid,"%d",ESP.getChipId());
 String ssid=eeprom_read_ssid();
  String pwd=eeprom_read_password();
  mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION);  // set before init() so that you can see startup messages

  mesh.init(nodeid,nodeid, MESH_PORT,WIFI_AP_STA,6);
  mesh.onReceive(&receivedCallback);

 
mesh.stationManual(ssid.c_str(),pwd.c_str());
mesh.setRoot(true);



}
void mesh_update(void){

 if(esptouch_done()){
  mesh.update();
  }

}