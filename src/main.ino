// Import required libraries
// #include "main.h"

#include <Arduino.h> // For Serial
#include <accesspoint.h>
#include <confignetwork.h>
#include <eepromutil.h>
#include <helpers.h>
#include <htmlfunctions.h>
#include <htmlpages.h>
#include <ota.h>
#include <wifi.h>
#include <confignetwork.h>

void setup(void)
{
    configure_console();
    // init_wifi();
    // scan_network();
    // init_ota();
    // writeDefaultConfig();
    init_accesspoint();
}

void configure_console(void)
{
    // Start Serial
    Serial.begin(115200);
}

void loop(void)
{
    yield(); // For ESP8266 to not dump
    server_esp.handleClient();
    delay(10);

    // if (otaFlag) {
    //     otaReceive();
    //     // ArduinoOTA.handle();
    // } else {
    //     customLoop();
    // }
}
