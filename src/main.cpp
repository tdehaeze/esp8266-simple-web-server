// Import required libraries
#include "main.h";

void setup(void)
{
    Serial.println("Booting");
    configure_console();

    init_wifi();
    init_ota();
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
