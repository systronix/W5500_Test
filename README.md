# W5500 WIZnet Ethernet Tests
Applies to all boards and modules which use the WIZnet W5500 chip: WIZ850io, W5500 Shield, etc.

## Hardware used
 - Teensy 3.2 [Teensy 3.2](https://www.pjrc.com/store/teensy32.html) with ARM Cortex M4
 - PRJC [WIZ820io & Micro SD Card Adaptor](https://www.pjrc.com/store/wiz820_sd_adaptor.html) which also works with the WIZ850io module (850io and 820io are pin-compatible). To use this with Ethernet, the CS and DC signals need remapping with cuts on the board. @TODO: add photos of the hacks
 -- TFT_CS moves from default 10 to 20
 -- TFT_DC moves from default 9 to 21
 - WIZnet [WIZ850io](http://www.wiznet.co.kr/product-item/wiz850io/) - about USD $17; this module uses the W5500 chip, will also work with WIZ820io which uses the W5200
 - eBay [WIZ850io clones](http://www.ebay.com/itm/201560299414?_trksid=p2057872.m2749.l2649&ssPageName=STRK%3AMEBIDX%3AIT) - about USD $9; ignore the misleading name in the listing. Five ordered 2017 Feb 25 for testing. These have been tested by PJRC. These are reporterdly the real W5500 cheap on a cheaper Chinese module with other Chinese components. It ain't rocket science so there's no reason these have to be crap.
 - Adafruit [M0 Pro](https://www.adafruit.com/products/2417) which appears to be identical to the Arduino.org M0Pro with SAMD21 ARM Cortex M0
 - Arduino.org [M0 Pro](http://www.arduino.org/products/boards/arduino-m0-pro)
 - WIZnet [W5500 Shield](http://www.wiznet.co.kr/product-item/w5500-ethernet-shield/) which uses the W5500 chip in the Arduino board form factor. I bought this combo to have an official, blessed-by-WIZnet board set which should work out of the box. This turned out to be mostly true thanks to Adafruit Ethernet2
 - note: these M0 Pros are *not* identical to the Arduino.cc Zero boards. They are very *close*. Apparently pins #2 and #4 are swapped (see Adafruit M0 page)

## Software and Libraries
 - Remember the schism between Arduino.cc and Arduino.org? Now (2016 Oct 01) they have promised to [kiss and make up](https://blog.arduino.cc/2016/10/01/two-arduinos-become-one-2/) but the unification has not occurred yet and affects these efforts... why can't we all just get along? Oh yeah... that human nature thing.
 - Arduino.cc [Arduino 1.8.11](https://www.arduino.cc/en/Main/Software), also worked with 1.6.11, modified for Teensy 3 by TeensyDuino: 
 - PJRC [TeensyDuino 1.35](http://www.pjrc.com/teensy/td_download.html), W5500 support added since TD 1.32, Paul has added many optimizations, see [WIZ850io and W5500 discussion thread at PJRC forum](https://forum.pjrc.com/threads/28642-Wiznet-W5500-support/page2?highlight=Wiz850io)
 - PJRC T3Mac library to access the MAC address baked in to Teensy 3.2
 - Adafruit [Ethernet2 library 1v2](https://github.com/adafruit/Ethernet2) which is required for the W5500 shield. This Adafruit library is actually based on WIZnet code of Soohwan Kim which has not seen any change in 2+ years. The default "Ethernet" library supports only W5100 and W5200 chips.
 - Arduino.org [Arduino 1.7.11](http://www.arduino.org/downloads), or at least a version 1.7.5 or later. Arduino.org 1.7.X *must* be used with the .org M0 Pro, or now with Arduino.cc 1.8.11 I can build the DHCP stress test program for M0Pro. Don't add TeensyDuino to this Arduino.org installation.
 - WIZnet advises you go to [wizwiki.net](wizwiki.net) where you can find [W5500 Ethernet Shield Docs](http://wizwiki.net/wiki/doku.php?id=osh:w5500_ethernet_shield:start) and this [W5500 getting started](http://wizwiki.net/wiki/doku.php?id=osh:w5500_ethernet_shield_getting_started) which refers to [WIZ_Ethernet_Library](https://github.com/Wiznet/WIZ_Ethernet_Library) which has not seen a commit since two years ago. So instead I used the Adafruit Ethernet2 library.

## Installation and Configuration
 - All programs use default SPI pins D10,11,12,13 for Ethernet connection. These pins can now be changed (within limits) since TD 1.3.2
 - I set my DHCP server to the minimum lease time of 120 seconds. This is a stress test so I want the lease to renew as often as possible.
 - Arduino M0 Pro plugs under the W5500 shield and is programmed with Arduino.org 1.7.11, selecting:
 -- Select Tools > board "Arduino M0 Pro (Programming Port)"" and connect USB cable to the port closest to the M0 power jack
 -- Selection of programmer doesn't seem to matter but it should be "Atmel EDBG ..." since that's what it really is
 -- For the Serial Monitor to work the baud rate must match what is used in the code, 115 kbaud. It's USB... go figure.
 - Teensy 3.2 connects to WIZ850io and is programmed with Arduino.cc 1.8.11 with Teensyduino 1.35
 -- Teensy 3.2 connects to WIZ850io using the PJRC WIZ820io adapter, a custom board, or wires
 -- Select Tools > board "Teensy 3.2/3.1" and I used 48 MHz.
 -- Programmer selection is not critical, default is "AVR ISP". The TeensyDuino extension will pop up and do the actual programming.
 -- Serial monitor baud rate doesn't matter. It's really serial over USB... Why is Arduino.org 1.7.11 different?

## Programs
### DhcpStressTest
 - Originally developed for the WIZ820io which has some ARP/DHCP bugs which necessitate special recovery techniques in code
 - DHCP lease time (on my router) is set to 120 seconds, the minimum allowed by the Asus RT56NU router, and it appears to allow renewal at 1/2 that, or every 60 seconds. 
 - This enables 24 * 60, or 1440 DHCP renewals in 24 hrs vs a more typical one or two. This compresses one or two years of DHCP renewal into 24 hours.
 - Versions for Teensy3 with WIZ850io and the Arduino.org (not the same as Arduino.cc) M0 Pro with WIZnet W5500 Shield

### ILI9341_WIZ820_Test
 - use of Ethernet and the ILI9341 touchscreen at same time
 - moves the ILI9341 to alternate SPI pins: 

### EthernetKeypadLCD (on my wish list)
 - the Arduino Ethernet Shield example adapted to the Teensy and WIZ820io hardware

### NtpTest
 - just as it sounds, to use Network Time Protocol. Based on Arduino Ethernet example UdpNtpClient with mods for Teensy and W5500. 
 - Typical output:
 	Seconds since Jan 1 1900 = 3697051697
 	Unix time = 1488062897
 	The UTC time is 22:48:17
 - M0Pro version does not work and I don't know why.
