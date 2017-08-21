# TempServer with Ethernet2

## 2017 Aug 19 - Malice Aforethought
Finally some interesting malicious probes.
IP addresses looked up with [icann whois](https://whois.icann.org/en) which you can [learn about here](https://whois.icann.org/en/about-whois), where
it is stated that "Any entity that wants to become a registrar must earn ICANN accreditation." But there are five [Regional Internet Registries](https://en.wikipedia.org/wiki/Regional_Internet_registry) (RIRs) which are components of the Internet Number Registry System (IANA). Each maintains their own whois database, apparently not all linked to ICANN. So you may have to search all five to find specific whois data for a given IP. As in interesting aside, four of the five RISIs have exhausted IPV4 addresses - APNIC as early as 2011.

120.194.X.X is from Beijing, China
This is registered in Asia Pacific Network Information Centre (APNIC). APNIC is the Regional Internet Registry
for the Asia Pacific region, with [apnic whois](http://wq.apnic.net/apnic-bin/whois.pl)
which shows China Mobile Communications Corporation as the owner.
120.194.54.186 is a known infection site for IoT DDOS attacks using Hajime, Wopbot, [Mirai](https://f5.com/labs/articles/threat-intelligence/ddos/mirai-the-iot-bot-that-took-down-krebs-and-launched-a-tbps-attack-on-ovh-22422) or similar malware

37.201.4.100 is a known [Vawtrak](https://news.sophos.com/en-us/2016/06/08/sophoslabs-vawtrak-v2-analysis/) or NeverQuest or Snifula banking trojan infection site 

You can look up details on these or other IP addresses at the [CBL abuseat site](https://www.abuseat.org/lookup.cgi)
```
...@ 230864 sec, Got new client, Temp is 24.875 C
From 192.168.1.194, port 61775
    Socket(0) SnSr=Establ SnMR=TCP IP=192.168.1.194 Port=61775 MAC=6C:62:6D:C3:34:4B
    Socket(1) SnSr=Listen SnMR=TCP
    Socket(2) SnSr=Closed SnMR=TCP IP=192.168.1.194 Port=60005 MAC=6C:62:6D:C3:34:4B
    Socket(3) SnSr=Closed SnMR=TCP IP=67.177.36.6 Port=23953 MAC=20:CF:30:B8:3D:ED
    Socket(4) SnSr=Closed SnMR=TCP IP=37.201.4.100 Port=20015 MAC=20:CF:30:B8:3D:ED
    Socket(5) SnSr=Closed SnMR=TCP IP=120.194.54.186 Port=46043 MAC=20:CF:30:B8:3D:ED
    Socket(6) SnSr=Closed SnMR=TCP IP=120.194.54.186 Port=46050 MAC=20:CF:30:B8:3D:ED
    Socket(7) SnSr=Closed SnMR=TCP IP=120.194.54.186 Port=46070 MAC=20:CF:30:B8:3D:ED
```
## 2017 Aug 06
One Firefox client. Note there are not the duplicated requests, just one every 5 seconds.
I am also outputting remote hardware address (should be remote MAC) but it never changes. Something broken there, not sure where.

	.'....@ 71374 sec, Got new client, Temp is 25.812 C
	From 192.168.1.1, port 58616
	    Socket(0) SnSr=Listen SnMR=TCP
	    Socket(1) SnSr=Establ SnMR=TCP IP=172.58.33.184 Port=48913 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=58616 MAC=20:CF:30:B8:3D:ED
	    Socket(3) SnSr=Closed SnMR=TCP IP=66.249.84.44 Port=61837 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=54327 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Closed SnMR=TCP IP=173.185.52.214 Port=60486 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    ----
	    Socket(0) SnSr=Listen SnMR=TCP
	    Socket(1) SnSr=Establ SnMR=TCP IP=172.58.33.184 Port=48913 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=58616 MAC=20:CF:30:B8:3D:ED
	    Socket(3) SnSr=Closed SnMR=TCP IP=66.249.84.44 Port=61837 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=54327 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Closed SnMR=TCP IP=173.185.52.214 Port=60486 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	--------

	......'@ 71380 sec, Got new client, Temp is 25.812 C
	From 192.168.1.1, port 58623
	    Socket(0) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=58623 MAC=20:CF:30:B8:3D:ED
	    Socket(1) SnSr=Establ SnMR=TCP IP=172.58.33.184 Port=48913 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=Listen SnMR=TCP
	    Socket(3) SnSr=Closed SnMR=TCP IP=66.249.84.44 Port=61837 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=54327 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Closed SnMR=TCP IP=173.185.52.214 Port=60486 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    ----
	    Socket(0) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=58623 MAC=20:CF:30:B8:3D:ED
	    Socket(1) SnSr=Establ SnMR=TCP IP=172.58.33.184 Port=48913 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=Listen SnMR=TCP
	    Socket(3) SnSr=Closed SnMR=TCP IP=66.249.84.44 Port=61837 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=54327 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Closed SnMR=TCP IP=173.185.52.214 Port=60486 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	--------

	.....@ 71385 sec, Got new client, Temp is 25.812 C
	From 192.168.1.1, port 58630
	    Socket(0) SnSr=Listen SnMR=TCP
	    Socket(1) SnSr=Establ SnMR=TCP IP=172.58.33.184 Port=48913 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=58630 MAC=20:CF:30:B8:3D:ED
	    Socket(3) SnSr=Closed SnMR=TCP IP=66.249.84.44 Port=61837 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=54327 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Closed SnMR=TCP IP=173.185.52.214 Port=60486 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    ----
	    Socket(0) SnSr=Listen SnMR=TCP
	    Socket(1) SnSr=Establ SnMR=TCP IP=172.58.33.184 Port=48913 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=58630 MAC=20:CF:30:B8:3D:ED
	    Socket(3) SnSr=Closed SnMR=TCP IP=66.249.84.44 Port=61837 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=54327 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Closed SnMR=TCP IP=173.185.52.214 Port=60486 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	--------

## 2017 Aug 05
Finally we have the ability to track socket use (or abuse) by remote IP. This seems so useful it's surprising this did not already exist in the library.
It's added to printSocketStatus() in socket.cpp. It outputs the socket 'n' DIPR (Destination IP Address) register.

In the Tempserver.ino code, this is a key line:
	EthernetClient client = server.available();
Here server is an instance of EthernetServer. EthernetServer.available() returns an EthernetClient object. Prior to returning a client instance (coming from a device) making an http request, by accessing the Tempserver URL, EthernetServer.available() executes EthernetServer.accept() and EthernetServer.begin(). Those functions attempt to be sure one socket is listening, and if the current connection-request-socket is Established or Close_wait, it returns the client reference as a usable connection.
This means that a Close_wait mode socket gets "recycled" for server-to-client communication. If I understand the TCP socket state diagram, this may be a violation of socket use??? This is because a Close_wait socket has been requested to be closed by the client (with a FIN), and the client cannot make any more use of it other than to wait for the server to send a FIN/ACK and the client to ACK that, a total of three steps.

### Behavior on clean Server startup

	Teensy Temperature Server
	Build 15:53:54 Aug  5 2017
	689 msec to start serial
	Teensy3 128-bit UniqueID int array: E4A10000-8E620024-003A300B-32624E45
	USB Serialnumber: 1772780 
	Teensy MAC Address: 04:E9:E5:02:B4:7E 
	Server at 192.168.1.10
	    Socket(0) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(1) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(2) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(3) SnSr=Closed SnMR=Close IP=0.0.0.0
	Start listening:
	    Socket(0) SnSr=Listen SnMR=TCP IP=0.0.0.0
	    Socket(1) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(2) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(3) SnSr=Closed SnMR=Close IP=0.0.0.0

So we are listening on socket 0. Their has been no connection made yet so the destination IP is 0.0.0.0

	TMP102 Sensor at 0x48
	SetCFG=0x80 SetCFG=0x150 
	Setup Complete!
	Send V/v to toggle verbose, h/H to toggle hush/silent, s/S socket status
	.@ 3 sec, Got new client, Temp is 29.812 C

Then a client requests and receives a new connection, on socket 0, and listening automatically moves to another available socket.
Socket 0 is now the Established connection with client at 66.249.84.44

	From 66.249.84.44, port 60160
	    Socket(0) SnSr=Establ SnMR=TCP IP=66.249.84.44
	    Socket(1) SnSr=Listen SnMR=TCP IP=0.0.0.0
	    Socket(2) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(3) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(4) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(5) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0
	GET / HTTP/1.1
	Host: systronix.hopto.org:8080
	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
	Accept-Encoding: gzip,deflate
	Accept-Language: en-US,en;q=0.8
	Cache-Control: max-age=0
	Forwarded: for="[2607:fb90:a4a4:d1b7:4e36:e8d7:d1ec:969]"
	Save-Data: on
	Scheme: http
	Upgrade-Insecure-Requests: 1
	Via: 1.1 Chrome-Compression-Proxy
	X-Forwarded-For: 2607:fb90:a4a4:d1b7:4e36:e8d7:d1ec:969
	Connection: Keep-alive
	User-Agent: Mozilla/5.0 (Linux; Android 5.1; Z955A Build/LMY47O) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.78 Mobile Safari/537.36

	Request is complete
	Sending Response...
	Sent 48
	Sent head
	Sent body header and build
	Sent temperature
	Sent all of body
	done
	client stopped
	    Socket(0) SnSr=Closed SnMR=TCP IP=66.249.84.44
	    Socket(1) SnSr=Listen SnMR=TCP IP=0.0.0.0
	    Socket(2) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(3) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(4) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(5) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0
	1 http requests, 0.33 per sec, 0 timeouts
	1 sec max w/o client
	--------

Then socket 0 gets Closed, and listening continues on socket 1.
So we expect any new connection to Establish on socket 1.
Bingo: a new client request arrives, but wait another connection from the same client? Why?
The client should refresh only every 5 seconds. Why this immediate other request?

Now the new request is accepted on the listening socket 1 and listening moves to the next available closed socket, which happens
to be socket 0, because the algorithm uses: for (int sock = 0; sock < MAX_SOCK_NUM; sock++) so the lowest Closed socket will
become the new Listener.

	.@ 4 sec, Got new client, Temp is 29.812 C
	From 66.249.84.44, port 37992
	    Socket(0) SnSr=Listen SnMR=TCP IP=66.249.84.44
	    Socket(1) SnSr=Establ SnMR=TCP IP=66.249.84.44
	    Socket(2) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(3) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(4) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(5) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0
	GET /favicon.ico HTTP/1.1
	Host: systronix.hopto.org:8080
	Accept: image/webp,image/apng,image/*,*/*;q=0.8
	Accept-Encoding: gzip,deflate
	Accept-Language: en-US,en;q=0.8
	Forwarded: for="[2607:fb90:a4a4:d1b7:4e36:e8d7:d1ec:969]"
	Referer: http://systronix.hopto.org:8080/
	Save-Data: on
	Scheme: http
	Via: 1.1 Chrome-Compression-Proxy
	X-Forwarded-For: 2607:fb90:a4a4:d1b7:4e36:e8d7:d1ec:969
	Connection: Keep-alive
	User-Agent: Mozilla/5.0 (Linux; Android 5.1; Z955A Build/LMY47O) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.78 Mobile Safari/537.36

	Request is complete
	Sending Response...
	Sent 48
	Sent head
	Sent body header and build
	Sent temperature
	Sent all of body
	done
	client stopped
	    Socket(0) SnSr=Listen SnMR=TCP IP=66.249.84.44
	    Socket(1) SnSr=Closed SnMR=TCP IP=66.249.84.44
	    Socket(2) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(3) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(4) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(5) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0
	2 http requests, 0.50 per sec, 0 timeouts
	1 sec max w/o client
	--------

Now, 5 seconds later comes a new request. I trimmmed out the response details

	.....@ 9 sec, Got new client, Temp is 29.812 C
	From 66.249.84.46, port 36700
	    Socket(0) SnSr=Establ SnMR=TCP IP=66.249.84.46
	    Socket(1) SnSr=Listen SnMR=TCP IP=66.249.84.44
	done
	client stopped
	    Socket(0) SnSr=Closed SnMR=TCP IP=66.249.84.46
	    Socket(1) SnSr=Listen SnMR=TCP IP=66.249.84.44
	3 http requests, 0.33 per sec, 0 timeouts
	5 sec max w/o client
	--------

But here is the unexpected duplicate request:

	.'@ 10 sec, Got new client, Temp is 29.812 C
	From 66.249.84.42, port 63243
	    Socket(0) SnSr=Listen SnMR=TCP IP=66.249.84.46
	    Socket(1) SnSr=Establ SnMR=TCP IP=66.249.84.42
	done
	client stopped
	    Socket(0) SnSr=Listen SnMR=TCP IP=66.249.84.46
	    Socket(1) SnSr=Closed SnMR=TCP IP=66.249.84.42
	    Socket(2) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(3) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(4) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(5) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0
	4 http requests, 0.40 per sec, 0 timeouts
	5 sec max w/o client

After running for a while:

	.....@ 3946 sec, Got new client, Temp is 28.188 C
	From 67.177.36.6, port 53035
	    Socket(0) SnSr=Listen SnMR=TCP IP=67.177.36.6
	    Socket(1) SnSr=Establ SnMR=TCP IP=67.177.36.6
	    Socket(2) SnSr=Closed SnMR=TCP IP=67.177.36.6
	done
	    Socket(0) SnSr=Listen SnMR=TCP IP=67.177.36.6
	    Socket(1) SnSr=Closed SnMR=TCP IP=67.177.36.6
	    Socket(2) SnSr=Closed SnMR=TCP IP=67.177.36.6

What now? An "extra" socket got used? Scroll back through the logs to see where:

	..........'..........'..........'..........'...@ 2323 sec, Got new client, Temp is 28.688 C
	From 66.102.6.10, port 36622
	    Socket(0) SnSr=Listen SnMR=TCP IP=66.249.84.42
	    Socket(1) SnSr=Establ SnMR=TCP IP=66.102.6.10
	    Socket(0) SnSr=Listen SnMR=TCP IP=66.249.84.42
	    Socket(1) SnSr=Closed SnMR=TCP IP=66.102.6.10
	--------

OK, so after the above response, listening on 0

	@ 2323 sec, Got new client, Temp is 28.688 C
	From 66.102.6.14, port 38444
	    Socket(0) SnSr=Establ SnMR=TCP IP=66.102.6.14
	    Socket(1) SnSr=Listen SnMR=TCP IP=66.102.6.10
	    Socket(0) SnSr=Closed SnMR=TCP IP=66.102.6.14
	    Socket(1) SnSr=Listen SnMR=TCP IP=66.102.6.10
	--------

Now listening on 1. The most recent request was handled on socket 0, then closed.

	.......'..........'
	..........'..........'..........'..........'..........'..........'
	..........'..........'..........'..........'..........'..........'
	..........'..........'..........'..........'....@ 2504 sec, Got new client, Temp is 28.688 C
	From 67.177.36.6, port 52403
	    Socket(0) SnSr=Establ SnMR=TCP IP=67.177.36.6
	    Socket(1) SnSr=Establ SnMR=TCP IP=67.177.36.6
	    Socket(2) SnSr=Listen SnMR=TCP IP=0.0.0.0

We were listening on 1, so socket 1 makes the new connection with 67.177.36.6
But wait! Socket 0 which was closed is now also Established with 67.177.36.6?

	    Socket(0) SnSr=Establ SnMR=TCP IP=67.177.36.6
	    Socket(1) SnSr=Closed SnMR=TCP IP=67.177.36.6
	    Socket(2) SnSr=Listen SnMR=TCP IP=0.0.0.0
	--------

Socket 1 gets used and closed. Socket 2 is still listening. But why is socket 0 still open?

	@ 2504 sec, Got new client, Temp is 28.688 C
	From 67.177.36.6, port 52404
	    Socket(0) SnSr=Establ SnMR=TCP IP=67.177.36.6
	    Socket(1) SnSr=Closed SnMR=TCP IP=67.177.36.6
	    Socket(2) SnSr=Listen SnMR=TCP IP=0.0.0.0
	    Socket(0) SnSr=Closed SnMR=TCP IP=67.177.36.6
	    Socket(1) SnSr=Closed SnMR=TCP IP=67.177.36.6
	    Socket(2) SnSr=Listen SnMR=TCP IP=0.0.0.0
	--------

Here what seems to have happened is that 67.177.36.6 has a new request, and lo and behold, socket 0 is already open at that remote IP, so it gets used.
Afterwards, socekt 0 gets closed (finally!)
We'd expect the next request to get handled by the listening socket 2, and it does:
.....@ 2509 sec, Got new client, Temp is 28.688 C
From 67.177.36.6, port 52405
    Socket(0) SnSr=Listen SnMR=TCP IP=67.177.36.6
    Socket(1) SnSr=Closed SnMR=TCP IP=67.177.36.6
    Socket(2) SnSr=Establ SnMR=TCP IP=67.177.36.6


## 2017 Aug 4
From a day ago, Ethernet2 is the library in use, not Ethernet.
### Typical request and response
	@ 62487 sec, Got new client, Temp is 26.062 C
	From 67.177.36.6, port 30615
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = 0x16   SnMR = TCP
	    Socket(4) SnSr = Listen SnMR = TCP
	    Socket(5) SnSr = Closed SnMR = TCP
	    Socket(6) SnSr = Establ SnMR = TCP
	    Socket(7) SnSr = Closed SnMR = TCP
	Sending Response...
	done
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = 0x16   SnMR = TCP
	    Socket(4) SnSr = Listen SnMR = TCP
	    Socket(5) SnSr = Closed SnMR = TCP
	    Socket(6) SnSr = Closed SnMR = TCP
	    Socket(7) SnSr = Closed SnMR = TCP
	--------

	@ 62487 sec, Got new client, Temp is 26.062 C
	From 66.102.6.12, port 34431
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = 0x16   SnMR = TCP
	    Socket(4) SnSr = Establ SnMR = TCP
	    Socket(5) SnSr = Listen SnMR = TCP
	    Socket(6) SnSr = Closed SnMR = TCP
	    Socket(7) SnSr = Closed SnMR = TCP
	Sending Response...
	done
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = 0x16   SnMR = TCP
	    Socket(4) SnSr = Closed SnMR = TCP
	    Socket(5) SnSr = Listen SnMR = TCP
	    Socket(6) SnSr = Closed SnMR = TCP
	    Socket(7) SnSr = Closed SnMR = TCP
	--------

	..@ 62489 sec, Got new client, Temp is 26.062 C
	From 172.58.36.162, port 50062
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = 0x16   SnMR = TCP
	    Socket(4) SnSr = Listen SnMR = TCP
	    Socket(5) SnSr = Establ SnMR = TCP
	    Socket(6) SnSr = Closed SnMR = TCP
	    Socket(7) SnSr = Closed SnMR = TCP
	Sending Response...
	done
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = 0x16   SnMR = TCP
	    Socket(4) SnSr = 0x16   SnMR = TCP
	    Socket(5) SnSr = Closed SnMR = TCP
	    Socket(6) SnSr = Closed SnMR = TCP
	    Socket(7) SnSr = Closed SnMR = TCP
	--------

	.'@ 62490 sec, Got new client, Temp is 26.062 C
	From 172.58.36.162, port 61935
	    Socket(0) SnSr = Establ SnMR = TCP
	    Socket(1) SnSr = Establ SnMR = TCP
	    Socket(2) SnSr = Establ SnMR = TCP
	    Socket(3) SnSr = 0x16   SnMR = TCP
	    Socket(4) SnSr = Establ SnMR = TCP
	    Socket(5) SnSr = Listen SnMR = TCP
	    Socket(6) SnSr = Closed SnMR = TCP
	    Socket(7) SnSr = Closed SnMR = TCP
	Sending Response...