/**
 * DHCP Stress Test for Teensy 3 and WIZnet 850io
 *
 * (based on Arduino Ethernet library example DhcpAddressPrinter by Tom Igoe, modified 9 Apr 2012
 * and also modified by Paul Stoffregen at pjrc.com)
 *
 * Modified by Bruce Boyes to stress test DHCP client with WIX820io and Teensy 3.X
 * Using the PJRC Wiznet and SD card adapter as well as custom board codenamed SALT.
 *
 * Uses SPI default digital pins 10, 11, 12, 13
 *
 * DHCP lease time is set to 120 seconds, the minimum allowed by the Asus RT56NU router,
 * and it appears to allow renewal at 1/2 that, or every 60 seconds. This enables 24 * 60,
 * or 1440 DHCP renewals in 24 hrs vs a more typical one or two. This compresses one
 * or two years of DHCP renewal into 24 hours.
 *
 * https://github.com/systronix   bboyes@systronix.com
 */

/**
 * Revisions
 *
 * 2016 Oct 28	bboyes	Adapted for WIZ850io by using Ethernet2 library
 * 2016 Jan 26 move IP 0 detection and restart to be more proactive
 * 2016 Jan 20	bboyes put in restart in case of IP address 0.0.0.0, which the Arduino library
 * seems to feel is fine as an address, and which also throws no exception with Ethernet.renew()
 * even though it could not possibly have been assigned by DHCP.
 * 2016 Jan 17	bboyes the summary of status got clobbered by change of Arduino preferences,
 * I guess. So adding it back in.
 * 2016 Jan 16	print summary of renew and rebind fail/success every minute
 * 				also track restart fail/success
 *
 *
 */

/*
https://www.pjrc.com/teensy/td_libs_Ethernet.html
http://www.epyon.be/2016/12/06/test-cheap-chinese-wiz850io-ethernet-board/
https://github.com/PaulStoffregen/Ethernet
https://www.arduino.cc/en/reference/ethernet

*/



#include <SPI.h>
// W550 needs Ethernet2 library
#include <Ethernet.h>
#include <T3Mac.h>

#define CS_PIN  8   // resistive touch controller XPT2406 uses SPI

#define TFT_CS 20    // 10 is default, different on ethernet/touch combo
#define TFT_DC 21    // 9 is default, different on ethernet/touch combo

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
uint8_t ext_mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x44 };

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

// for measuring how long a routine takes
uint32_t time_start, time_stop;

uint32_t new_millis = 0;
uint32_t old_millis = 0;	// millis saved every tiem through loop, if new > old
uint32_t old_sec_millis;	// millis saved every second tick

uint32_t new_elapsed_seconds = 0;
uint32_t total_elapsed_seconds = 0;
boolean seconds_tick = false;

uint8_t seconds_five=0;
boolean seconds_five_tick = false;
boolean seconds_ten_tick = false;
boolean minute_tick = false;

uint8_t flag=0;

uint32_t switch_default_error=0;

// if Ethernet.maintain() fails, we try to restart and track results with these
uint32_t restart_fail_count=0, restart_success_count=0;

// renew is Ethernet.maintain() return value
uint8_t renew;
// Ethernet.maintain() fail and success counts
uint32_t renew_success_count=0, renew_fail_count=0, rebind_success_count=0, rebind_fail_count=0;


void setup() {

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
	pinMode(10, INPUT_PULLUP);
	pinMode (CS_PIN, INPUT_PULLUP);  // disable resistive touch controller

	pinMode (TFT_CS, INPUT_PULLUP);    // disable LCD display
	pinMode (TFT_DC, INPUT_PULLUP);    // 

	delay(1);  // allow time for pins to reach 3.3V

	// Open serial communications and wait for port to open:
	Serial.begin(115200);

	//  Serial1.begin(9600);  // TX1, RX1 on Teensy pins 3 and 2, not the USB serial output!

	// Wait here for up to 10 seconds to see if we will use Serial Monitor, so output is not lost
	while((!Serial) && (millis()<10000));    // wait until serial monitor is open or timeout,

	new_millis = millis();


	Serial.println("DHCP Stress Test - 2017 Feb 25");
	Serial.printf("\r\n%u msec to start serial", new_millis);
	// Serial.print(millis());
	// Serial.println(" msec to start serial");

	char ID[32];
	sprintf(ID, "%08lX %08lX %08lX %08lX", SIM_UIDH, SIM_UIDMH, SIM_UIDML, SIM_UIDL);
	Serial.print("Teensy3 128-bit UniqueID: ");
	Serial.println(ID);

	//  pinMode(12, INPUT);   // help make sure MISO is input to Teensy

	delay(1000);


	Serial.print("MAC from Teensy: ");
	read_mac();
	print_mac();
	Serial.println();

	uint8_t tries=1;

	  // start the Ethernet connection, try 8 times
	do
		{
		Serial.print("Try ");
		Serial.print(tries);
		Serial.print(":");
		flag = ethernet_start(mac, true);	// 0 if failed
		Serial.print(flag);
		Serial.print(" ");
		}
	while ((tries++ < 5) && (flag == 0));

	if (0!=flag)
	{
		// Ethernet started OK
		Serial.print("Ethernet started after ");
	}
	else
	{
		Serial.print("Ethernet start failed even after ");
	}
	Serial.print(tries-1);	// loop already incremented it
	Serial.println(" attempts");

}	// end of setup

/**
 * Add up the four octets in the IP address.
 * The sum should never be 0 since 0.0.0.0 is not a routable client IP.
 */
uint16_t address_sum = 1;	// start with no error

