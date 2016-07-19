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

unsigned long previousMillis = 0;

const long interval = 5000;

void setup(void)
{
    delay(1000);
    initConsole();
    initPins();
    initEeprom();
    initConfig();
    initAccessPoint();
    initWifiSTA();
    // initOTA();
}

void initPins(void)
{
    pinMode(A0, INPUT_PULLUP);
}

void initConsole(void)
{
    Serial.begin(115200, SERIAL_8N1);
}

void loop(void)
{
    yield(); // For ESP8266 to not dump
    server_esp.handleClient();

    // unsigned long currentMillis = millis();

    // if (currentMillis - previousMillis >= interval) {
    //     previousMillis = currentMillis;
    //     downloadFile();
    // }

    // if (otaFlag) {
    //     otaReceive();
    //     // ArduinoOTA.handle();
    // } else {
    //     customLoop();
    // }
}


