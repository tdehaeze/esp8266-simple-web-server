#include <accesspoint.h>

#include <Arduino.h> // For Serial
// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>
// #include <stdio.h>
// #include <wifi.h>
// #include <WString.h>

#include <htmlfunctions.h>
#include <htmlpages.h>

// #include "/lib/htmlpages/htmlpages.h"

// #include <ESP8266Webserver.h>
// ESP8266WebServer server_esp(80);

ESP8266WebServer server_esp(80);

void init_accesspoint(void)
{
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("ESP8266_test");

    Serial.printf("AP IP address: %s", WiFi.softAPIP().toString().c_str());

    server_esp.on("/", [](){
        Serial.println("admin.html");
        server_esp.send(200, "text/html", PAGE_AdminMainPage);
    });

    server_esp.on("/favicon.ico", [](){
        Serial.println("favicon.ico");
        server_esp.send (200, "text/html", "");
    });

    server_esp.on("/config.html", send_network_configuration_html);

    server_esp.on("/info.html", [](){
        Serial.println("info.html");
        server_esp.send(200, "text/html", PAGE_Information);
    });

    server_esp.on("/general.html", send_general_html);

    server_esp.on("/style.css", [](){
        Serial.println("style.css");
        server_esp.send(200, "text/plain", PAGE_Style_css);
    });

    server_esp.on("/microajax.js", [](){
        Serial.println("microajax.js");
        server_esp.send(200, "text/plain", PAGE_microajax_js);
    });

    server_esp.on("/admin/values", send_network_configuration_values_html);
    server_esp.on("/admin/connectionstate", send_connection_state_values_html);
    server_esp.on("/admin/infovalues", send_information_values_html);
    server_esp.on("/admin/devicename", send_devicename_value_html);

    server_esp.onNotFound([](){
        Serial.println("Page Not Found");
        server_esp.send(400, "text/html", "Page not Found");
    });

    server_esp.begin();
    Serial.println("HTTP server started");
}

// static char * createForm(void)
// {
//     char buffer[1000] = "";
//     char *cur = buffer, * const end = buffer + sizeof buffer;

//     int n = scan_network();

//     if (n == 0) {
//         cur += snprintf(cur, end-cur, "%s", "No networks found");
//         Serial.println("No networks found");
//     } else {
//         Serial.printf("%i networks found", n);
//         Serial.println("");
//         cur += snprintf(cur, end-cur, "%s", "<h1>Selectionnez le wifi sur lequel se connecter</h1><form action='/' method='post'><select name='ssid_id'>");

//         for (int i = 0; i < n; ++i) {
//             // Print SSID and RSSI for each network found
//             Serial.printf("%i: %s (%d) %s\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i), (WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
//             if (cur < end) {
//                 cur += snprintf(cur, end-cur, "<option value='%i'>%s (%d)</option>", i, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
//             } else {
//                 Serial.println("To many characters");
//             }
//             // snprintf(buffer, 500, "<option value='%i'>%s (%d)</option>", i, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
//         }

//         if (cur < end) {
//             cur += snprintf(cur, end-cur, "</select><br/><input type='password' name='password'/><br/><input type='submit' value='Enregistrer'/></form>");
//         } else {
//             Serial.println("To many characters");
//         }
//     }

//     // Serial.println(buffer);

//     return &buffer[0];
// }

// static void handleRoot(void)
// {
//     Serial.println("GET");
//     server_esp.send(200, "text/html", createForm());
// }

// static void onNotFound(void)
// {
//     Serial.println("NOT FOUND");
//     server_esp.send(404, "text/html"); // TODO => Should change to a 301 code and redirect
// }

// static void handlePost(void)
// {
//     Serial.println("POST");

//     String ssid_selected = WiFi.SSID(server_esp.argName(0).toInt());
//     String password_selected = server_esp.arg(1);

//     // int n = server_esp.args();
//     // Serial.println(n);
//     // for (int i = 0; i < n; ++i) {
//     // }

//     Serial.printf("ssid: %s \npassword: %s\n", ssid_selected.c_str(), password_selected.c_str());

//     // Should try to connect to the access point.
//     int success = connect_to_AP(ssid_selected.c_str(), password_selected.c_str());

//     // If it's working
//     if (success) {
//         server_esp.send(200, "text/html", "<h1>La configuration s'est correctement effectuee.</h1>");
//     } else {
//         server_esp.send(200, "text/html", "<h1>Erreur. Veuillez <a href='/'>essayer a nouveau</a>.</h1>");
//     }
// }

// void init_accesspoint(void)
// {
//     delay(1000);
//     Serial.print("Configuring access point...");

//     /* You can remove the password parameter if you want the AP to be open. */
//     // WiFi.softAP(ssid, password);
//     WiFi.softAP(ssid);

//     IPAddress myIP = WiFi.softAPIP();

//     Serial.printf("AP IP address: %s", myIP.toString().c_str());

//     server_esp.on("/", HTTP_GET, handleRoot);
//     server_esp.on("/", HTTP_POST, handlePost);
//     server_esp.onNotFound(onNotFound);

//     server_esp.begin();

//     Serial.println("HTTP server started");

//     while(true)
//     {
//         server_esp.handleClient();
//     }
// }
