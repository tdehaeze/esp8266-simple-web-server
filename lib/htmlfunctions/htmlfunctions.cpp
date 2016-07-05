#include <htmlfunctions.h>

#include <Arduino.h>
#include <confignetwork.h>
#include <accesspoint.h>
#include <helpers.h>
#include <htmlpages.h>
#include <ota.h>

// Functions for this Page
void send_devicename_value_html(void)
{
    String values = "";
    values += "devicename|";
    values += config_server.DeviceName;
    values += "|div\n";
    server_esp.send(200, "text/plain", values);
    Serial.println(__FUNCTION__);
}

void send_general_html(void)
{
    if (server_esp.args() > 0)  // Save Settings
    {
        String temp = "";
        for (uint8_t i = 0; i < server_esp.args(); i++) {
            if (server_esp.argName(i) == "devicename") config_server.DeviceName = urlDecode(server_esp.arg(i));
        }
        // writeConfig();
    }
    server_esp.send(200, "text/html", PAGE_GENERAL);
    Serial.println(__FUNCTION__);
}

void send_general_configuration_values_html(void)
{
    String values ="";
    values += "devicename|";
    values += config_server.DeviceName;
    values += "|input\n";

    server_esp.send(200, "text/plain", values);
    Serial.println(__FUNCTION__);
}

String GetMacAddress(void)
{
    uint8_t mac[6];
    char macStr[18] = {0};
    WiFi.macAddress(mac);
    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0],  mac[1], mac[2], mac[3], mac[4], mac[5]);
    return  String(macStr);
}

String GetFirstMacAddress(void)
{
    return GetMacAddress().substring(0, 2) + GetMacAddress().substring(3, 5) + GetMacAddress().substring(6, 8);
}

// FILL WITH INFOMATION
void send_information_values_html(void)
{
    String values = "";
    values += "x_ssid|" + WiFi.SSID() + "|div\n";
    values += "x_ip|" +       String(WiFi.localIP()[0]) +     "." + String(WiFi.localIP()[1]) +     "." + String(WiFi.localIP()[2]) +     "." + String(WiFi.localIP()[3]) +     "|div\n";
    values += "x_gateway|" +  String(WiFi.gatewayIP()[0]) +   "." + String(WiFi.gatewayIP()[1]) +   "." + String(WiFi.gatewayIP()[2]) +   "." + String(WiFi.gatewayIP()[3]) +   "|div\n";
    values += "x_netmask|" +  String(WiFi.subnetMask()[0]) +  "." + String(WiFi.subnetMask()[1]) +  "." + String(WiFi.subnetMask()[2]) +  "." + String(WiFi.subnetMask()[3]) +  "|div\n";
    values += "x_mac|" + GetMacAddress() +  "|div\n";

    server_esp.send(200, "text/plain", values);
    Serial.println(__FUNCTION__);
}

// Check the Values is between 0-255
bool checkRange(String Value)
{
    if (Value.toInt() < 0 || Value.toInt() > 255) {
        return false;
    } else {
        return true;
    }
}

//  SEND HTML PAGE OR IF A FORM SUMBITTED VALUES, PROCESS THESE VALUES
void send_network_configuration_html(void)
{
    // // Save Settings
    if (server_esp.args() > 0 ) { // if submit form
        String temp = "";
        config_server.dhcp = false;
        for ( uint8_t i = 0; i < server_esp.args(); i++ ) {
            if (server_esp.argName(i) == "ssid") config_server.ssid = urlDecode(server_esp.arg(i));
            if (server_esp.argName(i) == "password") config_server.password = urlDecode(server_esp.arg(i));
            if (checkRange(server_esp.arg(i))) {
                if (server_esp.argName(i) == "ip_0") config_server.IP[0] = server_esp.arg(i).toInt();
                if (server_esp.argName(i) == "ip_1") config_server.IP[1] = server_esp.arg(i).toInt();
                if (server_esp.argName(i) == "ip_2") config_server.IP[2] = server_esp.arg(i).toInt();
                if (server_esp.argName(i) == "ip_3") config_server.IP[3] = server_esp.arg(i).toInt();
                if (server_esp.argName(i) == "nm_0") config_server.Netmask[0] = server_esp.arg(i).toInt();
                if (server_esp.argName(i) == "nm_1") config_server.Netmask[1] = server_esp.arg(i).toInt();
                if (server_esp.argName(i) == "nm_2") config_server.Netmask[2] = server_esp.arg(i).toInt();
                if (server_esp.argName(i) == "nm_3") config_server.Netmask[3] = server_esp.arg(i).toInt();
                if (server_esp.argName(i) == "gw_0") config_server.Gateway[0] = server_esp.arg(i).toInt();
                if (server_esp.argName(i) == "gw_1") config_server.Gateway[1] = server_esp.arg(i).toInt();
                if (server_esp.argName(i) == "gw_2") config_server.Gateway[2] = server_esp.arg(i).toInt();
                if (server_esp.argName(i) == "gw_3") config_server.Gateway[3] = server_esp.arg(i).toInt();
            }
            if (server_esp.argName(i) == "dhcp") config_server.dhcp = true;
        }
        // writeReceivedConfig();
        server_esp.send (200, "text/html", PAGE_RELOAD);
        // writeConfig();
        // ConfigureWifi();
    } else {
        server_esp.send (200, "text/html", PAGE_CONFIG);
    }
    Serial.println(__FUNCTION__);
}

