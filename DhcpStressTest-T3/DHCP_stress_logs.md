# DhcpStressTest_T3 
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