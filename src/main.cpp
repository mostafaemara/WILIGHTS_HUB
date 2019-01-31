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
#include"wl_conn_handler.h"

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










void setup() {
    Serial.begin(115200);
conn_handler_init();
 esptouch_init();
//mesh_init();
 pinMode(LED, OUTPUT);

 
 
  
  
 

 

  


  
}

void loop() {
  mesh_update();
  // it will run mesh scheduler as well
 
}






