//#ifndef WL_MESH_H
//#define WL_MESH_H


#include"painlessMesh.h"
#include"uMQTTBroker.h"
#include"wl_eeprom.h"
#include"wl_esptouch.h"
#include"wl_json.h"
#define TOPIC_APP_HANDSHAKE "base/app/handshake"
#define TOPIC_APP_COMMAND "base/app/cmd"
#define TOPIC_NODE_HANDSHAKE "base/node/handshake"
#define   MESH_PORT       5555
void mesh_init(receivedCallback_t receivedCallback);
void mesh_update(void);
void mqtt_init(void);
extern  painlessMesh mesh;
//#endif