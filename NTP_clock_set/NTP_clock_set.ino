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

#define	PERIF_RST			22			// SALT I/O such as PCA9557
#define	ETH_RST				9			// ethernet reset pin
#define	ETH_CS				10			// ethernet chip select

#define	NTP_PACKET_SIZE		48			// NTP time stamp is in the first 48 bytes of the message
#define	SEVENTY_YEARS		2208988800UL	// offset from 1900-01-01T00:00:00 to unix epoch 1970-01-01T00:00:00

#define	LOCAL_PORT			8888

//char time_server_str[] = "time.nist.gov";		// time.nist.gov NTP server
char time_server_str[] = "pool.ntp.org";		// ntp project pool of servers http://www.pool.ntp.org/zone/us
//char time_server_str[] = "198.60.22.240";		// xmission ipv4 address
//char time_server_str[] = "clock.xmission.com";

uint8_t packet_buffer[NTP_PACKET_SIZE];		//buffer to hold incoming and outgoing packets

// SALT_FETs is used here because, for reasons unknown, the DS1307RTC include will cause Teensy to hang unless
// some other something that uses the i2c is also started.  Yet another TODO

SALT_FETs FETs;							// to turn of lights fans, alarm
EthernetUDP Udp;						// A UDP instance to let us send and receive packets over UDP

uint32_t new_millis=0;

uint32_t server_too_busy_count;
uint32_t kiss_o_death_count;
uint32_t response_count;
uint32_t primary_stratum_count;

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
	pinMode(PERIF_RST, OUTPUT);				// High after POR, low when declared output
	digitalWrite(ETH_RST, LOW);				// assert it deliberately
	digitalWrite(PERIF_RST, LOW);			// low after POR anyway

	pinMode (CS_PIN, INPUT_PULLUP);			// disable resistive touch controller
	pinMode (TFT_CS, INPUT_PULLUP);			// disable LCD display
	pinMode (TFT_DC, INPUT_PULLUP);

	delay(1);								// allow time for pins to settle

	digitalWrite(ETH_RST, HIGH);			// release resets
	digitalWrite(PERIF_RST, HIGH);

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

	new_millis = millis();
	Serial.printf ("configuring ethernet\n");

	if (0 == Ethernet.begin (mac, 10000))	// start Ethernet with 10ish second timeout
		{
		Serial.printf ("\nFailed to configure Ethernet using DHCP after %lumS", millis()-new_millis);
		while (1);							// no point in carrying on, so do nothing forevermore
		}

	if (0 == Udp.begin (LOCAL_PORT))		// start udp
		{
		Serial.printf ("\nUdp.begin() failed");
		while (1);							// no point in carrying on, so do nothing forevermore
		}

	Serial.printf("\nSend V/v to toggle verbose\n");
	}


//---------------------------< L O O P >----------------------------------------------------------------------
//
//
//

boolean	clock_set = false;					// flag so we set the clock only once
boolean summary_flag = true;				// flag to tell us that we've printed the 10 minute summary; true at startup because pointless
boolean	verbose = false;					// packet dump after every transaction
int32_t	diff;								// difference between NTP time and RTC time; positive diff: NTP leads RTC
int32_t	min_diff = 0x7FFFFFFF;				// worst case RTC lag time
int32_t	max_diff = 0;						// worst case NTP lag time
uint8_t	inbyte;

uint32_t NTP_wait_timer_start_time;
uint32_t timer;
//uint32_t timer_min = 0xFFFFFFFF;			// meaningless with 100mS delay
uint32_t timer_max = 0;
//uint32_t timer_sum = 0;					// meaningless with 100mS delay
//uint32_t timer_avg;						// meaningless with 100mS delay


