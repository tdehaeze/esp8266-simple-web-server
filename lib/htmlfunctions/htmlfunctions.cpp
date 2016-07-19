#include <htmlfunctions.h>

#include <Arduino.h>
#include <WString.h>
#include <confignetwork.h>
#include <accesspoint.h>
#include <helpers.h>
#include <htmlpages.h>
#include <ota.h>
#include <wifi.h>
#include <FS.h>

// Get the nac address of the esp8266
String getMacAddress(void)
{
    uint8_t mac[6];
    char macStr[18] = {0};
    WiFi.macAddress(mac);
    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0],  mac[1], mac[2], mac[3], mac[4], mac[5]);
    return  String(macStr);
}

// Get the device name : "ESP8266_" + first 6 digits of the max address
String getDeviceName(void)
{
    return "ESP8266_" + getMacAddress().substring(0, 2) + getMacAddress().substring(3, 5) + getMacAddress().substring(6, 8);
}

// From WiFi.status() return the state of the Wifi connection
String getConnectionState(void)
{
    String state = "";

    if (WiFi.status() == 0) state += "Idle";
    else if (WiFi.status() == 1) state += "No ssid available";
    else if (WiFi.status() == 2) state += "Scan completed";
    else if (WiFi.status() == 3) state += "Connected on " + getWifiSsid();
    else if (WiFi.status() == 4) state += "Connected failed";
    else if (WiFi.status() == 5) state += "Connection lost";
    else if (WiFi.status() == 6) state += "Disconnected";
    else state += "N/A";

    return state;
}

// ==================================
// =========== /get/image ===========
// ==================================
void urlGetImage(void)
{
    // if (!SPIFFS.begin())
    // {
    //     Serial.println("SPIFFS failed to mount !\r\n");
    // }
    // else
    // {
    //     File f = SPIFFS.open("/image_100.png", "r");

    //     if (!f)
    //     {
    //         Serial.println("Can't open SPIFFS file !\r\n");
    //     }
    //     else
    //     {
    //         char buf[1024];
    //         int siz = f.size();
    //         while(siz > 0) {
    //             size_t len = std::min((int)(sizeof(buf) - 1), siz);
    //             f.read((uint8_t *)buf, len);
    //             buf[len] = 0;
    //             siz -= sizeof(buf) - 1;
    //             server_esp.sendContent_P(buf);
    //         }
    //         f.close();
    //         server_esp.send(200, "image/png", "");
    //     }
    // }

    Serial.println("urlGetImage");
    char testing[1024];
    memset(testing, 'a', 1024);
    for(int i=0; i<4*1024; i++){
        server_esp.sendContent_P(testing);
    }
    server_esp.send(200, "text/plain", "");

    // int idx = 0;
    // int time = getTimer();
    // while(idx < 1024*8)
    // {
    //     send(mysock, testing, 1024, 0);

    //     while(socket_sent==0)
    //     {
    //         m2m_wifi_handle_events(NULL);
    //         nm_bsp_sleep(2);
    //     }
    //     idx++;
    // }
}

// ==================================
// ===== /post/connection/form ======
// ==================================
void urlPostConnectionForm(void)
{
    if (server_esp.args() > 0 ) {
        String ssid = "";
        String password = "";
        for ( uint8_t i = 0; i < server_esp.args(); i++ ) {
            if (server_esp.argName(i) == "ssid") ssid = urlDecode(server_esp.arg(i));
            else if (server_esp.argName(i) == "password") password = urlDecode(server_esp.arg(i));
        }
        if (ssid != "") {
            config_server.ssid = ssid;
            config_server.password = password;
            connectToWifi();
            if (getWifiStatus()) {
                writeConfig();
            }
        }
    }
    server_esp.send(200, "text/plain", "");
    Serial.println(__FUNCTION__);
}


