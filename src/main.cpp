#include"eeprom.h"
#include <Arduino.h>
#include <painlessMesh.h>
#include "uMQTTBroker.h"
#include "json.h"
#include"esptouch.h"
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include "LiquidCrystal_I2C.h"
#define   LED             2       // GPIO number of connected LED, ON ESP-12 IS GPIO2
#define HOSTNAME "MQTT_Bridge"
#define   STATION_SSID     "NightWings"
#define   STATION_PASSWORD "la2a_la2a_la2a_la2a"
#define   MESH_SSID     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
 // milliseconds LED is on for






void receivedCallback( const uint32_t &from, const String &msg );

 // to control your personal task
painlessMesh  mesh;



 // Prototype
// start with a one second interval






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



void setup() {
 
  
 
 pinMode(LED, OUTPUT);
  Serial.begin(115200);
 
 
  
  
  String ssid=eeprom_read_ssid();
  String pwd=eeprom_read_password();
  Serial.printf("\n SSID FROM EEPROM = %s \n",ssid.c_str());
   Serial.printf("\n Password FROM EEPROM = %s \n",pwd.c_str());

  // Move the cursor 5 characters to the right and


  // Move the cursor to the next line and print
  // WORLD.
  

mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION);  // set before init() so that you can see startup messages

  mesh.init(MESH_SSID, MESH_PASSWORD, MESH_PORT,WIFI_AP_STA,6);
  mesh.onReceive(&receivedCallback);

 
mesh.stationManual(STATION_SSID, STATION_PASSWORD);
mesh.setRoot(true);
 

  


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

void loop() {
  // it will run mesh scheduler as well
  if(esptouch_done()){
  mesh.update();
  }
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
 


 


  // Move the cursor to the next line and print
  // WORLD.

}




