# WebServer Test Logs
Test Setup:
- SALT 2.1 board with Teensy 3.2 and WIZ850io
- Arduino 1.8.2 and Teensyduino 1.36
- Example Ethernet>Webserver, with just the IP address changed, no read of analog pins: instead, number of msec since startup
- FF and/or Chrome on LAN with several tabs open so the server gets about 1 request per second
- DDNS to reach from Internet at systronix.hopto.org:8080
## Server stops responding to http requests
### 2017 May 05
Stopped responding after about 18 hours. SPI traffic looks the same as when TempServer became unresponsive.
### 2017 May 04
This happened with the stock WebServer after only a few minutes.
I notice there is no firmware-drive hardware reset in this example.