void loop()
	{
	uint32_t event_millis = millis();
	uint32_t event_secs = event_millis/1000;

	Serial.println();
	Ethernet.getSocketStatus(4);

	Serial.printf ("@%.2d:%.2d:%.2d.%.4d ask for time from %s\r\n",
		(uint8_t)((event_secs % 86400L) / 3600),	// hour
		(uint8_t)((event_secs % 3600) / 60),		// minute
		(uint8_t)(event_secs % 60),					// second
		(uint8_t)(event_millis % 1000),				// milisecond
		time_server_str);

	send_NTP_packet (time_server_str);				// send an NTP packet to a time server
	NTP_wait_timer_start_time = millis ();			// mark the start time

	while (1)										// loop until timeout or we get an NTP packet
		{
		timer = millis() - NTP_wait_timer_start_time;
		if ((100 <= timer) && (1000 > timer))		// don't check for a response until we've waited for 100mS
			{
			if (Udp.parsePacket())					// returns number of bytes in packet or 0
				{
				time_t secs_since_1900;
				time_t epoch;
				time_t rtc_ts;

				if (SUCCESS != extract_time_data (&secs_since_1900, &epoch))
					{
					Serial.printf ("udp read failed\n");
					while(1);
					}

				Serial.printf ("\tNTP ts: %lu\n", secs_since_1900);
				Serial.printf ("\tUnix ts: %lu\n", epoch);				// print Unix time stamp

				Serial.printf ("\tUTC time: %.2d:%.2d:%.2d\n\n",		// print UTC time
					(uint8_t)((epoch  % 86400L) / 3600),				// hour
					(uint8_t)((epoch % 3600) / 60),						// minute
					(uint8_t)(epoch % 60));								// second

				if (clock_set)
					{
					rtc_ts = RTC.get();									// get time from RTC
					Serial.printf ("\tRTC ts: %lu\n", rtc_ts);			// print RTC time stamp
					diff = (int32_t)(epoch - rtc_ts);
					min_diff = min (min_diff, diff);
					max_diff = max (max_diff, diff);
					Serial.printf ("\tNTP Unix/RTC difference: %ld (NTP max lag: %ld; NTP max lead: %ld)\n\n", diff, min_diff, max_diff);
					if (verbose)
						dump_NTP_packet ();
					}
				else
					{
					if (RTC.set (epoch))
						{
						Serial.printf ("RTC set to %lu\n", epoch);
						clock_set = true;
						dump_NTP_packet ();
						}
					else
						Serial.printf ("RTC.set() failed\n");			// can't know why; RTC.set() returns boolean
					}

				if (0 == packet_buffer[1])								// if stratum is 0
					{													// print message
					kiss_o_death_count++;
					Serial.printf ("\tkiss o' death message: %c%c%c%c (%ld)\n\n", packet_buffer[12], packet_buffer[13], packet_buffer[14], packet_buffer[15], kiss_o_death_count);
					}
				if (1 == packet_buffer[1])								// if primary stratum
					{													// print message
					primary_stratum_count++;
					Serial.printf ("\tprimary stratum ID code: %c%c%c%c (%ld)\n\n", packet_buffer[12], packet_buffer[13], packet_buffer[14], packet_buffer[15], primary_stratum_count);
					}

				response_count++;
				break;
				}
			}
		else														// no NTP packet yet
			{
			if (1000 > timer)
				continue;											// still waiting; loop back and try again
			else
				{													// waited too long
				server_too_busy_count++;
				Serial.printf ("\t%s too busy: %u\n", time_server_str, server_too_busy_count);
				break;												// break out of the loop
				}
			}
		}

	if (1000 > timer)												// do not include timeouts
		{
		timer -= 100;												// remove our default delay
//		timer_min = min (timer_min, timer);							// save min; with 100mS delay, don't really know what min is
		timer_max = max (timer_max, timer);							// save max
//		timer_sum += timer;
//		timer_avg = timer_sum/response_count;						// now meaningless with 100mS delay
		}

//	Serial.printf("\tresponse time: %lu; min: %lu; max: %lu; avg: %lu\n\n", timer, timer_min, timer_max, timer_avg);
	Serial.printf("\tresponse time: %lu; max: %lu\n\n", timer, timer_max);	// with 100mS delay, don't really know what min or avg areis

	if ((0 == (uint8_t)((event_secs % 3600) / 60) % 10) && !summary_flag)
		{
		Serial.printf ("10 minute summary:\n\tattempts: %lu\n\ttoo busy: %lu\n\tkiss o' death: %lu\n\tprimary stratum: %lu\n\n",
			response_count + server_too_busy_count,					// attempts
			server_too_busy_count,
			kiss_o_death_count,
			primary_stratum_count);
		summary_flag = true;
		}
	else if (((uint8_t)((event_secs % 3600) / 60) % 10) && summary_flag)
		summary_flag = false;


	delay (60000);													// wait before asking for the time again

	if (0 < Serial.available())
		{
		inbyte = Serial.read();
		if (('v' == (inbyte)) || ('V' == (inbyte)))
			{
			verbose = !verbose;
			Serial.printf("\r\nverbose: %s ", verbose ? "true" : "false");
			}
		}

	Ethernet.maintain();
	}


//---------------------------< E X T R A C T _ T I M E _ D A T A >--------------------------------------------
//
// the timestamp starts at byte 40 of the received packet and is four bytes long.

// ARM is little endian ls byte in lowest memory address.  Network protocol is big endian.  In an array of bytes,
// lowest array index holds the most significant byte but when we grab four at once (as if the memory address
// is a unit32_t, the byte order is ass backwards.  But, we can flip the order to get the correct result.
//

uint8_t extract_time_data (time_t* ntp_ts_ptr, time_t* unix_ts_ptr)
	{
	int32_t	bytes_read;
	bytes_read = Udp.read(packet_buffer, NTP_PACKET_SIZE);	// read the packet into the buffer
	
	if (-1 == bytes_read)
		{
		Serial.printf ("udp packet empty\n");
		return FAIL;
		}
	
	if (NTP_PACKET_SIZE != bytes_read)
		{
		Serial.printf ("udp read %ld bytes\n", bytes_read);
		return FAIL;
		}

	*ntp_ts_ptr = *(time_t*)&packet_buffer[40];			// grab four bytes from array as uint32_t
	*ntp_ts_ptr = __builtin_bswap32 (*ntp_ts_ptr);		// and reorder

	*unix_ts_ptr = *ntp_ts_ptr - SEVENTY_YEARS;			// convert NTP time to Unix time
	return SUCCESS;
	}


