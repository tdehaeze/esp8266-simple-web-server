#ifndef WIFI_H_INCLUDED
#define WIFI_H_INCLUDED

#include <WString.h>

void initWifiSTA(void);
void connectToWifi(void);
int getWifiStatus(void);
String getWifiSsid(void);
int scanNetwork(void);
void printWifiDebug(void);

#endif /* WIFI_H_INCLUDED */
