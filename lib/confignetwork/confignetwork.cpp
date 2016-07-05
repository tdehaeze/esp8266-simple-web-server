#include <confignetwork.h>

#include <Arduino.h>
#include <EEPROM.h>
#include <eepromutil.h>

serverStruct config_server;

void initConfig(void)
{
    resetConfig();
    readConfig();
}

void writeConfig(void)
{
    Serial.printf("Writing Config\n");

    setConfigMarker();

    writeStringToEEPROM(64, config_server.ssid);
    writeStringToEEPROM(96, config_server.password);

    // EEPROM.write(16, config_server.dhcp);
    // EEPROM.write(32, config_server.IP[0]);
    // EEPROM.write(33, config_server.IP[1]);
    // EEPROM.write(34, config_server.IP[2]);
    // EEPROM.write(35, config_server.IP[3]);

    EEPROM.commit();
}

void writeDefaultConfig(void)
{
    Serial.printf("Setting default parameters\n");

    config_server.ssid = "";
    config_server.password = "";

    // config_server.dhcp = true;
    // config_server.IP[0] = 192;
    // config_server.IP[1] = 168;
    // config_server.IP[2] = 1;
    // config_server.IP[3] = 100;

    writeConfig();
    deleteConfigMarker();
}

void readConfig(void)
{
    Serial.printf("Reading Configuration\n");

    if (isConfigMarker()) {
        Serial.printf("Configurarion found!\n");

        config_server.ssid = readStringFromEEPROM(64);
        config_server.password = readStringFromEEPROM(96);

        Serial.printf("ssid : %s\n", config_server.ssid.c_str());
        Serial.println(config_server.ssid);
        Serial.printf("password : %s\n", config_server.password.c_str());

        // config_server.dhcp = EEPROM.read(16);
        // config_server.IP[0] = EEPROM.read(32);
        // config_server.IP[1] = EEPROM.read(33);
        // config_server.IP[2] = EEPROM.read(34);
        // config_server.IP[3] = EEPROM.read(35);
    } else {
        Serial.printf("Configurarion not found!\n");

        writeDefaultConfig();
    }
}
