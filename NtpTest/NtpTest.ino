/*

 Udp NTP Client

 Get the time from a Network Time Protocol (NTP) time server
 Demonstrates use of UDP sendPacket and ReceivePacket
 For more on NTP time servers and the messages needed to communicate with them,
 see http://en.wikipedia.org/wiki/Network_Time_Protocol

 created 4 Sep 2010
 by Michael Margolis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi

 This code is in the public domain.

 */

/** Revisions

2017Jul01 bboyes  Change to use TeensyID lib for mac address
2017Mar02 bboyes  Testing on Teensy 3.2 and W5500


**** TODO ****
Output sometimes stops after some hours. Why? How to recover? Etnernet.maintain() doesn't?

*/

#include <SPI.h>
#include <Ethernet.h>    // Ethernet 2 for W5500
#include <EthernetUdp.h>

//#include <T3Mac.h>
#include <TeensyID.h>   // https://github.com/systronix/TeensyID

#define RES_TOUCH_CS_PIN  8   // resistive touch controller XPT2406 uses SPI

#define TFT_CS 20    // 10 is default, different on ethernet/touch combo
#define TFT_DC 21    // 9 is default, different on ethernet/touch combo

#define PERIPH_RST 22   // SALT I/O such as PCA9557
#define ETH_RST 9 // ethernet reset pin
#define ETH_CS  10  // ethernet chip select

#define SD_CS 4   // on PJRC WIZ8XX adapter, not on SALT

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
uint8_t ext_mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x44 };

unsigned int localPort = 8888;       // local port to listen for UDP packets

//char timeServer[] = "time.nist.gov"; // time.nist.gov NTP server
char timeServer[] = "pool.ntp.org"; // ntp project pool of servers http://www.pool.ntp.org/zone/us


const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

uint32_t new_millis=0;

uint32_t server_too_busy;

// for use with TeensyID lib
uint8_t mac[6];

void setup() {
  /*
   * When using with PJRC wiz820 sd adapter
   * https://www.pjrc.com/store/wiz820_sd_adaptor.html [sic]
   * Some SD cards can be sensitive to SPI activity while the Ethernet library is initialized before the SD library.
   * For best compatiblity with all SD cards, these 3 lines are recommended at the beginning of setup().
   * Pins 4 and 10 will be reconfigured as outputs by the SD and Ethernet libraries. Making them input
   * pullup mode before initialization guarantees neither device can respond to unintentional signals
   * while the other is initialized.
   *
   * We don't use P4 on SALT, it is N/C
   */
  pinMode(SD_CS, INPUT_PULLUP);
  pinMode(ETH_CS, INPUT_PULLUP);

  pinMode(ETH_RST, OUTPUT);         // This drives the pin low. Don't see any way to avoid that
  pinMode(PERIPH_RST, OUTPUT);      // High after POR, low when declared output
  digitalWrite(ETH_RST, LOW);       // assert it deliberately
  digitalWrite(PERIPH_RST, LOW);    // low after POR anyway

  pinMode (RES_TOUCH_CS_PIN, INPUT_PULLUP);  // disable resistive touch controller
  pinMode (TFT_CS, INPUT_PULLUP);    // disable LCD display
  pinMode (TFT_DC, INPUT_PULLUP);    // 

  delay(1);  // allow time for pins to settle

  digitalWrite(ETH_RST, HIGH);      // negate resets
  digitalWrite(PERIPH_RST, HIGH);

  delay(1);                     // time for WIZ850io to reset



  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while((!Serial) && (millis()<10000));    // wait until serial monitor is open or timeout,

  new_millis = millis();

  Serial.println();
  Serial.println("NTP Test for Teensy 3");
  Serial.printf("Build %s %s\r\n", __TIME__, __DATE__);

  Serial.printf("%u msec to start serial\r\n", new_millis);

  // get Teensy MAC address
  teensyMAC(mac);

  // print out the USB serial number
  Serial.printf("USB Serialnumber: %u \n", teensyUsbSN());


  //  pinMode(12, INPUT);   // help make sure MISO is input to Teensy

  delay(1000);


  Serial.print("MAC from Teensy: ");
  Serial.printf("Array MAC Address: %02X:%02X:%02X:%02X:%02X:%02X \r\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);  

  // start Ethernet and UDP
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }
  Udp.begin(localPort);

  Serial.printf("\r\n");
}

void loop() {
  sendNTPpacket(timeServer); // send an NTP packet to a time server
  Serial.printf("@%u ask for time from %s\r\n", millis(), timeServer);

  Serial.println();
  Ethernet.getSocketStatus();

  // wait to see if a reply is available
  delay(1000);
  if (Udp.parsePacket()) { 
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    // the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, extract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("Seconds since Jan 1 1900 = ");
    Serial.println(secsSince1900);

    // now convert NTP time into everyday time:
    Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
    Serial.println(epoch);


    // print the hour, minute and second:
    Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
    Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
    Serial.print(':');
    if (((epoch % 3600) / 60) < 10) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    if ((epoch % 60) < 10) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.println(epoch % 60); // print the second
    Serial.println();
  }
  else
  {
    server_too_busy++;
    Serial.printf("%s too busy: %u", timeServer, server_too_busy);
  }
  // wait ten seconds before asking for the time again
  delay(10000);


  Ethernet.maintain();
}

// send an NTP request to the time server at the given address
void sendNTPpacket(char* address) {
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}










