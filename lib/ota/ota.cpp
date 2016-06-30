#include "ota.h"

void init_ota(void)
{
    ArduinoOTA.onStart([]() {
        Serial.println("Start");
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
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

void ConfigureWifi(void)
{
    // Serial.println("Configuring Wifi");

    // WiFi.begin("WLAN", "password");
    // WiFi.begin(config.ssid.c_str(), config.password.c_str());

    // while (WiFi.status() != WL_CONNECTED) {
    //     Serial.println("WiFi not connected");
    //     delay(500);
    // }

    // if (!config.dhcp) {
    //     WiFi.config(IPAddress(config.IP[0], config.IP[1], config.IP[2], config.IP[3] ),  IPAddress(config.Gateway[0], config.Gateway[1], config.Gateway[2], config.Gateway[3] ) , IPAddress(config.Netmask[0], config.Netmask[1], config.Netmask[2], config.Netmask[3] ));
    // }
}

// void otaInit(void)
// {
//     led(red);

//     for (int i = 0; i < 3; i++) beep(3);

//     WiFi.mode(WIFI_AP);
//     ConfigureWifi();
//     MDNS.begin(host);
//     MDNS.addService("arduino", "tcp", aport);
//     OTA.begin(aport);
//     TelnetServer.begin();
//     TelnetServer.setNoDelay(true);
//     Serial.print("IP address: ");
//     led(green);
//     Serial.println(WiFi.localIP());
//     Serial.println("OTA settings applied");
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
//             Serial.println("Update Begin Error");
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
//                 client.println("OK");
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
//     if (TelnetServer.hasClient()) {
//         if (!Telnet || !Telnet.connected()) {
//             if (Telnet) Telnet.stop();
//             Telnet = TelnetServer.available();
//         } else {
//             WiFiClient toKill = TelnetServer.available();
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
