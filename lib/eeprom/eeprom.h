#ifndef EEPROM_H_INCLUDED
#define EEPROM_H_INCLUDED

#include <Arduino.h> // For Serial
#include <EEPROM.h>
#include <WString.h>

void init_eeprom(void);
void WriteStringToEEPROM(int beginaddress, String string);
String ReadStringFromEEPROM(int beginaddress);
void storeSSID(char* ssid_to_store);
void storePassword(char* password_to_store);
String getSSID(void);
String getPassword(void);
void EEPROMWritelong(int address, long value);
long EEPROMReadlong(long address);


#endif /* EEPROM_H_INCLUDED */
