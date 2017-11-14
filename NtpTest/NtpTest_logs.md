# NtpTest Logs
Note: NTP time value is the number of msec since the epoch started. NTP epoch starts Jan 1, 1900 whereas Unix epoch starts 1 Jan 1970. Perhaps surprisingly, it's a bit more complicated than that, especailly for [Unix time.](https://en.wikipedia.org/wiki/Unix_time)

## Teensy 3.2 with WIZ850io and 2.8" touchscreen on PJRC adapter, USB power

### 2017 Nov 13
Here's what happened when the DHCP server went down in process of upgrading our Internet connection:

```
	Renew_F/S Bind_F/S Restart_F/S = 0/4508 0/0 0/1
	@267970 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 0/4509 0/0 0/1 192.168.1.125
	@267980 192.168.1.125
	@267990 192.168.1.125
	@268000 192.168.1.125
	@268010 192.168.1.125
	@268020 192.168.1.125
	Renew_F/S Bind_F/S Restart_F/S = 0/4509 0/0 0/1
	@268030 maintain()=1  Renew_F/S Bind_F/S Restart_F/S = 1/4509 0/0 0/1 0.0.0.0
	@268100  Error! IP address: 0.0.0.0 Try restart:OK DHCP after 3398 msec
	1
	192.168.1.125
	@268110 192.168.1.125
	@268120 192.168.1.125
	@268130 192.168.1.125
	@268140 192.168.1.125
	Renew_F/S Bind_F/S Restart_F/S = 1/4509 0/0 0/2
	@268150 192.168.1.125
	@268160 maintain()=1  Renew_F/S Bind_F/S Restart_F/S = 2/4509 0/0 0/2 192.168.1.125
	@268220 maintain()=3 Rebind Failed! Try restsart:Fail DHCP after 61039 msec
	0
	 Renew_F/S Bind_F/S Restart_F/S = 2/4509 1/0 1/2 0.0.0.0
	@268350  Error! IP address: 0.0.0.0 Try restart:Fail DHCP after 61039 msec
	 Reset Ethernet module! HW reset count now=1
	0
	0.0.0.0
	@268420  Error! IP address: 0.0.0.0 Try restart:Fail DHCP after 61039 msec
	 Reset Ethernet module! HW reset count now=2
	0
	0.0.0.0
	@268490  Error! IP address: 0.0.0.0 Try restart:OK DHCP after 57032 msec
	1
	192.168.1.124
	@268550 192.168.1.124
	@268560 192.168.1.124
	Renew_F/S Bind_F/S Restart_F/S = 2/4509 1/0 3/3
	@268570 192.168.1.124
	@268580 192.168.1.124
	@268590 192.168.1.124
	@268600 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 2/4510 1/0 3/3 192.168.1.124
	@268610 192.168.1.124
	@268620 192.168.1.124
	Renew_F/S Bind_F/S Restart_F/S = 2/4510 1/0 3/3
	@268630 192.168.1.124
	@268640 192.168.1.124
	@268650 192.168.1.124
	@268660 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 2/4511 1/0 3/3 192.168.1.124
```

### 2017 Aug 19
Ran for a week while unattended, however we can't know for sure if a power loss caused a system reset on this particular test system.
Also of interest here is that at some point another socket than 0 was opened and subsequently closed. How and why?
```
	    Socket(0) SnSr = Open SnMR = UDP
	    Socket(1) SnSr = Closed SnMR = UDP
	    Socket(2) SnSr = Closed SnMR = Close
	    Socket(3) SnSr = Closed SnMR = Close
	@01:50:55.0253 ask for time from pool.ntp.org
		NTP ts: 3712340918
		Unix ts: 1503352118
		UTC time: 21:48:38

	RTC.set() failed
		response time: 0; max: 717

	10 minute summary:
		attempts: 4398
		too busy: 168
		kiss o' death: 1
		primary stratum: 568
```

### 2017 Jul 04
```
	@1561466650 ask for time from pool.ntp.org
	pool.ntp.org too busy: 4669@1561477702 ask for time from pool.ntp.org
	Seconds since Jan 1 1900 = 3708193730
	Unix time = 1499204930
	The UTC time is 21:48:50

	@1561488754 ask for time from pool.ntp.org
	Seconds since Jan 1 1900 = 3708193741
	Unix time = 1499204941
	The UTC time is 21:49:01

```

