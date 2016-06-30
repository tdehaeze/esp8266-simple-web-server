#ifndef CONFIGNETWORK_H_INCLUDED
#define CONFIGNETWORK_H_INCLUDED

#include <Arduino.h> // For Serial
#include "eeprom.h"
#include "WString.h"

struct strConfig {
    String      ssid;
    String      password;
    uint8_t     IP[4];
    uint8_t     Netmask[4];
    uint8_t     Gateway[4];
    bool        dhcp;
    String      ntpServerName;
    String      DeviceName;
} config;

void writeConfig(void);
void writeDefaultConfig(void);
bool readConfig(void);

#endif /* CONFIGNETWORK_H_INCLUDED */
