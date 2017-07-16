# TempServer

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

