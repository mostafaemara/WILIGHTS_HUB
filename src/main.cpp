#include"wl_eeprom.h"
#include"wl_mesh.h"
#include"wl_mesh.h"
#include <Arduino.h>
#include "painlessMesh.h"
#include "uMQTTBroker.h"
#include "wl_json.h"
#include"wl_esptouch.h"
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>

#define   LED             2       // GPIO number of connected LED, ON ESP-12 IS GPIO2
#define HOSTNAME "MQTT_Bridge"
#define   STATION_SSID     "NightWings"
#define   STATION_PASSWORD "la2a_la2a_la2a_la2a"
#define   MESH_SSID     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
 // milliseconds LED is on for








 // to control your personal task




 // Prototype
// start with a one second interval






WiFiEventHandler gotIpEventHandler, disconnectedEventHandler;



void setup() {
    Serial.begin(115200);
 esptouch_init();
mesh_init();
 pinMode(LED, OUTPUT);

 
 
  
  
 

 

  


 gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP& event)
  {
    mqtt_init();
   Serial.print("My COde Station connected, IP: ");
 

  // Move the cursor to the next line and print
 


  

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
 
}