void loop()
{

	/**
	 * Are we at a 1-second tick?
	 * This relates only to time count
	 */
	new_millis = millis();
	if (new_millis > (old_millis + 100UL))	// 100 msec or more has passed, so check for seconds tick
	{
		old_millis = new_millis;

		new_elapsed_seconds = new_millis/1000UL;
		if (new_elapsed_seconds > total_elapsed_seconds)
		{
			// seconds tick
			total_elapsed_seconds = new_elapsed_seconds;
			old_sec_millis = new_millis;
			seconds_tick = true;
		}
	}


	/**
	 * Do whatever needs to happen every second
	 * such as update other slower counters
	 */
	if (seconds_tick)
	{
		seconds_tick = false;	// we've used it up

		if (0 == (total_elapsed_seconds % 10))
		{
			seconds_ten_tick = true;
		}

		if (0 == (total_elapsed_seconds % 60))
		{
			minute_tick = true;
		}
	}

	/**
	 * Do 10-second items
	 */
	if (seconds_ten_tick)
	{
		seconds_ten_tick = false;	// we've used it up
		Serial.print("@");
		Serial.print(total_elapsed_seconds);
		Serial.print(" ");

		/**
		 * If last reported IP was all zeros, deal with that since that is an error
		 */
		if ( 0 == address_sum)
		{
			// most recent IP address is 0.0.0.0 which is bad. Now what?
			Serial.print (" Error! IP address: ");
			Serial.print (Ethernet.localIP());
			Serial.print(" Try restart:");
			flag = ethernet_start(mac, true);	// 0 if failed
			if (0 == flag)
			{
				restart_fail_count++;
			}
			else
			{
				restart_success_count++;
			}
			Serial.println(flag);
		}

		/**
		* try to renew DHCP, maintain() returns
		* 0: nothing happened
		* 1: renew failed
		* 2: renew success
		* 3: rebind fail
		* 4: rebind success
		*
		* @see https://www.arduino.cc/en/Reference/EthernetMaintain
		*/
		renew = Ethernet.maintain();
		// if returned 0, no action needed: carry on, but if nonzero track the actions
		if (0 != renew)
		{
			Serial.print("maintain()=");
			Serial.print(renew);
			Serial.print(" ");

			switch (renew)
			{
			case 1:		// renew failed
				renew_fail_count++;
				break;

			case 2:		// renew success
				renew_success_count++;
				break;

			case 3:		// rebind failed
				rebind_fail_count++;
				Serial.print("Rebind Failed! Try restsart:");
				flag = ethernet_start(mac, true);	// 0 if failed
				if (0 == flag)
				{
					restart_fail_count++;
				}
				else
				{
					restart_success_count++;
				}
				Serial.println(flag);
				break;

			case 4:		// rebind success
				rebind_success_count++;
				break;

			default:
				switch_default_error++;
				Serial.print("Error! Defaulted with renew of  ");
				Serial.print(renew);
			}

			Serial.print(" ");
			print_dhcp_summary();
			Serial.print(" ");
		} 	// end of renew test for != 0
		else
		{
			/**
			 * renew was zero, meaning Ethernet library reported nothing needs to be done.
			 */

		}

		// print local IP address:
		//  Serial.print("My IP address: ");
		//  Serial1.print('d'); // start of message to LCD must be 'd' char
		//  Serial1.print("IP:");
		address_sum = 0;
		for (byte thisByte = 0; thisByte < 4; thisByte++)
		{
			// print the value of each byte of the IP address:
			Serial.print(Ethernet.localIP()[thisByte], DEC);
			if (thisByte < 3) Serial.print(".");  // don't print trailing period
			address_sum += Ethernet.localIP()[thisByte];
		}

		Serial.println();

		/**
		 * No clue what data format of localIP() is at the "documentation page"
		 * https://www.arduino.cc/en/Reference/EthernetLocalIP
		 * It prints as 192.168.1.161 so is this a string? If it is a byte array,
		 * how does it know to print the period separators?
		 *
		 */

//		Serial.println(Ethernet.localIP());
//		Serial.println();

		if (minute_tick)
		{
			minute_tick = false;	// we've used it up
			print_dhcp_summary();
			Serial.println();
		}

	}		// end seconds ten  tick

}	// end loop

/**
 * Try to begin ethernet with mac value, which means using DHCP.
 *
 * For non-DHCP different constructor with GW, etc is used.
 * @param verbose output status if true
 * @see https://www.arduino.cc/en/Reference/Ethernet
 * @return 0 if failed, 1 if success
 */
int8_t ethernet_start(uint8_t mac[], boolean verbose)
{
	int8_t status = 0;	// 0 = failed
	time_start = millis();
	status = Ethernet.begin(mac);
	time_stop = millis();

	if (verbose)
	{
		if (0==status)
		{
			Serial.print("Fail DHCP after ");
		}
		else
		{
			Serial.print("OK DHCP after ");
		}
		Serial.print(time_stop-time_start);
		Serial.println(" msec");
	}
	return status;
}

/**
 * Renew and Rebind Fail/Success since startup
 *
 * Prints on one line with no CR/LF at end
 */
void print_dhcp_summary()
{
	Serial.print("Renew_F/S Bind_F/S Restart_F/S = ");
	Serial.print(renew_fail_count);
	Serial.print("/");
	Serial.print(renew_success_count);
	Serial.print(" ");
	Serial.print(rebind_fail_count);
	Serial.print("/");
	Serial.print(rebind_success_count);
	Serial.print(" ");
	Serial.print(restart_fail_count);
	Serial.print("/");
	Serial.print(restart_success_count);
}



