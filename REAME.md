# Guide : Comment programmer sur ESP8266 NodeMCUv1

## Build the Firmware
http://nodemcu-build.com/

## Flash the Firmware
 - En ligne de commande (multiplateforme) :
Utilitaire python pour flasher le esp8266 (https://github.com/themadinventor/esptool)
`pip install esptool` ou `git clone https://github.com/themadinventor/esptool`
 - Avec une interface (windows) :
Installer nodeMCU Flasher : https://github.com/nodemcu/nodemcu-flasher

## Compile/Upload Code
[platformio](http://platformio.org/)
	brew install platformio

	// To compile code
	platformio run
	// To upload code
	platformio 

## Monitor
	platformio serialports monitor --port /dev/tty.SLAB_USBtoUART --baud 115200 --eol CR --raw

