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

2017Jul02			NTP_clock_set
2017Jul01 bboyes  Change to use TeensyID lib for mac address
2017Mar02 bboyes  Testing on Teensy 3.2 and W5500


**** TODO ****
Output sometimes stops after some hours. Why? How to recover? Etnernet.maintain() doesn't?

*/

//---------------------------< I N C L U D E S >--------------------------------------------------------------
#include <SPI.h>
#include <Ethernet.h>					// Ethernet 2 for W5500
#include <EthernetUdp.h>

#include <TeensyID.h>					// https://github.com/systronix/TeensyID
#include <SALT_FETs.h>
#include <DS1307RTC.h>


//---------------------------< D E F I N E S >----------------------------------------------------------------

#define	CS_PIN				8			// resistive touch controller XPT2406 uses SPI

#define	TFT_CS				20			// 10 is default, different on ethernet/touch combo
#define	TFT_DC				21			// 9 is default, different on ethernet/touch combo

#define	PERIPH_RST			22			// SALT I/O such as PCA9557
#define	ETH_RST				9			// ethernet reset pin
#define	ETH_CS				10			// ethernet chip select

#define	NTP_PACKET_SIZE		48			// NTP time stamp is in the first 48 bytes of the message
#define	SEVENTY_YEARS		2208988800UL	// offset from 1900-01-01T00:00:00 to unix epoch 1970-01-01T00:00:00

uint16_t local_port = 8888;       // local port to listen for UDP packets

//char time_server_str[] = "time.nist.gov";		// time.nist.gov NTP server
char time_server_str[] = "pool.ntp.org";		// ntp project pool of servers http://www.pool.ntp.org/zone/us

uint8_t packet_buffer[NTP_PACKET_SIZE];		//buffer to hold incoming and outgoing packets

// SALT_FETs is used here because, for reasons unknown, the DS1307RTC include will cause Teensy to hang unless
// some other something that uses the i2c is also started.  Yet another TODO

SALT_FETs FETs;							// to turn of lights fans, alarm
EthernetUDP Udp;						// A UDP instance to let us send and receive packets over UDP

uint32_t new_millis=0;

uint32_t server_too_busy;

uint8_t mac[6];							// for use with TeensyID lib

//---------------------------< S E T U P >--------------------------------------------------------------------
//
//
//

