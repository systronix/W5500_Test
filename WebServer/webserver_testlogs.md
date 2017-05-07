# WebServer Test Logs
Test Setup:
- SALT 2.1 board with Teensy 3.2 and WIZ850io
- Arduino 1.8.2 and Teensyduino 1.36
- Example Ethernet>Webserver, with just the IP address changed, no read of analog pins: instead, number of msec since startup
- FF and/or Chrome on LAN with several tabs open so the server gets about 1 request per second
- DDNS to reach from Internet at systronix.hopto.org:8080

## Server stops responding to http requests

### 2017 May 07
Stopped responding after 17.55 hours.
This is built with Arduino 1.8.2 and TD 1.36
There were three FF browser tabs open to the local LAN address and two in Chrome to the Internet address


.GET /favicon.ico HTTP/1.1
Host: systronix.hopto.org:8080
Connection: keep-alive
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/57.0.2987.133 Safari/537.36
Accept: image/webp,image/*,*/*;q=0.8
Referer: http://systronix.hopto.org:8080/
Accept-Encoding: gzip, deflate, sdch
Accept-Language: en-US,en;q=0.8

Sending Response...done
Out of while...
client disconnected
@ 63191 sec, Temp is 24.562 C
37922 http requests, 0.60 per sec, 3 timeouts
101 sec max w/o client

.........'..........'..........'..........'..........'

### 2017 May 05
Stopped responding after about 18 hours. SPI traffic looks the same as when TempServer became unresponsive.
### 2017 May 04
This happened with the stock WebServer after only a few minutes.
I notice there is no firmware-drive hardware reset in this example.