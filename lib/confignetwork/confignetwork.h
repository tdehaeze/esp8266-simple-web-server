#ifndef CONFIGNETWORK_H_INCLUDED
#define CONFIGNETWORK_H_INCLUDED

#include <WString.h>

typedef struct s_server {
    String      ssid;
    String      password;
    uint8_t     IP[4];
    uint8_t     Netmask[4];
    uint8_t     Gateway[4];
    bool        dhcp;
    String      ntpServerName;
    String      DeviceName;
} t_server;

void writeConfig(void);
void writeDefaultConfig(void);
bool readConfig(void);

#endif /* CONFIGNETWORK_H_INCLUDED */
