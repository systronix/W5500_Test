# TempServer with Ethernet2

## 2017 Nov 14
Here after a fresh reset with one FF connection. Really odd!
Teensy Temperature Server
Build 18:27:20 Aug  7 2017

```
	......@ 56 sec, Got new client, Temp is 22.688 C
	From 192.168.1.1, port 52771
	    Socket(0) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=52756 MAC=20:CF:30:B8:3D:ED
	    Socket(1) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=52771 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=52735 MAC=20:CF:30:B8:3D:ED
	    Socket(3) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=52768 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=52750 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Listen SnMR=TCP
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	GET / HTTP/1.1
	Host: systronix.hopto.org:8080
	User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:55.0) Gecko/20100101 Firefox/55.0
	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
	Accept-Language: en-US,en;q=0.5
	Accept-Encoding: gzip, deflate
	Connection: keep-alive
	Upgrade-Insecure-Requests: 1
	Cache-Control: max-age=0

	Request is complete
	Sending Response...
	Sent 48
	Sent head
	Sent body header and build
	Sent temperature
	Sent all of body
	    ----
	client stopped
	    Socket(0) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=52756 MAC=20:CF:30:B8:3D:ED
	    Socket(1) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=52771 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=52735 MAC=20:CF:30:B8:3D:ED
	    Socket(3) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=52768 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=52750 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Listen SnMR=TCP
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	8 http requests, 0.14 per sec, 0 timeouts
	9 sec max w/o client
	--------
	...
```
Then some recovery after a few more cycles:
```
	.........@ 189 sec, Got new client, Temp is 22.688 C
	From 192.168.1.1, port 52902
	    Socket(0) SnSr=Listen SnMR=TCP
	    Socket(1) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=52892 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=52902 MAC=20:CF:30:B8:3D:ED
	    Socket(3) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=52768 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=52750 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=52778 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	GET / HTTP/1.1
	Host: systronix.hopto.org:8080
	User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:55.0) Gecko/20100101 Firefox/55.0
	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
	Accept-Language: en-US,en;q=0.5
	Accept-Encoding: gzip, deflate
	Connection: keep-alive
	Upgrade-Insecure-Requests: 1
	Cache-Control: max-age=0

	Request is complete
	Sending Response...
	Sent 48
	Sent head
	Sent body header and build
	Sent temperature
	Sent all of body
	    ----
	client stopped
	    Socket(0) SnSr=Listen SnMR=TCP
	    Socket(1) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=52892 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=52902 MAC=20:CF:30:B8:3D:ED
	    Socket(3) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=52768 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=52750 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=52778 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	24 http requests, 0.13 per sec, 0 timeouts
	26 sec max w/o client
	--------	
```
Then back to badness:
```
	.........@ 269 sec, Got new client, Temp is 22.750 C
	From 192.168.1.1, port 53027
	    Socket(0) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=53025 MAC=20:CF:30:B8:3D:ED
	    Socket(1) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=52993 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=53006 MAC=20:CF:30:B8:3D:ED
	    Socket(3) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=53023 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=53027 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Listen SnMR=TCP
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	GET / HTTP/1.1
	Host: systronix.hopto.org:8080
	User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:55.0) Gecko/20100101 Firefox/55.0
	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
	Accept-Language: en-US,en;q=0.5
	Accept-Encoding: gzip, deflate
	Connection: keep-alive
	Upgrade-Insecure-Requests: 1
	Cache-Control: max-age=0

	Request is complete
	Sending Response...
	Sent 48
	Sent head
	Sent body header and build
	Sent temperature
	Sent all of body
	    ----
	client stopped
	    Socket(0) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=53025 MAC=20:CF:30:B8:3D:ED
	    Socket(1) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=52993 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=53006 MAC=20:CF:30:B8:3D:ED
	    Socket(3) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=53023 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=53027 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Listen SnMR=TCP
	    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
	30 http requests, 0.11 per sec, 0 timeouts
	42 sec max w/o client
	--------
```

## 2017 Nov 14
Here a code failure not seen before. This is a connection from within our LAN, yet it fails to get properly closed, using up almost all sockets. Then, client cannot connect reliably. This is an old build which ran well for a long time.
	Teensy Temperature Server
	Build 18:27:20 Aug  7 2017
So what has changed?
Recent browser updates... but does that make any sense?
Yesterday our xfinity account was changed (faster speed, newer cable modem) but this sort of problem was happening earlier.
These all with one Chrome connection.

