
#include <painlessMesh.h>

String json_creat_node_info_messege(String state);
int json_extract_messege_id(String json);
void json_extract_node_cmd_messege(String json,int*relayno,int*cmd);
uint32_t json_extract_node_id(String json);