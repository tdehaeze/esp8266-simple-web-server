#include "accesspoint.h"

using namespace std;

/* Set these to your desired credentials. */
const char* ssid = "ESP8266";
// const char* password = "12345";

ESP8266WebServer server(80);

static char * createForm(void)
{
    char buffer[1000] = "";
    char *cur = buffer, * const end = buffer + sizeof buffer;

    int n = scan_network();

    if (n == 0) {
        cur += snprintf(cur, end-cur, "%s", "No networks found");
        Serial.println("No networks found");
    } else {
        Serial.printf("%i networks found", n);
        Serial.println("");
        cur += snprintf(cur, end-cur, "%s", "<h1>Selectionnez le wifi sur lequel se connecter</h1><form action='/' method='post'><select name='ssid_id'>");

        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.printf("%i: %s (%d) %s\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i), (WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
            if (cur < end) {
                cur += snprintf(cur, end-cur, "<option value='%i'>%s (%d)</option>", i, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
            } else {
                Serial.println("To many characters");
            }
            // snprintf(buffer, 500, "<option value='%i'>%s (%d)</option>", i, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
        }

        if (cur < end) {
            cur += snprintf(cur, end-cur, "</select><br/><input type='password' name='password'/><br/><input type='submit' value='Enregistrer'/></form>");
        } else {
            Serial.println("To many characters");
        }
    }

    // Serial.println(buffer);

    return &buffer[0];
}

static void handleRoot(void)
{
    Serial.println("GET");
    server.send(200, "text/html", createForm());
}

static void onNotFound(void)
{
    Serial.println("NOT FOUND");
    server.send(404, "text/html"); // TODO => Should change to a 301 code and redirect
}

static void handlePost(void)
{
    Serial.println("POST");

    String ssid_selected = WiFi.SSID(server.argName(0).toInt());
    String password_selected = server.arg(1);

    // int n = server.args();
    // Serial.println(n);
    // for (int i = 0; i < n; ++i) {
    // }

    Serial.printf("ssid: %s \npassword: %s\n", ssid_selected.c_str(), password_selected.c_str());

    // Should try to connect to the access point.
    int success = connect_to_AP(ssid_selected.c_str(), password_selected.c_str());

    // If it's working
    if (success) {
        server.send(200, "text/html", "<h1>La configuration s'est correctement effectuee.</h1>");
    } else {
        server.send(200, "text/html", "<h1>Erreur. Veuillez <a href='/'>essayer a nouveau</a>.</h1>");
    }
}

void init_accesspoint(void)
{
    delay(1000);
    Serial.print("Configuring access point...");

    /* You can remove the password parameter if you want the AP to be open. */
    // WiFi.softAP(ssid, password);
    WiFi.softAP(ssid);

    IPAddress myIP = WiFi.softAPIP();

    Serial.printf("AP IP address: %s", myIP.toString().c_str());

    server.on("/", HTTP_GET, handleRoot);
    server.on("/", HTTP_POST, handlePost);
    server.onNotFound(onNotFound);

    server.begin();

    Serial.println("HTTP server started");

    while(true)
    {
        server.handleClient();
    }
}