```
	......'
	.@ 82981 sec, Got new client, Temp is 22.750 C
	From 192.168.1.1, port 50222
	    Socket(0) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=61182 MAC=20:CF:30:B8:3D:ED
	    Socket(1) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=59251 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=50228 MAC=20:CF:30:B8:3D:ED
	    Socket(3) SnSr=ClsWait SnMR=TCP IP=192.168.1.1 Port=50222 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=60507 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=61266 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=59611 MAC=20:CF:30:B8:3D:ED
	    Socket(7) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=60987 MAC=20:CF:30:B8:3D:ED
	GET /favicon.ico HTTP/1.1
	Host: systronix.hopto.org:8080
	Connection: keep-alive
	User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36
	Accept: image/webp,image/apng,image/*,*/*;q=0.8
	Referer: http://systronix.hopto.org:8080/
	Accept-Encoding: gzip, deflate
	Accept-Language: en-US,en;q=0.8

	Request is complete
	Sending Response...
	Sent 48
	Sent head
	Sent body header and build
	Sent temperature
	Sent all of body
	    ----
	client stopped
	    Socket(0) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=61182 MAC=20:CF:30:B8:3D:ED
	    Socket(1) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=59251 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=0x16   SnMR=TCP IP=192.168.1.1 Port=50228 MAC=20:CF:30:B8:3D:ED
	    Socket(3) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=50222 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=60507 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=61266 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=59611 MAC=20:CF:30:B8:3D:ED
	    Socket(7) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=60987 MAC=20:CF:30:B8:3D:ED
	392 http requests, 0.00 per sec, 1 timeouts
	16510 sec max w/o client
	--------

	..........'..........'..........'..........'.....@ 82245 sec, Got new client, Temp is 22.688 C
	From 46.174.191.31, port 51138
	    Socket(0) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=61182 MAC=20:CF:30:B8:3D:ED
	    Socket(1) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=59251 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=Listen SnMR=TCP
	    Socket(3) SnSr=Establ SnMR=TCP IP=46.174.191.31 Port=51138 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=60507 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=61266 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=59611 MAC=20:CF:30:B8:3D:ED
	    Socket(7) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=60987 MAC=20:CF:30:B8:3D:ED
	GET / HTTP/1.0
	User-Agent: User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36

	Request is complete
	Sending Response...
	Sent 48
	Sent head
	Sent body header and build
	Sent temperature
	Sent all of body
	    ----
	client stopped
	    Socket(0) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=61182 MAC=20:CF:30:B8:3D:ED
	    Socket(1) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=59251 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=Listen SnMR=TCP
	    Socket(3) SnSr=Closed SnMR=TCP IP=46.174.191.31 Port=51138 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=60507 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=61266 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=59611 MAC=20:CF:30:B8:3D:ED
	    Socket(7) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=60987 MAC=20:CF:30:B8:3D:ED
	388 http requests, 0.00 per sec, 1 timeouts
	16510 sec max w/o client

	...

	..........'..........'..........'..........'.....@ 82245 sec, Got new client, Temp is 22.688 C
	From 46.174.191.31, port 51138
	    Socket(0) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=61182 MAC=20:CF:30:B8:3D:ED
	    Socket(1) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=59251 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=Listen SnMR=TCP
	    Socket(3) SnSr=Establ SnMR=TCP IP=46.174.191.31 Port=51138 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=60507 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=61266 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=59611 MAC=20:CF:30:B8:3D:ED
	    Socket(7) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=60987 MAC=20:CF:30:B8:3D:ED
	GET / HTTP/1.0
	User-Agent: User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36

	Request is complete
	Sending Response...
	Sent 48
	Sent head
	Sent body header and build
	Sent temperature
	Sent all of body
	    ----
	client stopped
	    Socket(0) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=61182 MAC=20:CF:30:B8:3D:ED
	    Socket(1) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=59251 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=Listen SnMR=TCP
	    Socket(3) SnSr=Closed SnMR=TCP IP=46.174.191.31 Port=51138 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=60507 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=61266 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=59611 MAC=20:CF:30:B8:3D:ED
	    Socket(7) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=60987 MAC=20:CF:30:B8:3D:ED
	388 http requests, 0.00 per sec, 1 timeouts
	16510 sec max w/o client
```

## 2017 Oct 01

https://www.abuseipdb.com/check/45.63.20.41 Vultr Holdings LLC, vultr.com, NYC, NY. Reported for web and email spam
185.102.219.23 Datadelivery s.r.o. Germany superhosting.cz, reported for Port Scan and Brute-Force attacks.

```

```
## 2017 Sep 30
Here all sockets should be closed. Four are held open.
172.58.36.197 and .219 are TMobile near LA, can only trace back as far as ae19.mpr3.sjc7.us.zip.zayo.com [64.125.30.76]
124.133.200.65 is near Jinan, China:
	inetnum: 124.128.0.0 - 124.135.255.255
	netname: UNICOM-SD
	descr: China Unicom Shandong province network
	descr: China Unicom

