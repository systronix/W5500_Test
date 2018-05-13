

//---------------------------< I N C L U D E S >--------------------------------------------------------------

#include	<SPI.h>
#include	<SdFat.h>
#include	<i2c_t3.h>			// MUST be included before DS1307RTC; something about how RTC starts up causes
#include	<DS1307RTC.h>		// a hang somewhere - DS1307RTC::DS1307RTC() called too early?

SdFat sd;

#define		uSD_DETECT	16
#define		uSD_CS_PIN	15


//---------------------------< u S D _ L O G _ E V E N T >----------------------------------------------------
//
// This function is derived from the same-name function in SALT_logging.cpp.  This function does not convert
// UTC time to local time; log folders and log files are differently named to distinguish them from SALT logs
//
// Makes a file name from the tm (UTC) time struct and then attempts to open that file.  If the file does
// not exist, a new file of that name is created.  Creates an ISO 8601 timestamp from the tm time struct.
// Time stamp and event string are concatenated and appended to the log file.  log file then closed.
//
// uSD card is initialized before every logging event because the card may have been removed after the previous
// log event.  uSD card initialization is performed at a 250kHz SCK so there will be a burst of 250kHz SCK before
// log information is actually written at speed.
//

char* usd_months [13] ={(char*)"nil", (char*)"Jan", (char*)"Feb", (char*)"Mar", (char*)"Apr", (char*)"May",
					(char*)"Jun", (char*)"Jul", (char*)"Aug", (char*)"Sep", (char*)"Oct", (char*)"Nov", (char*)"Dec"};
void uSD_log_event (char* event_str)
	{
	File			log_file;
	char			filename [64];
	char			path [20];

	time_t			timestamp;				// UTC unix time stamp; used for logging
	tmElements_t	tm;						// UTC; complete date-time information from the DS3231; note: year is a uint8_t offset from 1970 (for 2017, tm.Year is 47)

	if (digitalRead (uSD_DETECT))
		{
		Serial.printf ("uSD logger: uSD not present\n");
//		e7n.exception_add (E7N_USD_MISSING_IDX);
		return;
		}

	RTC.get_time (tm, timestamp);	// get current time; can't log without current time

														// create a path from current local date
	sprintf (path, "/xlogs/%4d/%s/",  1970+tm.Year, usd_months[tm.Month]);
														// create a filename from current local date
	sprintf (filename, "xlog_%4d-%02d-%02d.txt",1970+tm.Year, tm.Month, tm.Day);

	if (!sd.begin(uSD_CS_PIN, SPI_FULL_SPEED))			// always initialize because card may have been removed
		{
		Serial.printf ("\r\nerror initializing uSD; cs: %d; full-speed mode\r\n", uSD_CS_PIN);
		return;
		}

	boolean made = false;
	if (!sd.chdir (path, false))						// attempt to change to path folder; 
		{
		Serial.printf ("making directory: %s\n", path);
		made = sd.mkdir (path, true);					// can't change? attempt to make a directory with missing parent directories

		if (made)
			{
			Serial.printf ("made directory: %s\n", path);
			sd.chdir (path, false);
			}
		else
			{
			Serial.printf ("could not make directory: %s\n", path);
			return;
			}
		}

	Serial.printf ("%s%s\n", path, filename);

	log_file = sd.open(filename, FILE_WRITE);			// open the file in write mode

	if (log_file)										// if the file opened
		{
		Serial.printf ("Writing to %s...\n", filename);	
		log_file.printf("%4d-%02d-%02dT%02d:%02d:%02d, %s\n",	// write the event string 
			1970+tm.Year,
			tm.Month,
			tm.Day,
			tm.Hour,
			tm.Minute,
			tm.Second,
			event_str);

		log_file.timestamp (T_WRITE,					// set the file's timestamp
			1970+tm.Year,
			tm.Month,
			tm.Day,
			tm.Hour,
			tm.Minute,
			tm.Second);

		log_file.close();								// and close the file
		Serial.printf ("done.\n");
		}
	else
		Serial.printf ("error opening %s\n", filename);	// file did not open
	}


//---------------------------< S E T U P >--------------------------------------------------------------------
//
//
//

void setup (void)
	{
	pinMode(9, OUTPUT);						// ETH_RST(L)
	pinMode(22, OUTPUT);					// PERIF_RST(L)
	digitalWrite(9, LOW);					// resets asserted
	digitalWrite(22, LOW);
	
	Serial.begin(115200);						// usb; could be any value
	while((!Serial) && (millis()<10000));		// wait until serial monitor is open or timeout
	Serial.printf ("uSD_log.ino\n");

	pinMode (6, INPUT_PULLUP);				// SALT FLASH_CS(L)
	pinMode (8, INPUT_PULLUP);				// SALT T_CS(L)
	pinMode (10, INPUT_PULLUP);				// SALT ETH_CS(L)
	pinMode (20, INPUT_PULLUP);				// SALT DISP_CS(L)
	
	pinMode (uSD_DETECT, INPUT_PULLUP);		// so we know that uSD is in the socket

	digitalWrite(9, HIGH);					// resets released
	digitalWrite(22, HIGH);

	uSD_log_event ((char*)"test string");
	}


//---------------------------< L O O P >----------------------------------------------------------------------
//
//
//

void loop (void)
	{
	}