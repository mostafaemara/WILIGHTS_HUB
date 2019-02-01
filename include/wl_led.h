#include<Arduino.h>
extern "C" {
#include <osapi.h>
#include "user_interface.h"
#include <ets_sys.h>
}
#define LED 2
void led_start_blink(u32_t delay);
void led_start();
void led_stop(void);