//---------------------------< D U M P _ N T P _ P A C K E T >------------------------------------------------
//
// dump the content of the received NTP packet
//

void dump_NTP_packet (void)
	{
	uint32_t	temp32;

	Serial.printf ("NTP rx packet dump:\n");
	Serial.printf ("\t [0]: 0x%.2X\n", packet_buffer[0]);
	Serial.printf ("\t\t[0]: %d - leap indicator\n", packet_buffer[0] >> 6);
	Serial.printf ("\t\t[0]: %d - version\n", (packet_buffer[0] & 0b00111000) >> 3);
	Serial.printf ("\t\t[0]: %d - mode\n", packet_buffer[0] & 0b00000111);
	Serial.printf ("\t [1]: 0x%.2X (%d) - stratum\n", packet_buffer[1], packet_buffer[1]);
	Serial.printf ("\t [2]: 0x%.2X (%d) - poll\n", packet_buffer[2], (int8_t)packet_buffer[2]);
	Serial.printf ("\t [3]: 0x%.2X (%d) - precision\n", packet_buffer[3], (int8_t)packet_buffer[3]);

	temp32 = *(uint32_t*)&packet_buffer[4];
	temp32 = __builtin_bswap32 (temp32);
	Serial.printf ("\t [4]: 0x%.8X (%0d.%d) - root delay\n", temp32, (int16_t)(temp32 >> 16), (uint16_t)temp32);	// TODO fix this

	temp32 = *(uint32_t*)&packet_buffer[8];
	temp32 = __builtin_bswap32 (temp32);
	Serial.printf ("\t [8]: 0x%.8X (%0d.%d) - root dispersion\n", temp32, (uint16_t)(temp32 >> 16), (uint16_t)temp32);	// TODO fix this

	temp32 = *(uint32_t*)&packet_buffer[12];
	temp32 = __builtin_bswap32 (temp32);
	Serial.printf ("\t[12]: 0x%.8X (%lu) - reference ID\n", temp32, temp32);

	temp32 = *(uint32_t*)&packet_buffer[16];
	temp32 = __builtin_bswap32 (temp32);
	Serial.printf ("\t[16]: 0x%.8X (%lu) - reference TS (int)\n", temp32, temp32);

	temp32 = *(uint32_t*)&packet_buffer[20];
	temp32 = __builtin_bswap32 (temp32);
	Serial.printf ("\t[20]: 0x%.8X (%lu) - reference TS (frac)\n", temp32, temp32);

	temp32 = *(uint32_t*)&packet_buffer[24];
	temp32 = __builtin_bswap32 (temp32);
	Serial.printf ("\t[24]: 0x%.8X (%lu) - origin TS (int)\n", temp32, temp32);

	temp32 = *(uint32_t*)&packet_buffer[28];
	temp32 = __builtin_bswap32 (temp32);
	Serial.printf ("\t[28]: 0x%.8X (%lu) - origin TS (frac)\n", temp32, temp32);

	temp32 = *(uint32_t*)&packet_buffer[32];
	temp32 = __builtin_bswap32 (temp32);
	Serial.printf ("\t[32]: 0x%.8X (%lu) - receive TS (int)\n", temp32, temp32);

	temp32 = *(uint32_t*)&packet_buffer[36];
	temp32 = __builtin_bswap32 (temp32);
	Serial.printf ("\t[36]: 0x%.8X (%lu) - receive TS (frac)\n", temp32, temp32);

	temp32 = *(uint32_t*)&packet_buffer[40];
	temp32 = __builtin_bswap32 (temp32);
	Serial.printf ("\t[40]: 0x%.8X (%lu) - transmit TS (int)\n", temp32, temp32);

	temp32 = *(uint32_t*)&packet_buffer[44];
	temp32 = __builtin_bswap32 (temp32);
	Serial.printf ("\t[44]: 0x%.8X (%lu) - transmit TS (frac)\n\n", temp32, temp32);
	}


//---------------------------< S E N D _ N T P _ P A C K E T >------------------------------------------------
//
// send an NTP request to the time server at the given address
//

void send_NTP_packet (char* address)
	{
	memset (packet_buffer, 0, NTP_PACKET_SIZE);	// set all bytes in the buffer to 0
												// Initialize values needed to form NTP request (see URL above for details)
	packet_buffer[0] = 0b00100011;				// msb to lsb: LI (00 - server message); Version (100 4);  Mode (011 = client) (0x23)

												// all NTP fields have been given values, now send a packet requesting a timestamp
	Udp.beginPacket (address, 123);				//NTP requests are to port 123
	Udp.write (packet_buffer, NTP_PACKET_SIZE);
	Udp.endPacket();
	}










