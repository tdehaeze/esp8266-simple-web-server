#ifndef ACCESSPOINT_H_INCLUDED
#define ACCESSPOINT_H_INCLUDED

#include <ESP8266WebServer.h>
extern ESP8266WebServer server_esp;

#ifdef __cplusplus
extern "C" {
#endif

void init_accesspoint(void);

#ifdef __cplusplus
}
#endif

#endif /* ACCESSPOINT_H_INCLUDED */
