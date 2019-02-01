#include"wl_led.h"

static os_timer_t sw_timer;
 static bool flag=true;
void ICACHE_FLASH_ATTR sw_timer_cb(void){
if(flag){
digitalWrite(LED,HIGH);

flag=false;
}else{

digitalWrite(LED,LOW);
flag=true;
}
   

   }
   void led_start(){
       pinMode(LED,OUTPUT);
os_timer_disarm(&sw_timer);
digitalWrite(LED,LOW);


   }
void led_start_blink(u32_t delay){
   pinMode(LED,OUTPUT);
os_timer_disarm(&sw_timer);
 os_timer_setfn(&sw_timer,(os_timer_func_t *)sw_timer_cb,NULL);
 os_timer_arm(&sw_timer,delay,1);


}
void led_stop(void){



os_timer_disarm(&sw_timer);
digitalWrite(LED,HIGH);
}