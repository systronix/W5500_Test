# DhcpStressTest_T3 

### 2017 Dec 17
After running for months unattended I have started to pay attention again. Renewals are failing
but rebinding or restarting recovers... mostly... it's been so long since I have looked at the code,
I need to refresh my mind on how it works. But even with a failed restart @121620 it eventually recovers.

Also errors seem to occur in clusters, with long periods of reliable operation between. What would explain this?
Is the DHCP server busy? It would be interesting to have multiple clients running and logging simultaneously
and see if they all fail at the same times.

```
	@118060 192.168.1.124
	@118070 maintain()=1  Renew_F/S Bind_F/S Restart_F/S = 5/1979 0/4 0/1 192.168.1.124
	@118130 maintain()=4  Renew_F/S Bind_F/S Restart_F/S = 5/1979 0/5 0/1 192.168.1.124

	@120410 maintain()=1  Renew_F/S Bind_F/S Restart_F/S = 6/2017 0/5 0/1 192.168.1.124
	@120470 maintain()=4  Renew_F/S Bind_F/S Restart_F/S = 6/2017 0/6 0/1 192.168.1.124

	@121620 maintain()=1  Renew_F/S Bind_F/S Restart_F/S = 7/2036 0/6 0/1 192.168.1.124
	Renew_F/S Bind_F/S Restart_F/S = 7/2036 0/6 0/1
	@121680 maintain()=3 Rebind Failed! Try restsart:Fail DHCP after 65185 msec
	0
	Renew_F/S Bind_F/S Restart_F/S = 7/2036 1/6 1/1 0.0.0.0
	Renew_F/S Bind_F/S Restart_F/S = 7/2036 1/6 1/1
	@121810  Error! IP address: 0.0.0.0 Try restart:OK DHCP after 16305 msec
	1
	192.168.1.124	

	Renew_F/S Bind_F/S Restart_F/S = 7/2073 1/6 1/2
	@124030 maintain()=1  Renew_F/S Bind_F/S Restart_F/S = 8/2073 1/6 1/2 192.168.1.124
	@124100 maintain()=4  Renew_F/S Bind_F/S Restart_F/S = 8/2073 1/7 1/2 192.168.1.124
	@124150 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 8/2074 1/7 1/2 192.168.1.124
	@124170 192.168.1.124	

	@127080 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 8/2123 1/7 1/2 192.168.1.124
	Renew_F/S Bind_F/S Restart_F/S = 8/2123 1/7 1/2
	@127140 maintain()=3 Rebind Failed! Try restsart:OK DHCP after 1148 msec
	1
	 Renew_F/S Bind_F/S Restart_F/S = 8/2123 2/7 1/3 192.168.1.124
	Renew_F/S Bind_F/S Restart_F/S = 8/2123 2/7 1/3
	@127270 192.168.1.124	

	@129910 192.168.1.124
	@129920 maintain()=1  Renew_F/S Bind_F/S Restart_F/S = 9/2168 2/7 1/3 192.168.1.124
	@129980 maintain()=4  Renew_F/S Bind_F/S Restart_F/S = 9/2168 2/8 1/3 192.168.1.124	

	@130630 192.168.1.124
	@130640 maintain()=1  Renew_F/S Bind_F/S Restart_F/S = 10/2178 2/8 1/3 192.168.1.124
	@130700 maintain()=4  Renew_F/S Bind_F/S Restart_F/S = 10/2178 2/9 1/3 192.168.1.124
	@130710 192.168.1.124

	@131170 192.168.1.124
	@131180 maintain()=1  Renew_F/S Bind_F/S Restart_F/S = 11/2185 2/9 1/3 192.168.1.124
	@131250 maintain()=4  Renew_F/S Bind_F/S Restart_F/S = 11/2185 2/10 1/3 192.168.1.124
	@131260 192.168.1.124

	@145980 192.168.1.124
	Renew_F/S Bind_F/S Restart_F/S = 11/2432 2/10 1/3
	@145990 192.168.1.124
	@146000 maintain()=1  Renew_F/S Bind_F/S Restart_F/S = 12/2432 2/10 1/3 192.168.1.124
	@146070 192.168.1.124

	@172000  Error! IP address: 0.0.0.0 Try restart:OK DHCP after 6151 msec
	1
	192.168.1.124
	@172010 192.168.1.124
	@172020 192.168.1.124
	Renew_F/S Bind_F/S Restart_F/S = 12/2432 2/10 1/4
	@172030 192.168.1.124

	@172050 192.168.1.124
	@172060 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 12/2433 2/10 1/4 192.168.1.124
	@172070 192.168.1.124

	@172290 192.168.1.124
	@172300 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 12/2437 2/10 1/4 192.168.1.124
	@172340 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 12/2438 2/10 1/4 192.168.1.124
	@172350 192.168.1.124

	<Note huge time here where operation is stable>

	@336730 192.168.1.124
	@336740 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 12/5178 2/10 1/4 192.168.1.124
	@336750 192.168.1.124

```

### 2017 Jul 05
Had been running fine for weeks, WIZ850io. Sometimes would get a bad IP address, but then recover:
```
	@920790 0.0.0.0
	@920800  Error! IP address: 0.0.0.0 Try restart:OK DHCP after 55506 msec
	1
	192.168.1.213
	@920860 192.168.1.213
```

