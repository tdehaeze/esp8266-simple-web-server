#ifndef ACCESSPOINT_H_INCLUDED
#define ACCESSPOINT_H_INCLUDED

#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

#include <Arduino.h> // For Serial
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <stdio.h>
#include <wifi.h>
#include <string>

// #include "confignetwork.h"
#include "Page_Root.h"
#include "Page_Admin.h"
#include "Page_Script.js.h"
#include "Page_Style.css.h"
#include "Page_Information.h"
#include "Page_General.h"
#include "Page_NetworkConfiguration.h"

#define SSID "ESP8266"

void init_accesspoint(void);

#endif /* ACCESSPOINT_H_INCLUDED */
