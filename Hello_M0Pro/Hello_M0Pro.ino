/**
 * Hello World for Arduino M0 Pro board
 *
 * https://github.com/systronix   bboyes@systronix.com
 */

/**
 * Revisions
 *
 * 2016 Sep 28	bboyes	Created to see if I could get anything to program on the M0 Pro board. Answer: only if I used Arduino.org 1.7.11 not Arduino.cc 1.6.11 IDE
 *
 *
 */


#include <SPI.h>



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


void setup() {

	/*
	 * When using with PJRC wiz820 sd adapter
	 * https://www.pjrc.com/store/wiz820_sd_adaptor.html [sic]
	 * Some SD cards can be sensitive to SPI activity while the Ethernet library is initialized before the SD library.
	 * For best compatiblity with all SD cards, these 3 lines are recommended at the beginning of setup().
	 * Pins 4 and 10 will be reconfigured as outputs by the SD and Ethernet libraries. Making them input
	 * pullup mode before initialization guarantees neither device can respond to unintentional signals
	 * while the other is initialized.
	 * This code is left from the Ethernet-enabled program on which it is based
	 */
	pinMode(4, INPUT_PULLUP);
	pinMode(10, INPUT_PULLUP);
	delay(1);  // allow time for both pins to reach 3.3V

	// Open serial communications and wait for port to open:
	Serial.begin(115200);

	//  Serial1.begin(9600);  // TX1, RX1 on Teensy pins 3 and 2, not the USB serial output!

	// Wait here for up to 10 seconds to see if we will use Serial Monitor, so output is not lost
	while((!Serial) && (millis()<10000));    // wait until serial monitor is open or timeout,
	Serial.print(millis());
	Serial.println(" msec to start serial");

	Serial.println("Hello M0 Pro - 2016 Oct 28");

	//  pinMode(12, INPUT);   // help make sure MISO is input to Teensy

	delay(1000);


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

		Serial.println();


	}		// end seconds ten  tick

}	// end loop





