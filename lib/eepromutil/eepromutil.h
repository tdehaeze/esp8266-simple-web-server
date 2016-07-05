#ifndef EEPROMUTIL_H_INCLUDED
#define EEPROMUTIL_H_INCLUDED

#include <WString.h>

void initEeprom(void);
void writeStringToEEPROM(int beginaddress, String string);
String readStringFromEEPROM(int beginaddress);
void storeSSID(char* ssid_to_store);
void storePassword(char* password_to_store);
String getSSID(void);
String getPassword(void);
void setConfigMarker(void);
void deleteConfigMarker(void);
int isConfigMarker(void);
void resetConfig(void);

#endif /* EEPROMUTIL_H_INCLUDED */
