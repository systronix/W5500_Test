# NtpTest Logs

## Teensy 3.2 with WIZ850io and 2.8" touchscreen on PJRC adapter, USB power
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
