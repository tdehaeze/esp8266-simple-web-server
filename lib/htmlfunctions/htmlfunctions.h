#ifndef HTMLFUNCTIONS_H_INCLUDED
#define HTMLFUNCTIONS_H_INCLUDED

#include <Arduino.h> // For Serial
#include <confignetwork.h>
#include <accesspoint.h>
#include <helpers.h>
#include <ota.h>
#include <WString.h>

void send_devicename_value_html(void);
void send_general_html(void);
void send_general_configuration_values_html(void);
String GetMacAddress(void);
void send_information_values_html(void);
bool checkRange(String Value);
void send_network_configuration_html(void);
void send_network_configuration_values_html(void);
void send_connection_state_values_html(void);
void sendRootPage(void);

#endif /* HTMLFUNCTIONS_H_INCLUDED */
