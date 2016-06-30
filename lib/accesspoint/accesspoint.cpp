#include "accesspoint.h"

void init_accesspoint(void)
{
    WiFi.mode(WIFI_STA);
    WiFi.softAP(SSID);

    Serial.printf("AP IP address: %s", WiFi.softAPIP().toString().c_str());

    // Admin page
    server.on("/", [](){
        Serial.println("admin.html");
        server.send(200, "text/html", PAGE_AdminMainPage);  // const char top of page
    });

    server.on("/favicon.ico", [](){
        Serial.println("favicon.ico");
        server.send (200, "text/html", "");
    });

    // Network config
    server.on("/config.html", send_network_configuration_html);

    // Info Page
    server.on("/info.html", [](){
        Serial.println("info.html");
        server.send(200, "text/html", PAGE_Information);
    });

    server.on("/general.html", send_general_html );

    server.on("/style.css", [](){
        Serial.println("style.css");
        server.send(200, "text/plain", PAGE_Style_css);
    });

    server.on("/microajax.js", [](){
        Serial.println("microajax.js");
        server.send(200, "text/plain", PAGE_microajax_js);
    });

    server.on("/admin/values", send_network_configuration_values_html);
    server.on("/admin/connectionstate", send_connection_state_values_html);
    server.on("/admin/infovalues", send_information_values_html);
    server.on("/admin/devicename", send_devicename_value_html);

    server.onNotFound([](){
        Serial.println("Page Not Found");
        server.send(400, "text/html", "Page not Found");
    });

    server.begin();
    Serial.println( "HTTP server started");
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
//     server.send(200, "text/html", createForm());
// }

// static void onNotFound(void)
// {
//     Serial.println("NOT FOUND");
//     server.send(404, "text/html"); // TODO => Should change to a 301 code and redirect
// }

// static void handlePost(void)
// {
//     Serial.println("POST");

//     String ssid_selected = WiFi.SSID(server.argName(0).toInt());
//     String password_selected = server.arg(1);

//     // int n = server.args();
//     // Serial.println(n);
//     // for (int i = 0; i < n; ++i) {
//     // }

//     Serial.printf("ssid: %s \npassword: %s\n", ssid_selected.c_str(), password_selected.c_str());

//     // Should try to connect to the access point.
//     int success = connect_to_AP(ssid_selected.c_str(), password_selected.c_str());

//     // If it's working
//     if (success) {
//         server.send(200, "text/html", "<h1>La configuration s'est correctement effectuee.</h1>");
//     } else {
//         server.send(200, "text/html", "<h1>Erreur. Veuillez <a href='/'>essayer a nouveau</a>.</h1>");
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

//     server.on("/", HTTP_GET, handleRoot);
//     server.on("/", HTTP_POST, handlePost);
//     server.onNotFound(onNotFound);

//     server.begin();

//     Serial.println("HTTP server started");

//     while(true)
//     {
//         server.handleClient();
//     }
// }
