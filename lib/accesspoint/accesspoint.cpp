#include "accesspoint.h"

/* Set these to your desired credentials. */
const char* ssid = "ESP8266";
// const char* password = "12345";


/***
 * Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
static void handleRoot(void)
{
    server.send(200, "text/html", "<h1>You are connected</h1>");
}

void init_accesspoint(void)
{
    ESP8266WebServer server(80);

    delay(1000);
    Serial.print("Configuring access point...");

    /* You can remove the password parameter if you want the AP to be open. */
    // WiFi.softAP(ssid, password);
    WiFi.softAP(ssid);

    IPAddress myIP = WiFi.softAPIP();

    Serial.print("AP IP address: ");
    Serial.println(myIP);

    server.on("/", handleRoot);

    server.begin();

    Serial.println("HTTP server started");

    while(true)
    {
        server.handleClient();
    }
}
