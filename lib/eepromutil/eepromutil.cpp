#include <eepromutil.h>

#include <Arduino.h>
#include <EEPROM.h>

const int ssid_location = 300;
const int password_location = 400;

void initEeprom(void)
{
    EEPROM.begin(512);
}

void writeStringToEEPROM(int beginaddress, String string)
{
    char charBuf[string.length() + 1];
    string.toCharArray(charBuf, string.length() + 1);
    for (int t =  0; t < sizeof(charBuf); t++) {
        EEPROM.write(beginaddress + t, charBuf[t]);
    }
}

String readStringFromEEPROM(int beginaddress)
{
    volatile uint8_t counter = 0;
    char rChar;
    String retString = "";
    while (1) {
        rChar = EEPROM.read(beginaddress + counter);
        if (rChar == 0) break;
        if (counter > 31) break;
        counter++;
        retString.concat(rChar);
    }
    return retString;
}

void storeSSID(char* ssid_to_store)
{
    Serial.printf("EEPROM ssid was %s and is now %s\n", readStringFromEEPROM(ssid_location).c_str(), ssid_to_store);
    writeStringToEEPROM(ssid_location, String(ssid_to_store));
    EEPROM.commit();
}

void storePassword(char* password_to_store)
{
    Serial.printf("EEPROM password was %s and is now %s\n", readStringFromEEPROM(password_location).c_str(), password_to_store);
    writeStringToEEPROM(password_location, String(password_to_store));
    EEPROM.commit();
}

String getSSID(void)
{
    return readStringFromEEPROM(ssid_location);
}

String getPassword(void)
{
    return readStringFromEEPROM(password_location);
}

void setConfigMarker(void)
{
    EEPROM.write(0, 'C');
    EEPROM.write(1, 'F');
    EEPROM.write(2, 'G');
    EEPROM.commit();
}

void deleteConfigMarker(void)
{
    Serial.printf("deleteConfigMarker\n");
    EEPROM.write(0, '0');
    EEPROM.write(1, '0');
    EEPROM.write(2, '0');
    EEPROM.commit();
}

int isConfigMarker(void)
{
    if (EEPROM.read(0) == 'C' && EEPROM.read(1) == 'F' && EEPROM.read(2) == 'G') {
        return 1;
    } else {
        return 0;
    }
}

void resetConfig(void)
{
    // char* lapin = "";
    // storeSSID(lapin);
    // Serial.printf("isConfigMarker() : %i\n", isConfigMarker());
    // Serial.printf("getSSID().length() : %i\n", getSSID().length());
    if (isConfigMarker() && getSSID().length() == 0) {
        deleteConfigMarker();
    }
}

// void EEPROMWritelong(int address, long value)
// {
//     uint8_t four = (value & 0xFF);
//     uint8_t three = ((value >> 8) & 0xFF);
//     uint8_t two = ((value >> 16) & 0xFF);
//     uint8_t one = ((value >> 24) & 0xFF);

//     //Write the 4 bytes into the eeprom memory.
//     EEPROM.write(address, four);
//     EEPROM.write(address + 1, three);
//     EEPROM.write(address + 2, two);
//     EEPROM.write(address + 3, one);
// }

// long EEPROMReadlong(long address)
// {
//     //Read the 4 bytes from the eeprom memory.
//     long four = EEPROM.read(address);
//     long three = EEPROM.read(address + 1);
//     long two = EEPROM.read(address + 2);
//     long one = EEPROM.read(address + 3);

//     //Return the recomposed long by using bitshift.
//     return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
// }
