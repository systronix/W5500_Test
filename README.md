# W5500 WIZnet Ethernet Tests
These all use the WIZnet W5500 chip on a board or in the WIZ850io module

## Hardware used
 - Teensy 3.X [Teensy 3.2](https://www.pjrc.com/store/teensy32.html)
 - PRJC [WIZ820io & Micro SD Card Adaptor](https://www.pjrc.com/store/wiz820_sd_adaptor.html) which also works with the WIZ850io module
 - WIZnet [WIZ850io](http://www.wiznet.co.kr/product-item/wiz850io/) - this module uses the W5500 chip
 - Adafruit [M0 Pro](https://www.adafruit.com/products/2417) which appears to be identical to the 
 - Arduino.org [M0 Pro](http://www.arduino.org/products/boards/arduino-m0-pro)
 - WIZnet [W5500 Shield](http://www.wiznet.co.kr/product-item/w5500-ethernet-shield/) which uses the W5500 chip in the Arduino board form factor
 - note: these M0 Pros are *not* identical to the Arduino.cc Zero boards. They are very *close*. Apparently pins #2 and #4 are swapped (see Adafruit M0 page)

## Software and Libraries
 - Remember the schism between Arduino.cc and Arduino.org? Now (2016 Oct 01) they have promised to [kiss and make up](https://blog.arduino.cc/2016/10/01/two-arduinos-become-one-2/) but the unification has not occurred yet and affects these efforts... why can't we all just get along? Oh yeah... that human nature thing.
 - Arduino.org [Arduino 1.7.11](http://www.arduino.org/downloads), or at least a version 1.7.5 or later. Arduino.org 1.7.X *must* be used with the .org M0 Pro. At least I could not achieve success with Arduino.cc 1.6.11 although this seems wrong. Maybe there was something to do with my 1.6.11 install being modified by TeensyDuino?
 - Adafruit [Ethernet2 library](https://github.com/adafruit/Ethernet2) which seems to work well with both Teensy and the Cortex M0 boards. This Adafruit library is actually based on WIZnet code of Soohwan Kim 
 - Arduino.cc [Arduino 1.6.11](https://www.arduino.cc/en/Main/Software) modified for Teensy 3 by TeensyDuino: 
 - PJRC [TeensyDuino 1.30](http://www.pjrc.com/teensy/td_download.html)
 - WIZnet advises you go to [wizwiki.net](wizwiki.net) where you can find [W5500 Ethernet Shield Docs](http://wizwiki.net/wiki/doku.php?id=osh:w5500_ethernet_shield:start) and this [W5500 getting started](http://wizwiki.net/wiki/doku.php?id=osh:w5500_ethernet_shield_getting_started) which refers to [WIZ_Ethernet_Library](https://github.com/Wiznet/WIZ_Ethernet_Library) which has not seen a commit since two years ago. So instead I used the Adafruit Ethernet2 library.

## Installation and Configuration
 - All programs use default SPI pins D10,11,12,13 for Ethernet connection
 - I set my DHCP server to the minimum lease time of 120 seconds. This is a stress test so I want the lease to renew as often as possible.
 - Arduino M0 Pro plugs under the W5500 shield and is programmed with Arduino.org 1.7.11, selecting:
 -- Select Tools > board "Arduino M0 Pro (Programming Port)"" and connect USB cable to the port closest to the M0 power jack
 -- Selection of programmer doesn't seem to matter but it should be "Atmel EDBG ..." since that's what it really is
 -- For the Serial Monitor to work the baud rate must match what is used in the code, 115 kbaud. It's USB... go figure.
 - Teensy 3.2 connects to WIZ850io and is programmed with Arduino.cc 1.6.11 with Teensyduino 1.30
 -- Teensy 3.2 connects to WIZ850io using the PJRC WIZ820io adapter, a custom board, or wires
 -- Select Tools > board "Teensy 3.2/3.1" and I used 48 MHz.
 -- Programmer selection is not critical, default is "AVR ISP". The TeensyDuino extension will pop up and do the actual programming.
 -- Serial monitor baud rate doesn't matter. It's really serial over USB... Why is 1.7.11 different?

## Programs
### DhcpStressTest
 - Originally developed for the WIZ820io which has some ARP/DHCP bugs which necessitate special recovery techniques in code
 - DHCP lease time (on my router) is set to 120 seconds, the minimum allowed by the Asus RT56NU router, and it appears to allow renewal at 1/2 that, or every 60 seconds. 
 - This enables 24 * 60, or 1440 DHCP renewals in 24 hrs vs a more typical one or two. This compresses one or two years of DHCP renewal into 24 hours.
 - Versions for Teensy3 with WIZ850io and the Arduino.org (not the same as Arduino.cc) M0 Pro with WIZnet W5500 Shield

### ILI9341_WIZ820_Test
 - use of Ethernet and the ILI9341 touchscreen at same time
 - moves the ILI9341 to alternate SPI pins

### EthernetKeypadLCD
 - the Arduino Ethernet Shield example adapted to the Teensy and WIZ820io hardware

### NtpTest
 - just as it sounds, to use Network Time Protocol, I have not done a lot with this yet
