#ifndef CONFIGNETWORK_H_INCLUDED
#define CONFIGNETWORK_H_INCLUDED

#include <WString.h>

struct serverStruct {
    String      ssid;
    String      password;
    uint8_t     IP[4];
    uint8_t     Netmask[4];
    uint8_t     Gateway[4];
    bool        dhcp;
};

extern serverStruct config_server;

void initConfig(void);
void writeConfig(void);
void writeDefaultConfig(void);
void readConfig(void);

#endif /* CONFIGNETWORK_H_INCLUDED */
