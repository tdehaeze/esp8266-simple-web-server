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

    // if (otaFlag) {
    //     otaReceive();
    //     // ArduinoOTA.handle();
    // } else {
    //     customLoop();
    // }
}

// int old_heap = ESP.getFreeHeap();
// int old_vcc = ESP.getVcc();
// while (true)
// {
//     int new_heap = ESP.getFreeHeap();
//     if (old_heap != new_heap) {
//         Serial.printf("Free Heap : %i\n", new_heap);
//         old_heap = new_heap;
//     }
//     int new_vcc = ESP.getVcc();
//     if (old_vcc != new_vcc) {
//         Serial.printf("Vcc : %i\n", new_vcc);
//         old_vcc = new_vcc;
//     }
// }
