# Simple web server on the ESP8266 NodeMCU v2 using Arduino core

## Installation process

First clone this git repository :


	git clone git@github.com:tdehaeze/esp8266-simple-web-server.git

You need to install [PlatformIO CLI](http://docs.platformio.org/en/latest/installation.html) or the full [PlatformIO IDE](http://platformio.org/).

Then, you have to set the correct serial port on `platformio.ini` file :


	platform = espressif
	framework = arduino
	board = nodemcuv2
	upload_port = /dev/tty.SLAB_USBtoUART


On mac, to see all available serial ports, you can use : `ls /dev/tty.*`.

Then on the project directory, to compile and upload the project, just type :


    platformio run

To open a serial communication, you can type :

    platformio serialports monitor --port /dev/tty.SLAB_USBtoUART --baud 115200 --eol CR --raw


## Documentation

Pin map : [link](https://github.com/nodemcu/nodemcu-devkit-v1.0)

### Other firmware for the esp8266
 - Cloud solution : http://nodemcu-build.com/
 - Using Docker : https://hub.docker.com/r/marcelstoer/nodemcu-build/
 - Official firmware : https://github.com/espressif/ESP8266_AT/tree/master/bin
 - Lua-NodeMCU firmware : https://github.com/nodemcu/nodemcu-firmware

### How to flash a firmware

 - **Command line** (*Windows/Linux/OSX*) : [esptool](https://github.com/themadinventor/esptool)


	git clone https://github.com/themadinventor/esptool
	cd esptool
	./esptool.py --port=ESP_SERIAL_PORT write_flash 0x00000 BINARY_PATH


On mac, to see all available serial ports, you can use : `ls /dev/tty.*`

 - **With UI** (*Windows*) : [nodeMCU Flasher](https://github.com/nodemcu/nodemcu-flasher)
