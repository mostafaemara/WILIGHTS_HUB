#include "json.h"




String json_creat_node_info_messege(String state){
DynamicJsonBuffer  jsonBuffer(5000);
JsonObject& root = jsonBuffer.createObject();
String json;
root["messegeid"]=500;
 root["nodeid"]=ESP.getChipId();
 root["nodestate"]=state;
  root["relay1"]=2;
  root["relay2"]=2;
  root["relay3"]=2;
  root["relay4"]=2;
  
  root.prettyPrintTo(json);
  jsonBuffer.clear();
 
  return json;

}
int json_extract_messege_id(String json){
  DynamicJsonBuffer  jsonBuffer(5000);

JsonObject& root = jsonBuffer.parseObject(json);
Serial.printf(" \n JSON STRING %s",json.c_str());
jsonBuffer.clear();
if (root.success()) {
   
int messegeid=root["messegeid"];


    return messegeid;
  }else{

      return -1;
  }


}
uint32_t json_extract_node_id(String json){
  DynamicJsonBuffer  jsonBuffer(5000);

JsonObject& root = jsonBuffer.parseObject(json);
Serial.printf(" \n JSON STRING %s",json.c_str());
jsonBuffer.clear();
if (root.success()) {
   
uint32_t nodeid=root["nodeid"];


    return nodeid;
  }else{

      return -1;
  }


}
void json_extract_node_cmd_messege(String json,int*relayno,int*cmd){
DynamicJsonBuffer  jsonBuffer(5000);
 
JsonObject& root = jsonBuffer.parseObject(json);
if (root.success()) {
   
*cmd=root["cmd"];
*relayno=root["relayno"];


  }
  else{

*cmd=-1;
*relayno=-1;

  }
jsonBuffer.clear();

}