What's odd is that one held open is my LAN.
```
	Sent all of body
	    ----
	client stopped
	    Socket(0) SnSr=Establ SnMR=TCP IP=172.58.36.197 Port=52566 MAC=20:CF:30:B8:3D:ED
	    Socket(1) SnSr=Establ SnMR=TCP IP=124.133.200.65 Port=57032 MAC=20:CF:30:B8:3D:ED
	    Socket(2) SnSr=Establ SnMR=TCP IP=172.58.36.197 Port=29228 MAC=20:CF:30:B8:3D:ED
	    Socket(3) SnSr=Establ SnMR=TCP IP=172.58.36.219 Port=46419 MAC=20:CF:30:B8:3D:ED
	    Socket(4) SnSr=Establ SnMR=TCP IP=192.168.1.1 Port=55773 MAC=20:CF:30:B8:3D:ED
	    Socket(5) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=55772 MAC=20:CF:30:B8:3D:ED
	    Socket(6) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=55624 MAC=20:CF:30:B8:3D:ED
	    Socket(7) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=61721 MAC=20:CF:30:B8:3D:ED
	364847 http requests, 0.48 per sec, 62 timeouts
```
## 2017 Sep 19 - more probes from malicious sites

185.100.87.190 from Romania

..@ 14613 sec, Got new client, Temp is 23.500 C
From 139.162.79.87, port 54504
    Socket(0) SnSr=Listen SnMR=TCP
    Socket(1) SnSr=0x16   SnMR=TCP IP=139.162.112.248 Port=59565 MAC=20:CF:30:B8:3D:ED
    Socket(2) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=54105 MAC=20:CF:30:B8:3D:ED
    Socket(3) SnSr=Establ SnMR=TCP IP=139.162.79.87 Port=54504 MAC=20:CF:30:B8:3D:ED
    Socket(4) SnSr=Closed SnMR=TCP IP=192.168.1.1 Port=51710 MAC=20:CF:30:B8:3D:ED
    Socket(5) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
    Socket(6) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
    Socket(7) SnSr=Closed SnMR=Close IP=0.0.0.0 Port=0 MAC=FF:FF:FF:FF:FF:FF
The client at 139.162.79.87 Port=54504 then sent a large number of nulls and an endless stream of exclamation marks until a timeout in TempServer closed the connection.

## 2017 Aug 24 - e-mail 'attack' from Brazil
According to CBL Lookup this IP is infected or NATting for an infected computer, emitting SPAM. It's been requesting and getting a connection to TempServer for a few days now, it just holds the connection open and seems to do nothing more... so it's not a very smart bot. I need to get a port mirror going and sniff this with Wireshark for more details. Also I should add a timeout to close the port if there's no request for some time.
```
	IP=179.220.112.223 Port=39849
```
According to APNIC WHOIS, this belongs to Claro, S.A., in Sao Paulo. They list no abuse email (maybe they don't have Internet?) or phone contact, just a street address.

## 2017 Aug 19 - Malice Aforethought from China and Germany
Finally some interesting malicious probes.
IP addresses looked up with [icann whois](https://whois.icann.org/en) which you can [learn about here](https://whois.icann.org/en/about-whois), where
it is stated that "Any entity that wants to become a registrar must earn ICANN accreditation." But there are five [Regional Internet Registries](https://en.wikipedia.org/wiki/Regional_Internet_registry) (RIRs) which are components of the Internet Number Registry System (IANA). Each maintains their own whois database, apparently not all linked to ICANN. So you may have to search all five to find specific whois data for a given IP. As an interesting aside, four of the five RIRs have exhausted IPV4 addresses - APNIC as early as 2011.

120.194.X.X is from Beijing, China
This is registered in Asia Pacific Network Information Centre (APNIC). APNIC is the Regional Internet Registry
for the Asia Pacific region, with [apnic whois](http://wq.apnic.net/apnic-bin/whois.pl)
which shows China Mobile Communications Corporation as the owner, with an abuse contact. I'll try that.
120.194.54.186 is a known infection site for IoT DDOS attacks using Hajime, Wopbot, [Mirai](https://f5.com/labs/articles/threat-intelligence/ddos/mirai-the-iot-bot-that-took-down-krebs-and-launched-a-tbps-attack-on-ovh-22422) or similar malware

37.201.4.100 is a known [Vawtrak](https://news.sophos.com/en-us/2016/06/08/sophoslabs-vawtrak-v2-analysis/) or NeverQuest or Snifula banking trojan infection site 
This is registered to Unitymedia Group in Koeln, Germany. They have abuse email and phone contact information.

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
## Those "duplicated" requests are for favicon.ico
Doh! Thanks to @drmartin for [his answer](https://forum.pjrc.com/threads/43761-Ethernet-library-socket-issues?p=150145&viewfull=1#post150145) on the PJRC forum.
Chrome does a GET of the main page from TempServer, then immediately another GET for favico.ico, which you can see in the logs:
```
	GET /favicon.ico HTTP/1.1
```
Chrome does this for every keep-alive refresh.
Firefox only does it the first time, which seems the more sensible approach.
My too-simple example doesn't parse out different types of requests, it serves the temperature page to any and all requests... so it currently sends another temperature
page to the favicon requester. Something else to improve.

### Serving a favicon.ico
It's possible to server the favicon from a uSD card [according to this post](https://forum.arduino.cc/index.php?topic=337723.15) so there's a future task.

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