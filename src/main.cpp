

#include"wl_mesh.h"
#include <Arduino.h>



#include"wl_esptouch.h"


#include"wl_conn_handler.h"


WiFiEventHandler gotIpEventHandler, disconnectedEventHandler;







void setup() {
    Serial.begin(115200);
WLConnectionManger.meshInit();
 esptouch_init();



 
   gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP &event) {
       
        

      WLConnectionManger.mqttBrokerStart();
        WLConnectionManger.mqttClientInit();
        WLConnectionManger.mqttClientConnect();

        //Serial.println(WiFi.localIP());
      mdns_start();
    });

    disconnectedEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected &event) {
   
    });
  
  
 

 

  


  
}

void loop() {
WLConnectionManger.meshUpdate();
  
}






