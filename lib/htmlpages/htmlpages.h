#ifndef HTMLPAGES_H_INCLUDED
#define HTMLPAGES_H_INCLUDED

const char PAGE_AdminMainPage[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1"/>
<strong>Administration</strong>
<hr>
<a href="general.html" style="width:250px" class="btn btn-m btn-blue">General Configuration</a><br>
<a href="config.html" style="width:250px" class="btn btn-m btn-blue">Network Configuration</a><br>
<a href="info.html" style="width:250px" class="btn btn-m btn-blue">Network Information</a><br>

<script>
window.onload = function () {
    load("style.css","css", function() {
        load("microajax.js","js", function() {
            // Do something after load...
        });
    });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
)=====";

const char PAGE_AdminGeneralSettings[] PROGMEM =  R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn-s"><</a>&nbsp;&nbsp;<strong>General Settings</strong>
<hr>
<form action="" method="post">
    <table border="0"  cellspacing="0" cellpadding="3" >
    <tr>
        <td align="right">Name of Device</td>
        <td><input type="text" id="devicename" name="devicename" value=""></td>
    </tr>
    <tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn-m btn-blue" value="Save"></td></tr>
    </table>
</form>
<script>window.onload = function() {
    load("style.css","css", function() {
        load("microajax.js","js", function() {
            setValues("/admin/generalvalues");
        });
    });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
)=====";

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

const char PAGE_NetworkConfiguration[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1"/>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
<a href="/" class="btn btn-s"><</a>&nbsp;&nbsp;<strong>Network Configuration</strong>
<hr>
Connect to Router with these settings:<br>
<form action="" method="get">
    <table border="0"  cellspacing="0" cellpadding="3" style="width:310px" >
        <tr><td align="right">SSID:</td><td><input type="text" id="ssid" name="ssid" value=""></td></tr>
        <tr><td align="right">Password:</td><td><input type="text" id="password" name="password" value=""></td></tr>
        <tr><td align="right">DHCP:</td><td><input type="checkbox" id="dhcp" name="dhcp"></td></tr>
        <tr><td align="right">IP:</td><td><input type="text" id="ip_0" name="ip_0" size="3">.<input type="text" id="ip_1" name="ip_1" size="3">.<input type="text" id="ip_2" name="ip_2" size="3">.<input type="text" id="ip_3" name="ip_3" value="" size="3"></td></tr>
        <tr><td align="right">Netmask:</td><td><input type="text" id="nm_0" name="nm_0" size="3">.<input type="text" id="nm_1" name="nm_1" size="3">.<input type="text" id="nm_2" name="nm_2" size="3">.<input type="text" id="nm_3" name="nm_3" size="3"></td></tr>
        <tr><td align="right">Gateway:</td><td><input type="text" id="gw_0" name="gw_0" size="3">.<input type="text" id="gw_1" name="gw_1" size="3">.<input type="text" id="gw_2" name="gw_2" size="3">.<input type="text" id="gw_3" name="gw_3" size="3"></td></tr>
        <tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn-m btn-blue" value="Save"></td></tr>
    </table>
</form>
<hr>
<strong>Connection State:</strong><div id="connectionstate">N/A</div>
<hr>
<strong>Networks:</strong><br>
<table border="0"  cellspacing="3" style="width:310px" >
    <tr><td><div id="networks">Scanning...</div></td></tr>
    <tr><td align="center"><a href="javascript:GetState()" style="width:150px" class="btn btn-m btn-blue">Refresh</a></td></tr>
</table>

<script>
function GetState() {
    setValues("/admin/connectionstate");
}
function selssid(value) {
    document.getElementById("ssid").value = value;
}
window.onload = function() {
    load("style.css","css", function() {
        load("microajax.js","js", function() {
            setValues("/admin/values");
            setTimeout(GetState,3000);
        });
    });
}

function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}

</script>
)=====";

const char PAGE_WaitAndReload[] PROGMEM = R"=====(
<meta http-equiv="refresh" content="5; URL=config.html">
Please Wait....Configuring and Restarting.
)=====";

const char PAGE_Root[] PROGMEM = R"=====(
<!doctype html>
<meta name="viewport" content="width=device-width, initial-scale=1" />
<script src="microajax.js"></script>
<html>
    <head>
        <title></title>
        <meta charset="utf-8" />
    </head>
    <body>
        <link rel="stylesheet" href="style.css" type="text/css" />
        It work's!
    </body>
</html>
)=====";

const char PAGE_microajax_js[] PROGMEM = R"=====(
function microAjax(B,A){this.bindFunction=function(E,D){return function(){return E.apply(D,[D])}};this.stateChange=function(D){if(this.request.readyState==4){this.callbackFunction(this.request.responseText)}};this.getRequest=function(){if(window.ActiveXObject){return new ActiveXObject("Microsoft.XMLHTTP")}else{if(window.XMLHttpRequest){return new XMLHttpRequest()}}return false};this.postBody=(arguments[2]||"");this.callbackFunction=A;this.url=B;this.request=this.getRequest();if(this.request){var C=this.request;C.onreadystatechange=this.bindFunction(this.stateChange,this);if(this.postBody!==""){C.open("POST",B,true);C.setRequestHeader("X-Requested-With","XMLHttpRequest");C.setRequestHeader("Content-type","application/x-www-form-urlencoded");C.setRequestHeader("Connection","close")}else{C.open("GET",B,true)}C.send(this.postBody)}};

function setValues(url) {
    microAjax(url, function(res) {
        res.split(String.fromCharCode(10)).forEach(function(entry) {
        fields = entry.split("|");
        if(fields[2] == "input") {
                document.getElementById(fields[0]).value = fields[1];
        } else if(fields[2] == "div") {
                document.getElementById(fields[0]).innerHTML  = fields[1];
        } else if(fields[2] == "chk") {
                document.getElementById(fields[0]).checked  = fields[1];
        }
      });
    });
}
)=====";

const char PAGE_Style_css[] PROGMEM = R"=====(
body {
    color: #000000;
    font-family: avenir, helvetica, arial, sans-serif;
    letter-spacing: 0.15em;
}
hr {
    background-color: #eee;
    border: 0 none;
    color: #eee;
    height: 1px;
}
.btn {
    border-radius: 0.3em;
    border-style: solid;
    border-width: 1px;
    color: #111;
    display: inline-block;
    font-family: avenir, helvetica, arial, sans-serif;
    letter-spacing: 0.15em;
    margin-bottom: 0.5em;
    padding: 1em 0.75em;
    text-decoration: none;
    text-transform: uppercase;
    -webkit-transition: color 0.4s, background-color 0.4s, border 0.4s;
    transition: color 0.4s, background-color 0.4s, border 0.4s;
}
.btn:hover, .btn:focus {
    color: #7FDBFF;
    border: 1px solid #7FDBFF;
    -webkit-transition: background-color 0.3s, color 0.3s, border 0.3s;
    transition: background-color 0.3s, color 0.3s, border 0.3s;
}
.btn:active {
    color: #0074D9;
    border: 1px solid #0074D9;
    -webkit-transition: background-color 0.3s, color 0.3s, border 0.3s;
    transition: background-color 0.3s, color 0.3s, border 0.3s;
}
.btn-s {
    font-size: 12px;
}
.btn-m {
    font-size: 14px;
}
.btn-l {
    font-size: 20px;
    border-radius: 0.25em !important;
}
.btn-blue {
    color: #fff;
    background-color: #0074D9;
}
.btn-blue:active {
    border-color: #001F3F;
}
)=====";

#endif /* HTMLPAGES_H_INCLUDED */
