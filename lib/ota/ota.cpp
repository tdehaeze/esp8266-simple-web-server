#include <ota.h>

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <confignetwork.h>

void initOTA(void)
{
    ArduinoOTA.onStart([]() {
        Serial.printf("Start\n");
    });
    ArduinoOTA.onEnd([]() {
        Serial.printf("End\n");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: \n", error);
        if (error == OTA_AUTH_ERROR) Serial.printf("Auth Failed\n");
        else if (error == OTA_BEGIN_ERROR) Serial.printf("Begin Failed\n");
        else if (error == OTA_CONNECT_ERROR) Serial.printf("Connect Failed\n");
        else if (error == OTA_RECEIVE_ERROR) Serial.printf("Receive Failed\n");
        else if (error == OTA_END_ERROR) Serial.printf("End Failed\n");
    });

    ArduinoOTA.begin();
}

//------------------- OTA ---------------------------------------

// #include <ESP8266mDNS.h>
// #include <WiFiUdp.h>
// #include <WiFiClient.h>
// // TODO => where does the Update object comes from ?
// WiFiServer TelnetServer(aport);
// WiFiUDP OTA;
// WiFiClient Telnet;

// void otaInit(void)
// {
//     led(red);

//     for (int i = 0; i < 3; i++) beep(3);

//     WiFi.mode(WIFI_AP);
//     ConfigureWifi();
//     MDNS.begin(host);
//     MDNS.addService("arduino", "tcp", aport);
//     OTA.begin(aport);
//     Telnetserver.begin();
//     Telnetserver.setNoDelay(true);
//     Serial.print("IP address: ");
//     led(green);
//     Serial.println(WiFi.localIP());
//     Serial.printf("OTA settings applied\n");
// }

// void otaReceive(void)
// {
//     if (OTA.parsePacket()) {
//         IPAddress remote = OTA.remoteIP();
//         int cmd  = OTA.parseInt();
//         int port = OTA.parseInt();
//         int size   = OTA.parseInt();

//         Serial.print("Update Start: ip:");
//         Serial.print(remote);
//         Serial.printf(", port:%d, size:%d\n", port, size);
//         uint32_t startTime = millis();

//         WiFiUDP::stopAll();

//         if (!Update.begin(size)) {
//             Serial.printf("Update Begin Error\n");
//             return;
//         }

//         WiFiClient client;
//         if (client.connect(remote, port)) {
//             uint32_t written;
//             while (!Update.isFinished()) {
//                 written = Update.write(client);
//                 if (written > 0) client.print(written, DEC);
//             }
//             Serial.setDebugOutput(false);

//             if (Update.end()) {
//                 client.printf("OK\n");
//                 Serial.printf("Update Success: %u\nRebooting...\n", millis() - startTime);
//                 ESP.restart();
//             } else {
//                 Update.printError(client);
//                 Update.printError(Serial);
//             }
//         } else {
//             Serial.printf("Connect Failed: %u\n", millis() - startTime);
//         }
//     }
//     //IDE Monitor (connected to Serial)
//     if (Telnetserver.hasClient()) {
//         if (!Telnet || !Telnet.connected()) {
//             if (Telnet) Telnet.stop();
//             Telnet = Telnetserver.available();
//         } else {
//             WiFiClient toKill = Telnetserver.available();
//             toKill.stop();
//         }
//     }
//     if (Telnet && Telnet.connected() && Telnet.available()) {
//         while (Telnet.available()) Serial.write(Telnet.read());
//     }
//     if (Serial.available()) {
//         size_t len = Serial.available();
//         uint8_t * sbuf = (uint8_t *)malloc(len);
//         Serial.readBytes(sbuf, len);
//         if (Telnet && Telnet.connected()) {
//             Telnet.write((uint8_t *)sbuf, len);
//             yield();
//         }
//         free(sbuf);
//     }
// }
