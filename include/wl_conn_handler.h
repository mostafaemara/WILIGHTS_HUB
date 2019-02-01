#ifndef WL_CONN_HANDLER_H
#define WL_CONN_HANDLER_H

#include"wl_mesh.h"
#include"wl_mqtt.h"
#include "wl_mdns.h"
#include "wl_debug.h"
#include"wl_led.h"
#if defined(CONN_HANDLER_DEBUG_ON)
#define CONN_HANDLER_INFO(format, ...) Serial.printf(format, ##__VA_ARGS__)
#else
#define CONN_HANDLER_INFO(format, ...)
#endif
void conn_handler_init(void);
#endif