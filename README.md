# W5500 WIZnet Ethernet Tests
Applies to all boards and modules which use the WIZnet W5500 chip: WIZ850io, W5500 Shield, etc.

## Hardware used
- Teensy 3.2 [Teensy 3.2](https://www.pjrc.com/store/teensy32.html) with ARM Cortex M4
- Teensy 3.2 [breakout board R3](https://www.oshpark.com/shared_projects/Gnvbt7io) at OSH park, essential to map Teensy 3.2 to a standard DIP-style pinout without the awkward bottom header and end pins. Systronix designed a simple assembly jig to help in assembling Teensy 3.2 to this adapter. 
- PRJC [WIZ820io & Micro SD Card Adaptor](https://www.pjrc.com/store/wiz820_sd_adaptor.html) which also works with the WIZ850io module (850io and 820io are pin-compatible). To use this with Ethernet, the CS and DC signals need remapping with cuts on the board. @TODO: add photos of the hacks
  - TFT_CS moves from default 10 to 20
  - TFT_DC moves from default 9 to 21
- WIZnet [WIZ850io](http://www.wiznet.co.kr/product-item/wiz850io/) - about USD $17; this module uses the W5500 chip, will also work with WIZ820io which uses the W5200
- ILI9341 2.8" color touchscreen, available tested [from PJRC](https://www.pjrc.com/store/display_ili9341_touch.html) or take your chances on eBay. A recent order of five on eBay had 4/5 with cracked screens, all with bent pins. Inadequately packaged.
- ILI9341 2.8" color touchscreen, [BuyDisplay ER-TFT028-4](http://www.buydisplay.com/default/serial-spi-2-8-tft-lcd-module-display-320x240-optional-touch-screen) and a custom carrier board with buffers, able to use at least a 36" ribbon cable back to the Teensy host board.
- eBay [WIZ850io clones](http://www.ebay.com/itm/201560299414?_trksid=p2057872.m2749.l2649&ssPageName=STRK%3AMEBIDX%3AIT) - about USD $9; ignore the misleading name in the listing. Five ordered 2017 Feb 25 for testing. These have been tested by PJRC. These are reporterdly the real W5500 cheap on a cheaper Chinese module with other Chinese components. It ain't rocket science so there's no reason these have to be crap.
- Adafruit [M0 Pro](https://www.adafruit.com/products/2417) which appears to be identical to the Arduino.org M0Pro with SAMD21 ARM Cortex M0
- Arduino.org [M0 Pro](http://www.arduino.org/products/boards/arduino-m0-pro)
- WIZnet [W5500 Shield](http://www.wiznet.co.kr/product-item/w5500-ethernet-shield/) which uses the W5500 chip in the Arduino board form factor. I bought this combo to have an official, blessed-by-WIZnet board set which should work out of the box. This turned out to be mostly true thanks to Adafruit Ethernet2
- note: these M0 Pros are *not* identical to the Arduino.cc Zero boards. They are very *close*. Apparently pins #2 and #4 are swapped (see Adafruit M0 page)

## Software and Libraries
### Ethernet2
- Currently using the Ethernet2 library, the Adafruit fork, modified by Systronix, so [this Ethernet2](https://github.com/systronix/Ethernet2)
- Adafruit [Ethernet2 library 1v2](https://github.com/adafruit/Ethernet2) which is required for the W5500 shield. This Adafruit library is actually based on WIZnet code of Soohwan Kim which has not seen any change in 2+ years. The default "Ethernet" library supports only W5100 and W5200 chips.
### Arduino.cc 1.8.2
- Remember the schism between Arduino.cc and Arduino.org? Now (2016 Oct 01) they have promised to [kiss and make up](https://blog.arduino.cc/2016/10/01/two-arduinos-become-one-2/) but the unification has not occurred yet and affects these efforts... why can't we all just get along? Oh yeah... that human nature thing.
- Arduino.cc [Arduino 1.8.11](https://www.arduino.cc/en/Main/Software), also worked with 1.6.11, modified for Teensy 3 by TeensyDuino: 
### TeensyDuino
- PJRC [TeensyDuino 1.36](http://www.pjrc.com/teensy/td_download.html), W5500 support added since TD 1.32 to Pauls' Ethernet library
- Paul has added many optimizations, see [WIZ850io and W5500 discussion thread at PJRC forum](https://forum.pjrc.com/threads/28642-Wiznet-W5500-support/page2?highlight=Wiz850io)
- Wiznet chip version is autodetected
- Support reportedly baked in since TD 1.32, here the [PJRC Github Teensy Ethernet repo](https://github.com/PaulStoffregen/Ethernet)
- PJRC [Ethernet library](https://github.com/PaulStoffregen/Ethernet) at github, which I have forked:
- systronix [fork of PJRC Ethernet](https://github.com/systronix/Ethernet) which has added exception handling, socket status code, etc. 
- Some way to read out the MAC address baked into Teensy 3.0 and later. 
- [Read about Teensy MAC address here](https://forum.pjrc.com/threads/91-teensy-3-MAC-address)
- [defragster's T3Mac library in post #43](https://forum.pjrc.com/attachment.php?attachmentid=7074&d=1462266657) which does disable interrupts and also reads the processor CHIP_ID (T3 and LC), and 128-bit Teensy serial number. 
- [FrankB's TeensyMAC library](\) which does disable interrupts when accessing flash
- [sstaub's TeensyID library](https://github.com/sstaub/TeensyID) which is frankb's code extended with pointers and strings for MAC, USB#, Serial# and ChipID, and UUID [RFC4122](https://tools.ietf.org/html/rfc4122) and also [UUID at Wikipedia](https://en.wikipedia.org/wiki/Universally_unique_identifier) tested with 64-bit memory of Teensy 3.5 and 3.6, and also used by systronix on Teensy 3.2
- [johnnyfp's T3Mac library in post #14](https://forum.pjrc.com/attachment.php?attachmentid=2083&d=1401162864) an arduino IDE library, which does not disable interrupts when accessing flash (but should)
- Arduino.org [Arduino 1.7.11](http://www.arduino.org/downloads), or at least a version 1.7.5 or later. Arduino.org 1.7.X *must* be used with the .org M0 Pro, or now with Arduino.cc 1.8.11 I can build the DHCP stress test program for M0Pro. Don't add TeensyDuino to this Arduino.org installation.
- WIZnet advises you go to [wizwiki.net](wizwiki.net) where you can find [W5500 Ethernet Shield Docs](http://wizwiki.net/wiki/doku.php?id=osh:w5500_ethernet_shield:start) and this [W5500 getting started](http://wizwiki.net/wiki/doku.php?id=osh:w5500_ethernet_shield_getting_started) which refers to [WIZ_Ethernet_Library](https://github.com/Wiznet/WIZ_Ethernet_Library) which has not seen a commit since two years ago. So instead I used the Adafruit Ethernet2 library.

## Installation and Configuration
- All programs use default SPI pins D10,11,12,13 for Ethernet connection. These pins can now be changed (within limits) since TD 1.3.2
- I set my DHCP server to the minimum lease time of 120 seconds. This is a stress test so I want the lease to renew as often as possible.
- Arduino M0 Pro plugs under the W5500 shield and is programmed with Arduino.org 1.7.11, selecting:
  - Select Tools > board "Arduino M0 Pro (Programming Port)"" and connect USB cable to the port closest to the M0 power jack
  - Selection of programmer doesn't seem to matter but it should be "Atmel EDBG ..." since that's what it really is
  - For the Serial Monitor to work the baud rate must match what is used in the code, 115 kbaud. It's USB... go figure.
- Teensy 3.2 connects to WIZ850io and is programmed with Arduino.cc 1.8.11 with Teensyduino 1.35
  - Teensy 3.2 connects to WIZ850io using the PJRC WIZ820io adapter, a custom board, or wires
  - Select Tools > board "Teensy 3.2/3.1" and I used 48 MHz.
  - Programmer selection is not critical, default is "AVR ISP". The TeensyDuino extension will pop up and do the actual programming.
  - Serial monitor baud rate doesn't matter. It's really serial over USB... Why is Arduino.org 1.7.11 different?

## Programs & Logs
### DhcpStressTest
- Originally developed for the WIZ820io which has some ARP/DHCP bugs which necessitate special recovery techniques in code
- DHCP lease time (on my router) is set to 120 seconds, the minimum allowed by the Asus RT56NU router, and it appears to allow renewal at 1/2 that, or every 60 seconds. 
- This enables 24 * 60, or 1440 DHCP renewals in 24 hrs vs a more typical one or two. This compresses one or two years of DHCP renewal into 24 hours.
- Versions for Teensy3 with WIZ850io and the Arduino.org (not the same as Arduino.cc) M0 Pro with WIZnet W5500 Shield
- [Logs for this test](https://github.com/systronix/W5500_Test/blob/master/DhcpStressTest-T3/DHCP_stress_logs.md) 

### ILI9341_Test
- Copied from WIZ820io_test repo 2017 Apr 23.
- Existence of Ethernet and the ILI9341 touchscreen at same time: resets Ethernet and then ignores it, while testing the LCD and touchscreen.
- the point is to show that Ethernet chip doesn't clash on the SPI lines.
- Binaries saved in the bin subfolder 

### TempServer
- TempServer [Socket Debug logs](https://github.com/systronix/W5500_Test/blob/master/TempServer/TempServer_Debug_logs.md) showing [Zombie Sockets](https://forum.pjrc.com/threads/43761-Ethernet-library-socket-issues?p=148714&viewfull=1#post148714)
- Simple temperature server which displays TMP102 temperature from onboard SALT temp sensor, or from a TMP102 breakout
- Intended to be a proof of concept for a highly reliable, secure (not hackable or crashable) Teensy/WIZ850io data server
- Uses a DDNS service and Port Forwarding to operate behind a router/firewall 
- First version stopped responding after some few thousand seconds. Turns out code optimization SMALLEST CODE breaks when printf is used just after client.stop() in Line 335
- you can try the example at [this IP address](http://systronix.hopto.org:8080/)
- some documentation about this apparent optimizer-related bug in [this google drive file](https://docs.google.com/document/d/1ZbH-lGuzJ1XOtw04R_Ga4RLg5KANeHKZRIIN780brBo/edit?usp=sharing), anyone can enter comments
- Working very reliably 2017 Jul 18 after too much effort tracing Zombie Sockets
- running on custom board with also a buffered interface to ILI9341 touchscreen displaying temperature

### Webserver
- taken from the Arduino Ethernet Example "Webserver" with minimal changes to work on our hardware
- but even this would not run for more than a few hours without becoming unresponsive to requests
- I set this aside in 2017 May to work on other things

### Webserver Simple
- start over with Arduino Ethernet webserver example, making even fewer changes, only what is needed to get to run on our hardware, simpler than "Webserver"
- but this also does not render reliably in standard browsers, fails W3 validator, and becomes unresponsive
- back to TempServer as the focus, 2017 July

### NTP Servers
- NTP servers are a surprisingly complex topic, and server response can be [fickle](https://www.google.com/search?q=define+fickle&oq=define+fickle&aqs=chrome..69i57j0l5.3344j0j7&sourceid=chrome&ie=UTF-8).
- Typically we use the [NTP Pool Project](http://www.pool.ntp.org/en/) since it has fewer response fails than [NIST](http://tf.nist.gov/tf-cgi/servers.cgi)
- NTP messages have a lot to [decode](https://www.eecis.udel.edu/~mills/ntp/html/decode.html)
- Good NTP citizens don't request time more often than once per minute. Some servers will give you the Kiss of Death if you pester them.

### NtpTest

- just as it sounds, to use Network Time Protocol. Based on Arduino Ethernet example UdpNtpClient with mods for Teensy and W5500. 
- [Test Logs](https://github.com/systronix/W5500_Test/blob/master/NtpTest/NtpTest_logs.md)

M0Pro version does not work and I don't know why.

### Ntp_clock_set
- Greatly enhanced output of NTP server response, by Scott. With a lot more info about the particular NTP server connection. Quite informative.
- [Test Logs coming soon]

### TODO
Current version of NtpTest runs for weeks without failing. The new NTP_clock_set is not so reliable.
