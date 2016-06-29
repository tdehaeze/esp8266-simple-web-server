// Import required libraries
#include "main.h";

void setup(void)
{
    Serial.println("Booting");
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
    ArduinoOTA.handle();
}
