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
    WiFi.softAP(String("ESP8266_" + GetFirstMacAddress()).c_str());

    Serial.printf("AP name: %s\n", String("ESP8266_" + GetFirstMacAddress()).c_str());
    Serial.printf("AP IP address: %s\n", WiFi.softAPIP().toString().c_str());

    server_esp.on("/", [](){
        server_esp.send(200, "text/html", PAGE_INDEX);
    });

    server_esp.on("/favicon.ico", [](){
        server_esp.send (200, "text/html", "");
    });

    server_esp.on("/config.html", send_network_configuration_html);

    server_esp.on("/info.html", [](){
        server_esp.send(200, "text/html", PAGE_INFO);
    });

    server_esp.on("/general.html", send_general_html);

    server_esp.on("/style.css", [](){
        server_esp.send(200, "text/css", PAGE_STYLE);
    });

    server_esp.on("/script.js", [](){
        server_esp.send(200, "text/javascript", PAGE_SCRIPT);
    });

    server_esp.on("/admin/generalvalues", send_general_configuration_values_html);
    server_esp.on("/admin/values", send_network_configuration_values_html);
    server_esp.on("/admin/connectionstate", send_connection_state_values_html);
    server_esp.on("/admin/infovalues", send_information_values_html);
    server_esp.on("/admin/devicename", send_devicename_value_html);

    server_esp.onNotFound([](){
        server_esp.sendHeader("Location", String("/"), true);
        server_esp.send(302, "text/plain", "");
    });

    server_esp.begin();
    Serial.printf("HTTP server started\n");
}
