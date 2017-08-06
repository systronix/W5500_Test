# TempServer
## 2017 Aug 01 
### Restart from lockup
Sending TyQt reset starts operation again but it starts off very oddly by immediately connecting on all three available sockets:

	Teensy Temperature Server
	Build 16:57:58 Jul 29 2017
	689 msec to start serial
	Teensy3 128-bit UniqueID int array: E4A10000-8E620024-003A300B-32624E45
	USB Serialnumber: 1772780 
	Teensy MAC Address: 04:E9:E5:02:B4:7E 
	Begin server at 192.168.1.10
	W5000socket begin, protocol=1, port=8080
	W5000socket 0
	W5000socket prot=1, RX_RD=0
	    Socket(0) SnSr = Listen SnMR = TCP
	    Socket(1) SnSr = Closed SnMR = Close
	    Socket(2) SnSr = Closed SnMR = Close
	    Socket(3) SnSr = Closed SnMR = Close
	TMP102 Sensor at 0x48
	SetCFG=0x80 SetCFG=0x150 
	Setup Complete!
	Send V/v to toggle verbose, h/H to toggle hush/silent, s/S socket status........'W5000socket begin, protocol=1, port=8080
	W5000socket 1
	W5000socket prot=1, RX_RD=0
	W5000socket begin, protocol=1, port=8080
	W5000socket 2
	W5000socket prot=1, RX_RD=0
	W5000socket begin, protocol=1, port=8080
	W5000socket 3
	W5000socket prot=1, RX_RD=0
	@ 10 sec, Got new client, Temp is 27.250 C
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	GET / HTTP/1.1
	Host: systronix.hopto.org:8080
	Connection: keep-alive
	Cache-Control: max-age=0
	Upgrade-Insecure-Requests: 1
	User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36
	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
	Accept-Encoding: gzip, deflate
	Accept-Language: en-US,en;q=0.8

	Request is complete
	Sending Response...
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	Sent 17
	done
	client stopped
	    Socket(0) SnSr = Closed SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	1 http requests, 0.10 per sec, 0 timeouts
	8 sec max w/o client
	--------

	.@ 11 sec, Got new client, Temp is 27.250 C
	    Socket(0) SnSr = Closed SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	GET /favicon.ico HTTP/1.1
	Host: systronix.hopto.org:8080
	Connection: keep-alive
	Pragma: no-cache
	Cache-Control: no-cache
	User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36
	Accept: image/webp,image/apng,image/*,*/*;q=0.8
	Referer: http://systronix.hopto.org:8080/
	Accept-Encoding: gzip, deflate
	Accept-Language: en-US,en;q=0.8

	Request is complete
	Sending Response...
	    Socket(0) SnSr = Closed SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	Sent 17
	done
	client stopped
	    Socket(0) SnSr = Closed SnMR = TCP
	    Socket(1) SnSr = Closed SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	2 http requests, 0.18 per sec, 0 timeouts
	8 sec max w/o client
	--------

### Lock up
- Tempserver locked up similar to yesterday, in midst of response to client request
- This time I had the Totalphase SPI analyzer running. BUT when I went to look at and save the data, it crashed! Urk. I did get a screen capture. It shows the last SPI message has multiple errors including Partial Last Byte.
- Ethernet CS is low/active, MOSI is high/inactive, MISO is low. So SPI locked up in process of WIZ850io sending data to Teensy.
- Last MOSI data is 0A 00 00 14 9B FF 1F 1F 0D 00 00 00
- Last MISO data is 01 02 03 00 C0 A8 01 01 FF FF FF 00
- Those data above are paired, so while MOSI at the start of the SPI cycle is 0A, MISO is 01

Semi-normal activity. Already too many sockets are in Established state.

	'.W5000socket begin, protocol=1, port=8080
	W5000socket 0
	W5000socket prot=1, RX_RD=0
	@ 154841 sec, Got new client, Temp is 27.375 C
	    Socket(0) SnSr = Listen SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Closed SnMR = TCP
	GET /favicon.ico HTTP/1.1
	Host: systronix.hopto.org:8080
	Accept: image/webp,image/apng,image/*,*/*;q=0.8
	Accept-Encoding: gzip,deflate
	Accept-Language: en-US,en;q=0.8
	Forwarded: for="[2607:fb90:2779:aa40:45ad:a800:368c:867d]"
	Referer: http://systronix.hopto.org:8080/
	Save-Data: on
	Scheme: http
	Via: 1.1 Chrome-Compression-Proxy
	X-Forwarded-For: 2607:fb90:2779:aa40:45ad:a800:368c:867d
	Connection: Keep-alive
	User-Agent: Mozilla/5.0 (Linux; Android 5.1; Z955A Build/LMY47O) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.125 Mobile Safari/537.36

	Request is complete
	Sending Response...
	    Socket(0) SnSr = Listen SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Closed SnMR = TCP
	Sent 17
	done
	client stopped
	    Socket(0) SnSr = Listen SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Closed SnMR = TCP
	    Socket(3) SnSr = Closed SnMR = TCP
	97482 http requests, 0.63 per sec, 8 timeouts
	7793 sec max w/o client
	--------

