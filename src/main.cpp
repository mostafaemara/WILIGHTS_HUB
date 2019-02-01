

#include"wl_mesh.h"
#include <Arduino.h>



#include"wl_esptouch.h"


#include"wl_conn_handler.h"










void setup() {
    Serial.begin(115200);
conn_handler_init();
 esptouch_init();



 
 
  
  
 

 

  


  
}

void loop() {
  mesh_update();
  
}






