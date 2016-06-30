#include "wifi.h"

void init_wifi(void)
{
    // WiFi parameters
    const char* ssid = "Rtone Cisco";
    const char* password = "0478477078rto";

    // Connect to WiFi
    WiFi.mode(WIFI_STA);
    connect_to_AP(ssid, password);
}

// WL_IDLE_STATUS      = 0,
// WL_NO_SSID_AVAIL    = 1,
// WL_SCAN_COMPLETED   = 2,
// WL_CONNECTED        = 3,
// WL_CONNECT_FAILED   = 4,
// WL_CONNECTION_LOST  = 5,
// WL_DISCONNECTED     = 6
int connect_to_AP(const char* ssid_ap, const char* password_ap)
{
    WiFi.begin(ssid_ap, password_ap);

    // TODO => should try for 5 seconds, and if still no connection => return 0;
    if (WiFi.waitForConnectResult() == WL_CONNECTED) {
        Serial.println("Ready");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        return 1;
    } else {
        return 0;
    }

}

// void init_server(void)
// {
//     WiFiServer server(80);

//     // Start the server
//     server.begin();
//     Serial.println("Server started");
// }

int scan_network(void)
{
    // WiFi.disconnect();
    Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();

    Serial.println("scan done");

    return n;
}




















// void loop() {
//     // Check if a client has connected
//     WiFiClient client = server.available();
//     if (!client) {
//         return;
//     }

//     // Wait until the client sends some data
//     Serial.println("new client");
//     while(!client.available()){
//         delay(1);
//     }

//     // Read the first line of the request
//     String req = client.readStringUntil('\r');
//     Serial.println(req);
//     client.flush();

//     // Match the request
//     int val;
//     if (req.indexOf("/gpio/0") != -1) {
//         val = 0;
//     } else if (req.indexOf("/gpio/1") != -1) {
//         val = 1;
//     } else {
//         Serial.println("invalid request");
//         client.stop();
//         return;
//     }

//     // Set GPIO2 according to the request
//     digitalWrite(2, val);

//     client.flush();

//     // Prepare the response
//     String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
//     s += (val)?"high":"low";
//     s += "</html>\n";

//     // Send the response to the client
//     client.print(s);
//     delay(1);
//     Serial.println("Client disonnected");

//     // The client will actually be disconnected
//     // when the function returns and 'client' object is detroyed
// }