### 2017 May 20
```
	@1168264508 ask for time from pool.ntp.org
	pool.ntp.org too busy: 5565@1168275560 ask for time from pool.ntp.org
	pool.ntp.org too busy: 5566@1168286613 ask for time from pool.ntp.org
	Seconds since Jan 1 1900 = 3704181443
	Unix time = 1495192643
	The UTC time is 11:17:23
	...
	@1292698246 ask for time from pool.ntp.org
	Seconds since Jan 1 1900 = 3704305857
	Unix time = 1495317057
	The UTC time is 21:50:57
```
### 2017 May 16
running for 265 hrs, 11.1 days
```
	@955892694 ask for time from pool.ntp.org
	Seconds since Jan 1 1900 = 3703969046
	Unix time = 1494980246
	The UTC time is 0:17:26
```
### 2017 May 05
loaded new build, no code changes, Arduino 1.8.2 and TD 1.36

### 2017 May 05
Running 47 hours
```
@169458352 ask for time from pool.ntp.org
Seconds since Jan 1 1900 = 3703012562
Unix time = 1494023762
The UTC time is 22:36:02
```

### 2017 May 04
Now running for 16 hours
```
@61117054 ask for time from pool.ntp.org
Seconds since Jan 1 1900 = 3702904219
Unix time = 1493915419
The UTC time is 16:30:19
```

### 2017 Apr 29
This test now running for 146.48 hours. 
It's surprising how often the NTP pool is either not responding or couldn't be reached.
Test should be improved to try to determine which is the case. I'd guess the issue is reaching it.
```
	pool.ntp.org too busy: 1658@527195231 ask for time from pool.ntp.org
	The UTC time is 0:16:07

	pool.ntp.org too busy: 1659@527239491 ask for time from pool.ntp.org
	The UTC time is 0:16:51

	@527316908 ask for time from pool.ntp.org
	Seconds since Jan 1 1900 = 3702500289
	Unix time = 1493511489
	The UTC time is 0:18:09
```

### 2017 Apr 09, Sunday afternoon. 
Can't reach pool.ntp.org, no Internet access in office. Why?
Cable modem and switch indicate normal status. So does the router.
Power cycled switch: no change.
Did a minor config change on Asus router (enable logging of dropped packets), which likely causes some kind of reset. 
Now we have Internet:
```
	pool.ntp.org too busy: 5809@77065248 ask for time from pool.ntp.org
	Seconds since Jan 1 1900 = 3700757772
	Unix time = 1491768972
	The UTC time is 20:16:12

	@77076352 ask for time from pool.ntp.org
	Seconds since Jan 1 1900 = 3700757783
	Unix time = 1491768983
	The UTC time is 20:16:23
```
Was working Sat afternoon. All Internet connection at the office is not working, so this really is an error
where the pool can't be reached, not that it is too busy. How do we tell the difference?
```
	@13073889 ask for time from pool.ntp.org
	Seconds since Jan 1 1900 = 3700693780
	Unix time = 1491704980
	The UTC time is 2:29:40

	@13086508 ask for time from pool.ntp.org
	pool.ntp.org too busy: 29@13099127 ask for time from pool.ntp.org
	pool.ntp.org too busy: 30@13111746 ask for time from pool.ntp.org
```
### 2017 Apr 04 after running over 2 weeks
```
	@1282682043 ask for time from pool.ntp.org
	Seconds since Jan 1 1900 = 3700255145
	Unix time = 1491266345
	The UTC time is 0:39:05
```
### 2017 Mar 18 night
Here ET is in msec. So this test has been running for 96+ hours
```
	@347004584 ask for time from pool.ntp.org
	Seconds since Jan 1 1900 = 3698950455
	Unix time = 1489961655
	The UTC time is 22:14:15

	@347015636 ask for time from pool.ntp.org
	Seconds since Jan 1 1900 = 3698950466
	Unix time = 1489961666
	The UTC time is 22:14:26
```
