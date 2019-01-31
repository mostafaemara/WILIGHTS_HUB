#include "wl_mesh.h"
 painlessMesh mesh;





String getNodeIdAsString(void){

 char nodeid[32];
  sprintf(nodeid, "%d", ESP.getChipId());
  return nodeid;



}
void mesh_init(receivedCallback_t receivedCallback)
{
  String nodeid;
  nodeid=getNodeIdAsString();
  Serial.printf(nodeid.c_str());
 
  String ssid = eeprom_read_ssid();
  String pwd = eeprom_read_password();
  mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION); // set before init() so that you can see startup messages

  mesh.init(nodeid.c_str(),nodeid.c_str(), MESH_PORT, WIFI_AP_STA, 6);
  mesh.onReceive(receivedCallback);

  mesh.stationManual(ssid.c_str(), pwd.c_str());
  mesh.setRoot(true);
}

void mesh_update(void)
{

  if (esptouch_done())
  {
    mesh.update();
  }
}