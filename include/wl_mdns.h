#include <ESP8266mDNS.h>
#include"wl_debug.h"
#define MDNS_HOST_NAME "mse"
#define MDNS_SERVICE_NAME "darkblue"
#define MDNS_SERVICE_TYPE "tcp"
#define MDNS_SERVICE_PORT 4500
#if defined(MDNS_DEBUG_ON)
#define MDNS_INFO( format, ... ) Serial.printf( format, ## __VA_ARGS__ )
#else
#define MDNS_INFO( format, ... )
#endif
void mdns_start(void);