#ifndef WIFI_H_INCLUDED
#define WIFI_H_INCLUDED

void init_wifi(void);
int scan_network(void);
int connect_to_AP(const char* ssid_ap, const char* password_ap);

#endif /* WIFI_H_INCLUDED */
