## TempServer is locking up

Here it locked up with Ethernet SPI SCK low, MOSI high, MISO low, CS high 
This happened only once. There was a buffer allocation error [thanks @defragster](https://forum.pjrc.com/threads/43572-Optimization-Fast-Faster-Fastest-with-without-LTO?p=141888&viewfull=1#post141888) and it was
this and/or "Smallest Code" optimization which caused incorrect execution when printf() appeared in some 
places in the code.

### Teensy output
This is not a typical complete request.
```
	Teensy Web Server
	811 msec to start serial
	Teensy3 128-bit UniqueID char array: E2A10000 5E0B002D 003B700B 28644E45
	Teensy3 128-bit UniqueID int array: E2A10000-5E0B002D-003B700B-28644E45
	USB Serialnumber: 1275060 
	Teensy MAC Address: 04:E9:E5:01:F2:12 
	server is at 192.168.1.10
	TMP102 Sensor at 0x48
	SetCFG=80 SetCFG=150 .....new client at 56 sec
	GET / HTTP/1.1
	Host: systronix.hopto.org:8080
	Connection: keep-alive
	Cache-Control: max-age=0
	Upgrade-Insecure-Requests: 1
	User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/57.0.2987.133 Safari/537.36
	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
	Accept-Encoding: gzip, deflate, sdch
	Accept-Language: en-US,en;q=0.8,es-US;q=0.6,es;q=0.4,es-419;q=0.2
```

### Router log
131.108.251.44 is in Brazil, whois is short record

216.218.206.94 is Hurricane Electric in Fremont, CA, covers 216.218.128.0 - 216.218.255.255

36.37.186.99 is IRT-VIETTEL-CAMBODIA-KH in Cambodia, covers 36.37.176.0 - 36.37.191.255

```
	Apr 30 19:33:02 kernel: DROP  <4>DROP IN=eth3 OUT= MAC=20:cf:30:b8:3d:ec:00:01:5c:66:00:46:08:00 <1>SRC=131.108.251.44 DST=67.177.21.142 <1>LEN=40 TOS=0x00 PREC=0x20 TTL=49 ID=22266 PROTO=TCP <1>SPT=17431 DPT=23 SEQ=1135678862 ACK=0 WINDOW=22023 RES=0x00 SYN URGP=0 
	
	Apr 30 19:33:20 kernel: DROP  <4>DROP IN=eth3 OUT= MAC=20:cf:30:b8:3d:ec:00:01:5c:66:00:46:08:00 <1>SRC=216.218.206.94 DST=67.177.21.142 <1>LEN=92 TOS=0x00 PREC=0x20 TTL=53 ID=51132 DF PROTO=UDP <1>SPT=18749 DPT=500 LEN=72 
	
	Apr 30 19:34:20 kernel: ACCEPT  <4>ACCEPT IN=br0 OUT=br0 <1>SRC=192.168.1.194 DST=192.168.1.10 <1>LEN=52 TOS=0x00 PREC=0x00 TTL=127 ID=29537 DF PROTO=TCP <1>SPT=50790 DPT=8080 SEQ=1901307933 ACK=0 WINDOW=8192 RES=0x00 SYN URGP=0 OPT (020405B80103030201010402) 
	
	Apr 30 19:34:21 kernel: ACCEPT  <4>ACCEPT IN=br0 OUT=br0 <1>SRC=192.168.1.194 DST=192.168.1.10 <1>LEN=52 TOS=0x00 PREC=0x00 TTL=127 ID=29553 DF PROTO=TCP <1>SPT=50793 
	DPT=8080 SEQ=259207872 ACK=0 WINDOW=8192 RES=0x00 SYN URGP=0 OPT (020405B80103030201010402) 
	
	Apr 30 19:34:23 kernel: DROP  <4>DROP IN=eth3 OUT= MAC=20:cf:30:b8:3d:ec:00:01:5c:66:00:46:08:00 <1>SRC=36.37.186.99 DST=67.177.21.142 <1>LEN=44 TOS=0x00 PREC=0x20 TTL=48 ID=39408 PROTO=TCP <1>SPT=57011 DPT=23 SEQ=1135678862 ACK=0 WINDOW=52387 RES=0x00 SYN URGP=0 OPT (020405A0) 

	Apr 30 19:34:30 kernel: ACCEPT  <4>ACCEPT IN=br0 OUT=br0 <1>SRC=192.168.1.194 DST=192.168.1.10 <1>LEN=52 TOS=0x00 PREC=0x00 TTL=127 ID=29719 DF PROTO=TCP <1>SPT=50838 DPT=8080 SEQ=193720522 ACK=0 WINDOW=8192 RES=0x00 SYN URGP=0 OPT (020405B80103030201010402) 
	Apr 30 19:34:31 kernel: ACCEPT  <4>ACCEPT IN=br0 OUT=br0 <1>SRC=192.168.1.194 DST=192.168.1.10 <1>LEN=52 TOS=0x00 PREC=0x00 TTL=127 ID=29721 DF PROTO=TCP <1>SPT=50838 DPT=8080 SEQ=193720522 ACK=0 WINDOW=8192 RES=0x00 SYN URGP=0 OPT (020405B80103030201010402) 
	Apr 30 19:34:31 kernel: ACCEPT  <4>ACCEPT IN=br0 OUT=br0 <1>SRC=192.168.1.194 DST=192.168.1.10 <1>LEN=48 TOS=0x00 PREC=0x00 TTL=127 ID=29730 DF PROTO=TCP <1>SPT=50838 DPT=8080 SEQ=193720522 ACK=0 WINDOW=8192 RES=0x00 SYN URGP=0 OPT (020405B801010402) 
```