Above, that request response ended with a socket still in Established state.

Now things go wrong more, with two more sockets Established. Only one at a time should be allowed.
These allocated socket numbers are incorrect. Socket 2 is established but Socket 3 is listening.
Socket.cpp incorrectly emits that Socket 3 was closed and can be used in a new connection.

	...W5000socket begin, protocol=1, port=8080
	W5000socket 2
	W5000socket prot=1, RX_RD=0
	W5000socket begin, protocol=1, port=8080
	W5000socket 3
	W5000socket prot=1, RX_RD=0
	@ 154844 sec, Got new client, Temp is 27.375 C
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	GET / HTTP/1.1
	Host: systronix.hopto.org:8080
	Connection: keep-alive
	Cache-Control: max-age=0
	Upgrade-Insecure-Requests: 1
	User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36
	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
	Referer: http://systronix.hopto.org:8080/
	Accept-Encoding: gzip, deflate
	Accept-Language: en-US,en;q=0.8

	Request is complete
	Sending Response...
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	Sent 17
	done
	client stopped
	    Socket(0) SnSr = Closed SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	97483 http requests, 0.63 per sec, 8 timeouts
	7793 sec max w/o client
	--------

Now we have only one socket Closed and available for a new connection.

Immediately the already open request tries to process.

	@ 154844 sec, Got new client, Temp is 27.375 C
	    Socket(0) SnSr = Closed SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	GET /favicon.ico HTTP/1.1
	Host: systronix.hopto.org:8080
	Connection: keep-alive
	User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36
	Accept: image/webp,image/apng,image/*,*/*;q=0.8
	Referer: http://systronix.hopto.org:8080/
	Accept-Encoding: gzip, deflate
	Accept-Language: en-US,en;q=0.8

	Request is complete
	Sending Response...
	    Socket(0) SnSr = Closed SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	Sent 17

Which socket is being used to respond to the request? Maybe Socket 2 but we can't tell. Execution hangs somewhere in the client.print()
Teensy is not updating the touchscreen.
Similar to the previous day's hang.

## 2017 Jul 30
- Server unresponsive. WIZ85io in SALT 2.1 #2/4
- SPI library updated a couple days earlier to PJRC latest
- link light on green, yellow activity is blinking normally due to other traffic on the subnet.

Here is the normal previous request socket use during the response: one listening, one established. Two closed.

	Request is complete
	Sending Response...
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Listen SnMR = TCP
	    Socket(2) SnSr = Closed SnMR = TCP
	    Socket(3) SnSr = Closed SnMR = Close
	Sent 17
	done

ANow there are three closed sockets available for subsequent use, and one passively listening. All is well:

	client stopped
	    Socket(0) SnSr = Closed SnMR = TCP
	    Socket(1) SnSr = Listen SnMR = TCP
	    Socket(2) SnSr = Closed SnMR = TCP
	    Socket(3) SnSr = Closed SnMR = Close
	57039 http requests, 0.78 per sec, 0 timeouts
	72 sec max w/o client
	--------

End of last request above is normal... But at the next request it all goes wrong. 
*Below, it appears we seemingly get a triple connection request all in one.* All three closed/available sockets get used. This should not be possible in a normal, well-formed request. Execution enters `EthernetClass::socketBegin`, gets a socket in the first level of effort to do so, sets up the socket, emits the message `W5000socket prot=` and returns. But then execution is right back in `EthernetClass::socketBegin` again, without handling any request.

	...W5000socket begin, protocol=1, port=8080
	W5000socket 0
	W5000socket prot=1, RX_RD=0
	W5000socket begin, protocol=1, port=8080
	W5000socket 2
	W5000socket prot=1, RX_RD=0
	W5000socket begin, protocol=1, port=8080
	W5000socket 3
	W5000socket prot=1, RX_RD=0
	@ 73544 sec, Got new client, Temp is 29.188 C
	    Socket(0) SnSr = 0x16   SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	GET / HTTP/1.1
	Host: systronix.hopto.org:8080
	Connection: keep-alive
	Cache-Control: max-age=0
	Upgrade-Insecure-Requests: 1
	User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36
	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
	Referer: http://systronix.hopto.org:8080/
	Accept-Encoding: gzip, deflate
	Accept-Language: en-US,en;q=0.8
	Request is complete
	Sending Response...

