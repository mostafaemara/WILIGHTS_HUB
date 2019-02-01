#include"wl_mdns.h"
void mdns_start(void){




   if (MDNS.begin(MDNS_HOST_NAME))
        { //Start mDNS with name esp8266
               MDNS_INFO("\n MDNS: STARTED WITH HOST NAME = %s \n",MDNS_HOST_NAME);
            MDNS.addService(MDNS_SERVICE_NAME,MDNS_SERVICE_TYPE,MDNS_SERVICE_PORT);
          MDNS_INFO("\n MDNS: STARTED SERVICE   NAME = %s  OF TYPE =%s ON PORT = %d\n",MDNS_SERVICE_NAME,MDNS_SERVICE_TYPE,MDNS_SERVICE_PORT);
           
        }else{


MDNS_INFO("\n MDNS: FAILD TO START");


        }





}