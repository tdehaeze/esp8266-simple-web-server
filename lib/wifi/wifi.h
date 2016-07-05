#ifndef WIFI_H_INCLUDED
#define WIFI_H_INCLUDED

void initWifiSTA(void);
int getWifiStatus(void);
int scanNetwork(void);
void printWifiDebug(void);

#endif /* WIFI_H_INCLUDED */
