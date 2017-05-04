## TempServer Unresponsive

Tennsy 3.2, Arduino.cc 1.8.2, Teensyduino 1.36
Compile options: 48 MHz, Fast

### Teensy output
Starting and stopping the browser seemed to break things easily.
Teensy excecution has not stopped, but http requests are being ignored.
SPI communication is active.
Where is the trouble: in the WIZ850io, Ethernet library?
No exceptions are being thrown.
I have SPI captures but they will take a bit of effort to decode.
Note that there were some (1000 msec) timeouts as defined by incomplete http request at the application level, and the recovery from those appears to have worked.
These requests are from my Android phone, and it is making one http request at a time, as it should.
```
....'.GET / HTTP/1.1
Host: systronix.hopto.org:8080
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Encoding: gzip,deflate,sdch
Accept-Language: en-US,en;q=0.8,es-US;q=0.6,es;q=0.4,es-419;q=0.2
Cache-Control: max-age=0
Forwarded: for=73.63.1.53
Referer: http://systronix.hopto.org:8080/
Save-Data: on
Scheme: http
Upgrade-Insecure-Requests: 1
Via: 1.1 Chrome-Compression-Proxy
X-Forwarded-For: 73.63.1.53
Connection: Keep-alive
User-Agent: Mozilla/5.0 (Linux; Android 5.1; Z955A Build/LMY47O) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.83 Mobile Safari/537.36

Sending Response...done
Out of while...
client disconnected
Temp 20.062500 C
Timeout count=3
Temp is 20.06C, 3 timeouts, 12540 http requests, 8926 sec max w/o client

GET /favicon.ico HTTP/1.1
Host: systronix.hopto.org:8080
Accept: image/webp,image/*,*/*;q=0.8
Accept-Encoding: gzip,deflate,sdch
Accept-Language: en-US,en;q=0.8,es-US;q=0.6,es;q=0.4,es-419;q=0.2
Forwarded: for=73.63.1.53
Referer: http://systronix.hopto.org:8080/
Save-Data: on
Scheme: http
Via: 1.1 Chrome-Compression-Proxy
X-Forwarded-For: 73.63.1.53
Connection: Keep-alive
User-Agent: Mozilla/5.0 (Linux; Android 5.1; Z955A Build/LMY47O) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.83 Mobile Safari/537.36

Sending Response...done
Out of while...
client disconnected
Temp 20.062500 C
Timeout count=3
Temp is 20.06C, 3 timeouts, 12541 http requests, 8926 sec max w/o client

.....GET / HTTP/1.1
Host: systronix.hopto.org:8080
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Encoding: gzip,deflate,sdch
Accept-Language: en-US,en;q=0.8,es-US;q=0.6,es;q=0.4,es-419;q=0.2
Cache-Control: max-age=0
Forwarded: for=73.63.1.53
Referer: http://systronix.hopto.org:8080/
Save-Data: on
Scheme: http
Upgrade-Insecure-Requests: 1
Via: 1.1 Chrome-Compression-Proxy
X-Forwarded-For: 73.63.1.53
Connection: Keep-alive
User-Agent: Mozilla/5.0 (Linux; Android 5.1; Z955A Build/LMY47O) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.83 Mobile Safari/537.36

Sending Response...done
Out of while...
client disconnected
Temp 20.062500 C
Timeout count=3
Temp is 20.06C, 3 timeouts, 12542 http requests, 8926 sec max w/o client

.GET /favicon.ico HTTP/1.1
Host: systronix.hopto.org:8080
Accept: image/webp,image/*,*/*;q=0.8
Accept-Encoding: gzip,deflate,sdch
Accept-Language: en-US,en;q=0.8,es-US;q=0.6,es;q=0.4,es-419;q=0.2
Forwarded: for=73.63.1.53
Referer: http://systronix.hopto.org:8080/
Save-Data: on
Scheme: http
Via: 1.1 Chrome-Compression-Proxy
X-Forwarded-For: 73.63.1.53
Connection: Keep-alive
User-Agent: Mozilla/5.0 (Linux; Android 5.1; Z955A Build/LMY47O) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.83 Mobile Safari/537.36

Sending Response...done
Out of while...
client disconnected
Temp 20.062500 C
Timeout count=3
Temp is 20.06C, 3 timeouts, 12543 http requests, 8926 sec max w/o client

...'..........'
..........'..........'..........'..........'..........'..........'
..........'..........'..........'..........'..........'..........'
(no futher response to http requests)