// Used to send the device name (general.html)
// ==================================
// ======== /get/devicename =========
// ==================================
void urlGetDeviceName(void)
{
    String values = "";
    values += "devicename|";
    values += getDeviceName();
    values += "|input\n";

    server_esp.send(200, "text/plain", values);
    Serial.println(__FUNCTION__);
}

// Send information about the connected AP (use in the info.html page)
// If not connected => send "not connected"
// ==================================
// ====== /get/connection/info ======
// ==================================
void urlGetConnectionInfo(void)
{
    String values = "";

    if (WiFi.isConnected()) {
        values += "x_ssid|" + WiFi.SSID() + "|div\n";
        values += "x_ip|" +       String(WiFi.localIP()[0]) +     "." + String(WiFi.localIP()[1]) +     "." + String(WiFi.localIP()[2]) +     "." + String(WiFi.localIP()[3]) +     "|div\n";
        values += "x_gateway|" +  String(WiFi.gatewayIP()[0]) +   "." + String(WiFi.gatewayIP()[1]) +   "." + String(WiFi.gatewayIP()[2]) +   "." + String(WiFi.gatewayIP()[3]) +   "|div\n";
        values += "x_netmask|" +  String(WiFi.subnetMask()[0]) +  "." + String(WiFi.subnetMask()[1]) +  "." + String(WiFi.subnetMask()[2]) +  "." + String(WiFi.subnetMask()[3]) +  "|div\n";
        values += "x_mac|" + getMacAddress() +  "|div\n";
    } else {
        values += "x_ssid|not connected|div\n";
    }

    server_esp.send(200, "text/plain", values);
    Serial.println(__FUNCTION__);
}

// Used to fill out the form on the config.html page
// ==================================
// ====== /get/connection/form ======
// ==================================
void urlGetConnectionForm(void)
{
    String values = "";

    values += "ssid|" + config_server.ssid + "|input\n";
    values += "password|" + config_server.password + "|input\n";

    server_esp.send(200, "text/plain", values);
    Serial.println(__FUNCTION__);
}


// ==================================
// ====== /get/connection/state ======
// ==================================
void urlGetConnectionState(void)
{
    String state = "";

    state += "connectionstate|";
    state += getConnectionState();
    state += "|div\n";

    server_esp.send(200, "text/plain", state);
    Serial.println(__FUNCTION__);
}

// ==================================
// ========= /get/networks ==========
// ==================================
void urlGetNetworks(void)
{
    String networks = "";

    networks += "networks|";

    int n = WiFi.scanNetworks();

    if (n == 0) {
        networks += "<font color='#FF0000'>No networks found!</font>";
    } else {
        networks += "Found " + String(n) + " Networks<br>";
        networks += "<table border='0' cellspacing='0' cellpadding='3'>";
        networks += "<tr bgcolor='#DDDDDD'><td><strong>Name</strong></td><td><strong>Quality</strong></td><td><strong>Enc</strong></td><tr>";
        for (int i = 0; i < n; ++i) {
            int quality = 0;
            if (WiFi.RSSI(i) <= -100) {
                quality = 0;
            } else if (WiFi.RSSI(i) >= -50) {
                quality = 100;
            } else {
                quality = 2 * (WiFi.RSSI(i) + 100);
            }

            networks += "<tr><td><a href='javascript:setssid(\""  +  String(WiFi.SSID(i))  + "\")'>"  +  String(WiFi.SSID(i))  + "</a></td><td>" +  String(quality) + "%</td><td>" +  String((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*")  + "</td></tr>";
        }
        networks += "</table>";
    }

    networks += "|div\n";

    server_esp.send(200, "text/plain", networks);
    Serial.println(__FUNCTION__);
}


void urlGetPinValue(void)
{
    String value = "";

    value += "value|";
    value += 3.3*analogRead(A0)/1000;
    value += "|div\n";

    server_esp.send(200, "text/plain", value);
    Serial.println(__FUNCTION__);
}
