#include <Arduino.h>
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
    delay(1000);
    initConsole();
    initEeprom();
    initConfig();
    initAccessPoint();
    initWifiSTA();
    initOTA();
}

void initConsole(void)
{
    Serial.begin(115200, SERIAL_8N1);
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
