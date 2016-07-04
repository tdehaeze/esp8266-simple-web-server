#include <confignetwork.h>

#include <Arduino.h> // For Serial
#include <EEPROM.h>
#include <eepromutil.h>

t_server config_server;

void writeConfig(void)
{
    Serial.println("Writing Config");
    EEPROM.write(0, 'C');
    EEPROM.write(1, 'F');
    EEPROM.write(2, 'G');

    EEPROM.write(16, config_server.dhcp);

    EEPROM.write(32, config_server.IP[0]);
    EEPROM.write(33, config_server.IP[1]);
    EEPROM.write(34, config_server.IP[2]);
    EEPROM.write(35, config_server.IP[3]);

    EEPROM.write(36, config_server.Netmask[0]);
    EEPROM.write(37, config_server.Netmask[1]);
    EEPROM.write(38, config_server.Netmask[2]);
    EEPROM.write(39, config_server.Netmask[3]);

    EEPROM.write(40, config_server.Gateway[0]);
    EEPROM.write(41, config_server.Gateway[1]);
    EEPROM.write(42, config_server.Gateway[2]);
    EEPROM.write(43, config_server.Gateway[3]);

    WriteStringToEEPROM(64, config_server.ssid);
    WriteStringToEEPROM(96, config_server.password);
    WriteStringToEEPROM(128, config_server.ntpServerName);

    EEPROM.commit();
}

void writeDefaultConfig(void)
{
    Serial.println("Setting default parameters");

    config_server.ssid = "Rtone Cisco"; // SSID of access point
    config_server.password = "0478477078tro";  // password of access point

    config_server.dhcp = true;

    config_server.IP[0] = 192;
    config_server.IP[1] = 168;
    config_server.IP[2] = 1;
    config_server.IP[3] = 100;

    config_server.Netmask[0] = 255;
    config_server.Netmask[1] = 255;
    config_server.Netmask[2] = 255;
    config_server.Netmask[3] = 0;

    config_server.Gateway[0] = 192;
    config_server.Gateway[1] = 168;
    config_server.Gateway[2] = 1;
    config_server.Gateway[3] = 1;

    config_server.ntpServerName = "0.ch.pool.ntp.org";
    config_server.DeviceName = "Not Named";

    writeConfig();
}

bool readConfig(void)
{
    Serial.println("Reading Configuration");

    if (EEPROM.read(0) == 'C' && EEPROM.read(1) == 'F' && EEPROM.read(2) == 'G') {
        Serial.println("Configurarion Found!");
        config_server.dhcp = EEPROM.read(16);

        config_server.IP[0] = EEPROM.read(32);
        config_server.IP[1] = EEPROM.read(33);
        config_server.IP[2] = EEPROM.read(34);
        config_server.IP[3] = EEPROM.read(35);

        config_server.Netmask[0] = EEPROM.read(36);
        config_server.Netmask[1] = EEPROM.read(37);
        config_server.Netmask[2] = EEPROM.read(38);
        config_server.Netmask[3] = EEPROM.read(39);

        config_server.Gateway[0] = EEPROM.read(40);
        config_server.Gateway[1] = EEPROM.read(41);
        config_server.Gateway[2] = EEPROM.read(42);
        config_server.Gateway[3] = EEPROM.read(43);

        config_server.ssid = ReadStringFromEEPROM(64);
        config_server.password = ReadStringFromEEPROM(96);
        config_server.ntpServerName = ReadStringFromEEPROM(128);

        config_server.DeviceName = ReadStringFromEEPROM(306);
        return true;
    } else {
        Serial.println("Configurarion NOT FOUND!");
        return false;
    }
}
