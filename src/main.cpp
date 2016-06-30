// Import required libraries
#include "main.h"

void setup(void)
{
    configure_console();
    // init_wifi();
    // scan_network();
    // init_ota();
    init_accesspoint();
}

void configure_console(void)
{
    // Start Serial
    Serial.begin(115200);
}

void loop(void)
{
    // yield(); // For ESP8266 to not dump

    // if (otaFlag) {
    //     otaReceive();
    //     // ArduinoOTA.handle();
    // } else {
    //     customLoop();
    // }
}