*Finally one request is handled and that socket (1 apparently) is closed, **but** socket 2 which was established also starts to close (why)? Only one should have closed).* 

	    Socket(0) SnSr = 0x16   SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	Sent 17
	done
	client stopped
	    Socket(0) SnSr = 0x16   SnMR = TCP
	    Socket(1) SnSr = Closed SnMR = TCP
	    Socket(2) SnSr = ClsWait SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	57040 http requests, 0.78 per sec, 0 timeouts
	72 sec max w/o client
	--------

Then immediately there is a new client without executing `EthernetClass::socketBegin` again. There are no established connections top use in the request. Socket 2 is in close-wait mode so TempServer could still send data to that client, but this is not the correct way to start a new connection.

	@ 73544 sec, Got new client, Temp is 29.188 C
	    Socket(0) SnSr = 0x16   SnMR = TCP
	    Socket(1) SnSr = Closed SnMR = TCP
	    Socket(2) SnSr = ClsWait SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	GET /favicon.ico HTTP/1.1
	Host: systronix.hopto.org:8080
	Connection: keep-alive
	User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36
	Accept: image/webp,image/apng,image/*,*/*;q=0.8
	Referer: http://systronix.hopto.org:8080/
	Accept-Encoding: gzip, deflate
	Accept-Language: en-US,en;q=0.8

	Request is complete
	Sending Response...
	    Socket(0) SnSr = 0x16   SnMR = TCP
	    Socket(1) SnSr = Closed SnMR = TCP
	    Socket(2) SnSr = ClsWait SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP

*At this point, TempServer should be sending the response with `client.println()` and `client.print()`. The first couple of such statements have outout if they are unable to print, and there is no such message. Somewhere in the attempted response execution hangs. Teensy is no longer responding to serial input. Temerature is no longer updated on the touchscreen.*

**Looking at Ethernet module signals, MISO (from WIZ850io) is LOW and so is Ethernet CS (P10). But there is no SCK. So execution is hung attempting to do something with the WIZ850io. I don't have the SPI sniffer running at the moment so I can't see the last SPI transactions.**


## 2017 Jul 29
- More than one socket is established, which should not be possible since requests are handled one at a time and closed when response is complete, assuming the requester is well-behaved and not malicious.
- One socket is stuck in the 'temporary' state of 0x16 which is SYN packet received. W5500 should have sent SYN/ACK, received an ACK from the requester and changed this socket to Established, or change to Closed after a timeout. Apparently none of this happened.
- The output "W5000socket 3" means socketBegin will use socket 3, the one in Listen mode. But socket status reports it is still in Listen mode. Perhaps there is some more delay before socket 3 enters Established mode. But...
- ...socketBegin looks for a socket in Closed mode... and this would not apply to socket 3 which is Listening. What??? 
```
	if (status[s] == SnSR::CLOSED) goto makesocket;
```
- It appears that when makesocket reports it is using socket n it is really using n+1 but looking at the code I don't see how this is possible.
```
	...W5000socket begin, protocol=1, port=8080
	W5000socket 3
	W5000socket prot=1, RX_RD=0
	@ 177107 sec, Got new client, Temp is 28.875 C
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = 0x16   SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	GET / HTTP/1.1
	Host: 192.168.1.10:8080
	Connection: keep-alive
	Cache-Control: max-age=0
	Upgrade-Insecure-Requests: 1
	User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36
	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
	Referer: http://192.168.1.10:8080/
	Accept-Encoding: gzip, deflate
	Accept-Language: en-US,en;q=0.8

	Request is complete
	Sending Response...Sent 17
	done
	client stopped
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Closed SnMR = TCP
	    Socket(2) SnSr = 0x16   SnMR = TCP
	    Socket(3) SnSr = Listen SnMR = TCP
	123363 http requests, 0.70 per sec, 0 timeouts
	351 sec max w/o client
	--------
```