Inexplicably, yesterday it could not recover:
```
	@1288840 192.168.1.213
	@1288850 maintain()=3 Rebind Failed! Try restsart:Fail DHCP after 60609 msec
	0
	 Renew_F/S Bind_F/S Restart_F/S = 87/15443 7/79 1/8 0.0.0.0
	@1288970  Error! IP address: 0.0.0.0 Try restart:Fail DHCP after 60589 msec
	0
	maintain()=3 Rebind Failed! Try restsart:Fail DHCP after 60589 msec
	0
	 Renew_F/S Bind_F/S Restart_F/S = 87/15443 8/79 3/8 0.0.0.0
	@1289160  Error! IP address: 0.0.0.0 Try restart:Fail DHCP after 60588 msec
	0
```
Also the Ethernet module was very warm to the touch, more than usual. And the WIZ850io yellow activity LED was on solid. Reloading the app and resetting Teensy did not recover operation or make the yellow activity LED normal.
Looking at the code, if a restart fails, we don't use the hardware reset of the WIZ850io. Nor to we drive that on setup. So I added hardware reset code to do both those things.

### 2017 May 20
```
	@769130 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 0/12945 0/0 0/0 192.168.1.213
	@769140 192.168.1.213
	Renew_F/S Bind_F/S Restart_F/S = 0/12945 0/0 0/0
	@769150 192.168.1.213
	@769160 192.168.1.213
```

### 2017 May 16
```
	DHCP Stress Test
	Build 16:45:53 May  5 2017
	
	@432020 192.168.1.213
	@432030 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 0/7271 0/0 0/0 192.168.1.213
	@432040 192.168.1.213
```
### 2017 May 05
loaded new build, no code changes, Arduino 1.8.2 and TD 1.36

### 2017 May 05
Running for 76 hours
```
	@274510 192.168.1.213
	@274530 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 0/4604 0/0 0/0 192.168.1.213
	@274540 192.168.1.213
```

### 2017 Apr 20
Running on SALT 2.1 #3, after 144 hours (reset I didn't expect?), one renewal per minute
```
	@519740 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 0/8748 0/0 0/0 192.168.1.254
	@519750 192.168.1.254
```

Running on PJRC WIZnet adapter, and color touchscreen carrier, USB supply.
369 hours, 22352 DHCP renewals, 6 DHCP restarts needed - all successful, one renew failed, still going
```
	@1328630 192.168.1.214
	@1328640 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 1/22352 0/0 0/6 192.168.1.214
	Renew_F/S Bind_F/S Restart_F/S = 1/22352 0/0 0/6
	@1328650 192.168.1.214
```

### 2017 Apr 23 
after 222 hours
```
	@801600 192.168.1.214
	Renew_F/S Bind_F/S Restart_F/S = 1/13481 0/0 0/6
	@801610 192.168.1.214
	@801620 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 1/13482 0/0 0/6 192.168.1.214
```
### 2017 Apr 03 
after running over 2 weeks (424.6 hours, 17.7 days)
```
	Renew_F/S Bind_F/S Restart_F/S = 3/25705 0/0 0/19
	@1528630 192.168.1.213
	@1528640 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 3/25706 0/0 0/19 192.168.1.213
	@1528650 192.168.1.213
	@1528660 192.168.1.213
	@1528670 192.168.1.213
	@1528680 192.168.1.213
	Renew_F/S Bind_F/S Restart_F/S = 3/25706 0/0 0/19
	@1528690 192.168.1.213
	@1528700 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 3/25707 0/0 0/19 192.168.1.213
	@1528710 192.168.1.213
```

### 2017 Mar 19 
```
	@28720 192.168.1.213
	@28730 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 0/483 0/0 0/0 192.168.1.213
	@28740 0.0.0.0
	Renew_F/S Bind_F/S Restart_F/S = 0/483 0/0 0/0
	@28750  Error! IP address: 0.0.0.0 Try restart:OK DHCP after 665 msec
	1
	192.168.1.213
	@28760 192.168.1.213
	@28770 192.168.1.213

	@34230 192.168.1.213
	@34240 0.0.0.0
	@34250  Error! IP address: 0.0.0.0 Try restart:OK DHCP after 665 msec
	1
	192.168.1.213
	@34260 192.168.1.213
	Renew_F/S Bind_F/S Restart_F/S = 0/574 0/0 0/2
	@34270 192.168.1.213
	@34280 192.168.1.213

	Renew_F/S Bind_F/S Restart_F/S = 0/831 0/0 0/2
	@49630 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 0/832 0/0 0/2 192.168.1.213
	@49640 192.168.1.213
	@49650 192.168.1.213
	@49660 0.0.0.0
	@49670  Error! IP address: 0.0.0.0 Try restart:OK DHCP after 665 msec
	1
	192.168.1.213
	@49680 192.168.1.213
	Renew_F/S Bind_F/S Restart_F/S = 0/832 0/0 0/3
	@49690 192.168.1.213
	@49700 192.168.1.213

	Renew_F/S Bind_F/S Restart_F/S = 0/917 0/0 0/3
	@54790 192.168.1.213
	@54800 maintain()=1  Renew_F/S Bind_F/S Restart_F/S = 1/917 0/0 0/3 0.0.0.0
	@54860  Error! IP address: 0.0.0.0 Try restart:OK DHCP after 3167 msec
	1
	192.168.1.213
	@54870 192.168.1.213
	@54880 192.168.1.213

```
@582170 maintain()=2  Renew_F/S Bind_F/S Restart_F/S = 1/9794 0/0 0/3 192.168.1.213
@582180 192.168.1.213
Renew_F/S Bind_F/S Restart_F/S = 1/9794 0/0 0/3
@582190 192.168.1.213
@582200 192.168.1.213
@582210 0.0.0.0
@582220  Error! IP address: 0.0.0.0 Try restart:OK DHCP after 665 msec
1
192.168.1.213
@582230 192.168.1.213
@582240 192.168.1.213
Renew_F/S Bind_F/S Restart_F/S = 1/9794 0/0 0/4
@582250 192.168.1.213
@582260 192.168.1.213
@582270 192.168.1.213
@582280 