//#ifndef WL_MESH_H
//#define WL_MESH_H


#include"painlessMesh.h"
#include"uMQTTBroker.h"
#include"wl_eeprom.h"
#include"wl_esptouch.h"
#include"wl_json.h"
#define   MESH_PORT       5555
void mesh_init(void);
void mesh_update(void);
void mqtt_init(void);
//#endif