void setup()
	{
	/*
	* When using with PJRC wiz820 sd adapter
	* https://www.pjrc.com/store/wiz820_sd_adaptor.html [sic]
	* Some SD cards can be sensitive to SPI activity while the Ethernet library is initialized before the SD library.
	* For best compatiblity with all SD cards, these 3 lines are recommended at the beginning of setup().
	* Pins 4 and 10 will be reconfigured as outputs by the SD and Ethernet libraries. Making them input
	* pullup mode before initialization guarantees neither device can respond to unintentional signals
	* while the other is initialized.
	*/
	pinMode(4, INPUT_PULLUP);

	pinMode(ETH_RST, OUTPUT);				// This drives the pin low. Don't see any way to avoid that
	pinMode(PERIPH_RST, OUTPUT);			// High after POR, low when declared output
	digitalWrite(ETH_RST, LOW);				// assert it deliberately
	digitalWrite(PERIPH_RST, LOW);			// low after POR anyway

	pinMode (CS_PIN, INPUT_PULLUP);			// disable resistive touch controller
	pinMode (TFT_CS, INPUT_PULLUP);			// disable LCD display
	pinMode (TFT_DC, INPUT_PULLUP);

	delay(1);								// allow time for pins to settle

	digitalWrite(ETH_RST, HIGH);			// release resets
	digitalWrite(PERIPH_RST, HIGH);

	delay(1);								// time for WIZ850io to reset
	FETs.setup (I2C_FET);						// constructor for SALT_FETs, and PCA9557
	FETs.begin ();
	FETs.init ();								// lights, fans, and alarms all off


	Serial.begin(115200);					// Open serial communications and wait for port to open:
	while((!Serial) && (millis()<10000));	// wait until serial monitor is open or timeout,

	new_millis = millis();

	Serial.printf ("NTP clock set test for Teensy 3\nBuild %s %s\r\n", __TIME__, __DATE__);
	Serial.printf("%u msec to start serial\r\n", new_millis);
	Serial.printf("USB Serialnumber: %u \n", teensyUsbSN());	// print out the USB serial number

	delay(1000);

	teensyMAC(mac);							// get Teensy MAC address
	Serial.print("MAC from Teensy: ");
	Serial.printf("Array MAC Address: %02X:%02X:%02X:%02X:%02X:%02X \r\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);  

	if (0 == Ethernet.begin(mac))			// start Ethernet and UDP
		{
		Serial.printf ("\nFailed to configure Ethernet using DHCP");
		while (1);							// no point in carrying on, so do nothing forevermore
		}

	Udp.begin (local_port);

	Serial.printf("\r\n");
	}


//---------------------------< L O O P >----------------------------------------------------------------------
//
//
//

boolean	clock_set = false;					// flag so we set the clock only once
int32_t	diff;								// difference between NTP time and RTC time; positive diff: NTP leads RTC
int32_t	min_diff = 0x7FFFFFFF;				// worst case RTC lagging
int32_t	max_diff = 0;						// worst case NTP lagging

void loop()
	{
	send_NTP_packet (time_server_str);		// send an NTP packet to a time server
	Serial.printf("@%u ask for time from %s\r\n", millis(), time_server_str);

	delay(1000);							// wait to see if a reply is available	

	if (Udp.parsePacket())
		{    								// We've received a packet, read the data from it
		uint32_t secs_since_1900;
		uint32_t epoch;
		uint32_t rtc_ts;

		extract_time_data (&secs_since_1900, &epoch);
		Serial.printf ("Seconds since Jan 1 1900 = %lu\n", secs_since_1900);
		Serial.printf ("Unix time = %lu\n", epoch);				// print Unix time stamp

		Serial.printf ("The UTC time is %.2d:%.2d:%.2d\n\n",	// print UTC time
			(uint8_t)((epoch  % 86400L) / 3600),				// hour
			(uint8_t)((epoch % 3600) / 60),						// minute
			(uint8_t)(epoch % 60));								// second

		if (clock_set)
			{
			rtc_ts = RTC.get();									// get time from RTC
			Serial.printf ("RTC time = %lu\n", rtc_ts);			// print RTC time stamp
			diff = (int32_t)(epoch - rtc_ts);
			min_diff = min (min_diff, diff);
			max_diff = max (max_diff, diff);
			Serial.printf ("difference: %lu (min: %lu; max: %lu)\n\n", diff, min_diff, max_diff);
			}
		else
			{
			if (RTC.set (epoch))
				{
				Serial.printf ("RTC set to %lu\n", epoch);
				clock_set = true;
				}
			}
		}
	else
		{
		server_too_busy++;
		Serial.printf ("\t%s too busy: %u\n", time_server_str, server_too_busy);
		}

	delay (10000);							// wait ten seconds before asking for the time again
	Ethernet.maintain();
	}


//---------------------------< E X T R A C T _ T I M E _ D A T A >--------------------------------------------
//
// the timestamp starts at byte 40 of the received packet and is four bytes long.  In ARM, lowest array index
// holds the least significant byte but the NTP timestamp is most significant byte in the lowest index so here
// we reorder
//

void extract_time_data (uint32_t* ntp_ts_ptr, uint32_t* unix_ts_ptr)
	{
	Udp.read(packet_buffer, NTP_PACKET_SIZE); // read the packet into the buffer

	*ntp_ts_ptr = *(uint32_t*)&packet_buffer[40];			// grab four bytes from array as uint32_t
	*ntp_ts_ptr = __builtin_bswap32 (*ntp_ts_ptr);		// and reorder

	*unix_ts_ptr = *ntp_ts_ptr - SEVENTY_YEARS;			// convert NTP time to Unix time
	}


//---------------------------< S E N D _ N T P _ P A C K E T >------------------------------------------------
//
// send an NTP request to the time server at the given address
//

void send_NTP_packet (char* address)
	{

	memset (packet_buffer, 0, NTP_PACKET_SIZE);	// set all bytes in the buffer to 0
												// Initialize values needed to form NTP request (see URL above for details)
	packet_buffer[0] = 0b11100011;				// LI, Version, Mode
	packet_buffer[1] = 0;						// Stratum, or type of clock
	packet_buffer[2] = 6;						// Polling Interval
	packet_buffer[3] = 0xEC;					// Peer Clock Precision
												// 8 bytes of zero for Root Delay & Root Dispersion
	packet_buffer[12]  = 49;
	packet_buffer[13]  = 0x4E;
	packet_buffer[14]  = 49;
	packet_buffer[15]  = 52;

												// all NTP fields have been given values, now send a packet requesting a timestamp
	Udp.beginPacket (address, 123);				//NTP requests are to port 123
	Udp.write (packet_buffer, NTP_PACKET_SIZE);
	Udp.endPacket();
	}