## 2017 Jul 19
- All four sockets are "used up"
- library attempts to force close
```
	W5000socket begin, protocol=1, port=8080
	W5000socket 2
	W5000socket prot=1, RX_RD=0
	W5000socket begin, protocol=1, port=8080
	W5000socket step2
	W5000socket step3
	All 4 Sockets in use
	W5000socket begin, protocol=1, port=8080
	W5000socket step2
	W5000socket step3
	All 4 Sockets in use
	W5000socket begin, protocol=1, port=8080
	W5000socket step2
	W5000socket step3
	All 4 Sockets in use
	W5000socket begin, protocol=1, port=8080
	W5000socket step2
	W5000socket step3
	All 4 Sockets in use
	@ 135581 sec, Got new client, Temp is 30.375 C
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = 0x16   SnMR = TCP		<< SYN connect request received... but not yet processed. Looks like error.
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Establ SnMR = TCP
	GET /favicon.ico HTTP/1.1
	Host: systronix.hopto.org:8080
	Connection: keep-alive
	User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36
	Accept: image/webp,image/apng,image/*,*/*;q=0.8
	Referer: http://systronix.hopto.org:8080/
	Accept-Encoding: gzip, deflate
	Accept-Language: en-US,en;q=0.8

	Request is complete
	Sending Response...Sent 17
	done
	client stopped
	    Socket(0) SnSr = Establ SnMR = TCP		<< all established connections should have closed. so what is this???
	    Socket(1) SnSr = 0x16   SnMR = TCP		<< SYN connect request received... but not yet processed. Looks like error.
	    *Socket(2) SnSr = Closed SnMR = TCP*	<< socket 2 is closed
	    Socket(3) SnSr = Establ SnMR = TCP		<< all established connections should have closed. so what is this???
	128567 http requests, 0.95 per sec, 31 timeouts
	6 sec max w/o client
	--------


	W5000socket begin, protocol=1, port=8080
	*W5000socket 2*			<< use socket 2, it was closed, right?
	W5000socket prot=1, RX_RD=0
	....W5000socket begin, protocol=1, port=8080
	W5000socket step2
	W5000socket step3		<< guess not... it's trying to close it here...
	All 4 Sockets in use	<< ??? How is this possible if socket 2 was closed? Why can't it be opened?
```


## 2017 Jul 17
- There should only be one established connection at a time.
- The used socket doesn't always close successfully. Why not?
```
	W5000socket begin, protocol=1, port=8080
	W5000socket 1
	W5000socket prot=1, RX_RD=0
	@ 6448 sec, Got new client, Temp is 27.812 C
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Listen SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = Closed SnMR = Close
	GET /favicon.ico HTTP/1.1
	newline
	Host: 192.168.1.10:8080
	newline
	Connection: keep-alive
	newline
	User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36
	newline
	Accept: image/webp,image/apng,image/*,*/*;q=0.8
	newline
	Referer: http://192.168.1.10:8080/
	newline
	Accept-Encoding: gzip, deflate
	newline
	Accept-Language: en-US,en;q=0.8
	newline

	newline
	Request is complete
	Sending Response...Sent 17
	done
	client stopped
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Listen SnMR = TCP
	    Socket(2) SnSr = Closed SnMR = TCP
	    Socket(3) SnSr = Closed SnMR = Close
	2976 http requests, 0.46 per sec, 0 timeouts
	11 sec max w/o client
	--------

	..'...W5000socket begin, protocol=1, port=8080
	W5000socket 2
	W5000socket prot=1, RX_RD=0
	@ 6453 sec, Got new client, Temp is 27.812 C
	    Socket(0) SnSr = 0x1c   SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Listen SnMR = TCP
	    Socket(3) SnSr = Closed SnMR = Close
```


## 2017 Jul 15
With debug printf and socket status output it has run over 24 hrs without failing.
```
	..W5000socket begin, protocol=1, port=8080
	W5000socket 1
	W5000socket prot=1, RX_RD=0

	Got a new client connection
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Listen SnMR = TCP
	    Socket(2) SnSr = Closed SnMR = TCP
	    Socket(3) SnSr = 0x1c   SnMR = TCP
	    Socket(4) SnSr = Closed SnMR = Close
	    Socket(5) SnSr = Closed SnMR = Close
	    Socket(6) SnSr = Closed SnMR = Close
	    Socket(7) SnSr = Closed SnMR = Close
	GET / HTTP/1.1
	Host: systronix.hopto.org:8080
	Connection: keep-alive
	Cache-Control: max-age=0
	Upgrade-Insecure-Requests: 1
	User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36
	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
	Referer: http://systronix.hopto.org:8080/
	Accept-Encoding: gzip, deflate
	Accept-Language: en-US,en;q=0.8

	Sending Response...done
	Out of while...
	client disconnected
	@ 90084 sec, Temp is 28.438 C
	40343 http requests, 0.45 per sec, 0 timeouts
	8 sec max w/o client
```

