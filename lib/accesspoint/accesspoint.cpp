#include <accesspoint.h>

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <stdio.h>
#include <wifi.h>
#include <WString.h>

#include <htmlfunctions.h>
#include <htmlpages.h>

#include <ESP8266Webserver.h>

ESP8266WebServer server_esp(80);

void initAccessPoint(void)
{
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(getDeviceName().c_str());

    Serial.printf("AP name: %s\n", getDeviceName().c_str());
    Serial.printf("AP IP address: %s\n", WiFi.softAPIP().toString().c_str());

    server_esp.on("/",              [](){ server_esp.send(200, "text/html", PAGE_INDEX); });
    server_esp.on("/style.css",     [](){ server_esp.send(200, "text/css", PAGE_STYLE); });
    server_esp.on("/script.js",     [](){ server_esp.send(200, "text/javascript", PAGE_SCRIPT); });
    server_esp.on("/config.html",   [](){ server_esp.send(200, "text/html", PAGE_CONFIG); });
    server_esp.on("/info.html",     [](){ server_esp.send(200, "text/html", PAGE_INFO); });
    server_esp.on("/general.html",  [](){ server_esp.send(200, "text/html", PAGE_GENERAL); });
    server_esp.on("/value.html",  [](){ server_esp.send(200, "text/html", PAGE_VALUE); });

    server_esp.on("/post/connection/form", urlPostConnectionForm);

    server_esp.on("/get/devicename", urlGetDeviceName);
    server_esp.on("/get/connection/info", urlGetConnectionInfo);
    server_esp.on("/get/connection/form", urlGetConnectionForm);
    server_esp.on("/get/connection/state", urlGetConnectionState);
    server_esp.on("/get/networks", urlGetNetworks);
    server_esp.on("/get/networks", urlGetNetworks);
    server_esp.on("/get/pin/value", urlGetPinValue);

    server_esp.onNotFound([](){
        server_esp.sendHeader("Location", String("/"), true);
        server_esp.send(302, "text/plain", "");
    });

    server_esp.begin();

    Serial.printf("HTTP server started\n");
}
