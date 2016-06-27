#include "wifi.h"

// WiFi parameters
const char* ssid = "Rtone Cisco";
const char* password = "0478477078rto";

void init_wifi(void)
{
    // Connect to WiFi
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");

    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.print(".");
        delay(5000);
        // ESP.restart();
    }

    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());


}

void init_server(void)
{
    WiFiServer server(80);

    // Start the server
    server.begin();
    Serial.println("Server started");
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