// FILL THE PAGE WITH VALUES
void send_network_configuration_values_html(void)
{
    String values = "";

    values += "ssid|" + config_server.ssid + "|input\n";
    values += "password|" + config_server.password + "|input\n";

    values += "ip_0|" + String(config_server.IP[0]) + "|input\n";
    values += "ip_1|" + String(config_server.IP[1]) + "|input\n";
    values += "ip_2|" + String(config_server.IP[2]) + "|input\n";
    values += "ip_3|" + String(config_server.IP[3]) + "|input\n";

    values += "nm_0|" + String(config_server.Netmask[0]) + "|input\n";
    values += "nm_1|" + String(config_server.Netmask[1]) + "|input\n";
    values += "nm_2|" + String(config_server.Netmask[2]) + "|input\n";
    values += "nm_3|" + String(config_server.Netmask[3]) + "|input\n";

    values += "gw_0|" + String(config_server.Gateway[0]) + "|input\n";
    values += "gw_1|" + String(config_server.Gateway[1]) + "|input\n";
    values += "gw_2|" + String(config_server.Gateway[2]) + "|input\n";
    values += "gw_3|" + String(config_server.Gateway[3]) + "|input\n";

    values += "dhcp|" + String(config_server.dhcp ? "checked" : "") + "|chk\n";

    server_esp.send(200, "text/plain", values);
    Serial.println(__FUNCTION__);
}

// FILL THE PAGE WITH NETWORKSTATE & NETWORKS
void send_connection_state_values_html(void)
{
    String state = "N/A";
    String Networks = "";

    if (WiFi.status() == 0) state = "Idle";
    else if (WiFi.status() == 1) state = "NO SSID AVAILBLE";
    else if (WiFi.status() == 2) state = "SCAN COMPLETED";
    else if (WiFi.status() == 3) state = "CONNECTED";
    else if (WiFi.status() == 4) state = "CONNECT FAILED";
    else if (WiFi.status() == 5) state = "CONNECTION LOST";
    else if (WiFi.status() == 6) state = "DISCONNECTED";

    int n = WiFi.scanNetworks();

    if (n == 0) {
        Networks = "<font color='#FF0000'>No networks found!</font>";
    } else {
        Networks = "Found " + String(n) + " Networks<br>";
        Networks += "<table border='0' cellspacing='0' cellpadding='3'>";
        Networks += "<tr bgcolor='#DDDDDD'><td><strong>Name</strong></td><td><strong>Quality</strong></td><td><strong>Enc</strong></td><tr>";
        for (int i = 0; i < n; ++i) {
            int quality = 0;
            if (WiFi.RSSI(i) <= -100) {
                quality = 0;
            } else if (WiFi.RSSI(i) >= -50) {
                quality = 100;
            } else {
                quality = 2 * (WiFi.RSSI(i) + 100);
            }

            Networks += "<tr><td><a href='javascript:setssid(\""  +  String(WiFi.SSID(i))  + "\")'>"  +  String(WiFi.SSID(i))  + "</a></td><td>" +  String(quality) + "%</td><td>" +  String((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*")  + "</td></tr>";
        }
        Networks += "</table>";
    }

    String values ="";
    values += "connectionstate|" + state + "|div\n";
    values += "networks|" + Networks + "|div\n";

    server_esp.send (200, "text/plain", values);
    Serial.println(__FUNCTION__);
}
