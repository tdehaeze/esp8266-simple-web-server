#ifndef PAGE_INFOMATION_H_INCLUDED
#define PAGE_INFOMATION_H_INCLUDED

#include <Arduino.h> // For Serial
#include <accesspoint.h>
#include <WString.h>

const char PAGE_Information[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="stylesheet" href="style.css" type="text/css" />
<script src="microajax.js"></script>
<a href="/"  class="btn btn-s"><</a>&nbsp;&nbsp;<strong>Network Information</strong>
<hr>
<table border="0"  cellspacing="0" cellpadding="3" style="width:310px" >
    <tr><td align="right">SSID :</td><td><span id="x_ssid"></span></td></tr>
    <tr><td align="right">IP :</td><td><span id="x_ip"></span></td></tr>
    <tr><td align="right">Netmask :</td><td><span id="x_netmask"></span></td></tr>
    <tr><td align="right">Gateway :</td><td><span id="x_gateway"></span></td></tr>
    <tr><td align="right">Mac :</td><td><span id="x_mac"></span></td></tr>

    <tr><td colspan="2" align="center"><a href="javascript:GetState()" class="btn btn-m btn-blue">Refresh</a></td></tr>
</table>
<script>

function GetState() {
    setValues("/admin/infovalues");
}

window.onload = function () {
    load("style.css","css", function() {
        load("microajax.js","js", function() {
            GetState();
        });
    });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
)=====" ;


String GetMacAddress(void)
{
    uint8_t mac[6];
    char macStr[18] = {0};
    WiFi.macAddress(mac);
    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0],  mac[1], mac[2], mac[3], mac[4], mac[5]);
    return  String(macStr);
}

// FILL WITH INFOMATION
// TODO
void send_information_values_html(void)
{
    String values = "";
    values += "x_ssid|" + WiFi.SSID() + "|div\n";
    // values += "x_ip|" +       WiFi.localIP()[0] +     "." + WiFi.localIP()[1] +     "." + WiFi.localIP()[2] +     "." + WiFi.localIP()[3] +     "|div\n";
    // values += "x_gateway|" +  WiFi.gatewayIP()[0] +   "." + WiFi.gatewayIP()[1] +   "." + WiFi.gatewayIP()[2] +   "." + WiFi.gatewayIP()[3] +   "|div\n";
    // values += "x_netmask|" +  WiFi.subnetMask()[0] +  "." + WiFi.subnetMask()[1] +  "." + WiFi.subnetMask()[2] +  "." + WiFi.subnetMask()[3] +  "|div\n";
    // values += "x_mac|" + GetMacAddress() +  "|div\n";

    server.send(200, "text/plain", values);
    Serial.println(__FUNCTION__);
}

#endif /* PAGE_INFOMATION_H_INCLUDED */
