# TempServer
### 2017 Jul 29
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

### 2017 Jul 19
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


### 2017 Jul 17
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


### 2017 Jul 15
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

