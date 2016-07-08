#include <wifi.h>

#include <Arduino.h>
#include <confignetwork.h>
#include <ESP8266WiFi.h>
#include <eepromutil.h>

// WL_NO_SHIELD        = 255,
// WL_IDLE_STATUS      = 0,
// WL_NO_SSID_AVAIL    = 1,
// WL_SCAN_COMPLETED   = 2,
// WL_CONNECTED        = 3,
// WL_CONNECT_FAILED   = 4,
// WL_CONNECTION_LOST  = 5,
// WL_DISCONNECTED     = 6

void initWifiSTA(void)
{
    if (isConfigMarker()) {
        Serial.printf("There is a configuration => try to connect to AP\n");
        connectToWifi();
        WiFi.setAutoConnect(true);
        WiFi.setAutoReconnect(true);
    } else {
        Serial.printf("There is no configuration => disconnect\n");
        // WiFi.disconnect(false);
    }
}

void connectToWifi(void)
{
    Serial.printf("Try to connect to %s\n", config_server.ssid.c_str());
    Serial.printf("With the following password %s\n", config_server.password.c_str());
    WiFi.begin(config_server.ssid.c_str(), config_server.password.c_str());
}

int getWifiStatus(void)
{
    return WiFi.status();
}

String getWifiSsid(void)
{
    return WiFi.SSID();
}

int scanNetwork(void)
{
    // WiFi.disconnect();
    Serial.printf("scan start\n");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();

    Serial.printf("scan done\n");

    return n;
}

void printWifiDebug(void)
{
    Serial.printf("==== WIFI DEBUG ====\n");
    WiFi.printDiag(Serial);
    Serial.printf("==== WIFI DEBUG ====\n");
}

void downloadFile(void)
{
    const char* host = "192.168.1.167";
    Serial.print("connecting to ");
    Serial.println(host);

    unsigned long StartTime = millis();

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 8080;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    // We now create a URI for the request
    String url = "/image";

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    while(client.available()) {
        yield();
    }

    unsigned long CurrentTime = millis();
    Serial.println(CurrentTime - StartTime);
}

// int connect_to_AP(const char* ssid_ap, const char* password_ap)
// {
//     WiFi.begin(ssid_ap, password_ap);

//     // TODO => should try for 5 seconds, and if still no connection => return 0;
//     if (WiFi.waitForConnectResult() == WL_CONNECTED) {
//         Serial.printf("Ready\n");
//         Serial.printf("IP address: %s\n", WiFi.localIP());
//         return 1;
//     } else {
//         return 0;
//     }
// }
