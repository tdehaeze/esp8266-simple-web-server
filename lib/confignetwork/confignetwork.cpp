#include "confignetwork.h"

void writeConfig(void)
{
    Serial.println("Writing Config");
    EEPROM.write(0, 'C');
    EEPROM.write(1, 'F');
    EEPROM.write(2, 'G');

    EEPROM.write(16, config.dhcp);

    EEPROM.write(32, config.IP[0]);
    EEPROM.write(33, config.IP[1]);
    EEPROM.write(34, config.IP[2]);
    EEPROM.write(35, config.IP[3]);

    EEPROM.write(36, config.Netmask[0]);
    EEPROM.write(37, config.Netmask[1]);
    EEPROM.write(38, config.Netmask[2]);
    EEPROM.write(39, config.Netmask[3]);

    EEPROM.write(40, config.Gateway[0]);
    EEPROM.write(41, config.Gateway[1]);
    EEPROM.write(42, config.Gateway[2]);
    EEPROM.write(43, config.Gateway[3]);

    WriteStringToEEPROM(64, config.ssid);
    WriteStringToEEPROM(96, config.password);
    WriteStringToEEPROM(128, config.ntpServerName);

    EEPROM.commit();
}

void writeDefaultConfig(void)
{
    Serial.println("Setting default parameters");

    config.ssid = "Rtone Cisco"; // SSID of access point
    config.password = "0478477078tro";  // password of access point

    config.dhcp = true;

    config.IP[0] = 192;
    config.IP[1] = 168;
    config.IP[2] = 1;
    config.IP[3] = 100;

    config.Netmask[0] = 255;
    config.Netmask[1] = 255;
    config.Netmask[2] = 255;
    config.Netmask[3] = 0;

    config.Gateway[0] = 192;
    config.Gateway[1] = 168;
    config.Gateway[2] = 1;
    config.Gateway[3] = 1;

    config.ntpServerName = "0.ch.pool.ntp.org";
    config.DeviceName = "Not Named";

    writeConfig();
}

bool readConfig(void)
{
    Serial.println("Reading Configuration");

    if (EEPROM.read(0) == 'C' && EEPROM.read(1) == 'F' && EEPROM.read(2) == 'G') {
        Serial.println("Configurarion Found!");
        config.dhcp = EEPROM.read(16);

        config.IP[0] = EEPROM.read(32);
        config.IP[1] = EEPROM.read(33);
        config.IP[2] = EEPROM.read(34);
        config.IP[3] = EEPROM.read(35);

        config.Netmask[0] = EEPROM.read(36);
        config.Netmask[1] = EEPROM.read(37);
        config.Netmask[2] = EEPROM.read(38);
        config.Netmask[3] = EEPROM.read(39);

        config.Gateway[0] = EEPROM.read(40);
        config.Gateway[1] = EEPROM.read(41);
        config.Gateway[2] = EEPROM.read(42);
        config.Gateway[3] = EEPROM.read(43);

        config.ssid = ReadStringFromEEPROM(64);
        config.password = ReadStringFromEEPROM(96);
        config.ntpServerName = ReadStringFromEEPROM(128);

        config.DeviceName = ReadStringFromEEPROM(306);
        return true;
    } else {
        Serial.println("Configurarion NOT FOUND!");
        return false;
    }
}
