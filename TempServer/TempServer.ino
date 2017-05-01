/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi
 
 */

#include <SPI.h>
#include <Ethernet.h>
#include <TeensyID.h>
#include <Systronix_TMP102.h> // best version of I2C library is #included by the library. Don't include it here!

#define CS_PIN  8   // resistive touch controller XPT2406 uses SPI
#define TFT_CS 20    // 10 is default, different on ethernet/touch combo
#define TFT_DC 21    // 9 is default, different on ethernet/touch combo

#define ETH_RST 9 // ethernet reset pin

uint8_t t_mac[6]; // hold internal MAC from Teensy 

uint32_t teensy_usb_sernum;
uint32_t uid[4];

IPAddress ip(192, 168, 1, 10);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

uint32_t new_millis = 0;
uint32_t old_millis = 0;  // millis saved every tiem through loop, if new > old
uint32_t old_sec_millis;  // millis saved every second tick

uint32_t start_millis = 0;  // start of HTTP listen and respond
uint32_t timeout_http_count = 0;
uint32_t http_request_count = 0;

uint32_t new_elapsed_seconds = 0;
uint32_t total_elapsed_seconds = 0;
boolean seconds_tick = false;

uint8_t seconds_five=0;
boolean seconds_five_tick = false;
boolean seconds_ten_tick = false;
boolean minute_tick = false;

uint16_t rawtemp;

float temp = 0.0;

//Systronix_TMP102 tmp102_48(0x48);    // We can pass constructor a value
Systronix_TMP102 tmp102_48;    // We can pass constructor a value
uint16_t configOptions;

int8_t stat = -1;

char log_message[128];



// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(8080);

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

  pinMode(TFT_CS, INPUT_PULLUP);    // disable LCD display
  pinMode(TFT_DC, INPUT_PULLUP);    // 

  pinMode(ETH_RST, INPUT_PULLUP);  // ethernet reset pin
  delay(1);  // allow time for pins to reach 3.3V

  // reset Ethernet
  pinMode(ETH_RST, OUTPUT);       // this causes low output anyway...
  digitalWrite(ETH_RST, LOW);     // ...so just do the reset Ethernet
  delay(1);
  digitalWrite(ETH_RST, HIGH);
  delay(10);                      // recover from reset
 
  strcpy (log_message, "Build time: ");
  strcat (log_message, __TIME__);
  strcat (log_message, " ");
  strcat (log_message, __DATE__);  
  // strcat (log_message, 0x00);

  // Wait here for up to 10 seconds to see if we will use Serial Monitor, so output is not lost
  while((!Serial) && (millis()<10000));    // wait until serial monitor is open or timeout,

  new_millis = millis();
  Serial.println("Teensy Web Server");

  Serial.printf("Build %s %s\r\n", __TIME__, __DATE__);
  Serial.println(log_message);

  Serial.printf("%u msec to start serial\r\n", new_millis);

  char ID[32];
  sprintf(ID, "%08lX %08lX %08lX %08lX", SIM_UIDH, SIM_UIDMH, SIM_UIDML, SIM_UIDL);
  Serial.print("Teensy3 128-bit UniqueID char array: ");
  Serial.println(ID);

  kinetisUID(uid);
  Serial.printf("Teensy3 128-bit UniqueID int array: %08X-%08X-%08X-%08X\n", uid[0], uid[1], uid[2], uid[3]);

  //  pinMode(12, INPUT);   // help make sure MISO is input to Teensy

  teensy_usb_sernum = teensyUsbSN();
  Serial.printf("USB Serialnumber: %u \n", teensyUsbSN());

  teensyMAC(t_mac);
  Serial.printf("Teensy MAC Address: %02X:%02X:%02X:%02X:%02X:%02X \n", t_mac[0], t_mac[1], t_mac[2], t_mac[3], t_mac[4], t_mac[5]);

  // start the Ethernet connection and the server:
  Ethernet.begin(t_mac, ip);

  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  // start TMP102 library
  tmp102_48.setup(0x48);
  tmp102_48.begin();
  
  Serial.print("TMP102 Sensor at 0x");
  Serial.println(tmp102_48.BaseAddr, HEX);

  // start with default config
  Serial.print ("SetCFG=0x");
  Serial.print (TMP102_CFG_DEFAULT_WR, HEX);
  Serial.print (" ");
//  stat = tmp102_48.writeRegister(TMP102_CONF_REG_PTR, TMP102_CFG_DEFAULT_WR);
  stat = tmp102_48.init(TMP102_CFG_DEFAULT_WR);
//  if ( 0!= stat) Serial.print (" writeReg error! ");
  if (SUCCESS != stat) Serial.print (" writeReg error! ");  

  configOptions = 0x0;  // 
  configOptions |= TMP102_CFG_EM;         // set Extended Mode
  configOptions |= TMP102_CFG_RATE_1HZ;  // 1Hz conversion
  configOptions |= TMP102_CFG_SD;        // sleep between conversions
  
  Serial.print ("SetCFG=0x");
  Serial.print (configOptions, HEX);
  Serial.print (" ");
  stat = tmp102_48.writeRegister(TMP102_CONF_REG_PTR, configOptions);
  if (SUCCESS != stat) Serial.print (" writeReg error! ");  

  // leave the pointer set to read temperature
  stat = tmp102_48.writePointer(TMP102_TEMP_REG_PTR);  

  Serial.println();
}

uint8_t update = 10;

void loop() 
{

  /**
   * Are we at a 1-second tick?
   * This relates only to time count
   */
  new_millis = millis();
  if (new_millis > (old_millis + 100UL))  // 100 msec or more has passed, so check for seconds tick
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
    seconds_tick = false; // we've used it up
    Serial.print(".");

    // read the temperature to have it ready for any clients
    configOptions |= TMP102_CFG_OS;        // start One Shot conversion
    stat = tmp102_48.writeRegister (TMP102_CONF_REG_PTR, configOptions);

    // pointer set to read temperature
    stat = tmp102_48.writePointer(TMP102_TEMP_REG_PTR);     
    // read two bytes of temperature
    stat = tmp102_48.readRegister (&rawtemp);
    temp = tmp102_48.raw13ToC(rawtemp);

    if (0 == (total_elapsed_seconds % 10))
    {
      seconds_ten_tick = true;
    }

    if (0 == (total_elapsed_seconds % 60))
    {
      minute_tick = true;
    }
  }


  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) 
  {
    start_millis = new_millis;  // for timeout check
    // Serial.printf("new client at %u sec\r\n", new_elapsed_seconds);

    // an http request ends with a blank line
    boolean currentLineIsBlank = true;

    // seems like this while could last forever as long as client is connected 
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) 
        {
          // we could be here if we get a request consisting of one blank line, in theory
          // send a standard http response header
          Serial.print("Sending Response...");

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 10");        // changing this to a print vs println breaks it
          // client.println(update);  // refresh the page automatically every X sec
          client.println();
          // client.print("<meta name=\"robots\" content=\"noindex\" />");
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

            client.println("<b>SALT 2.1 TMP102 Temperature Server</b> <br />");
            client.print(log_message);
            client.println("<br />");
            client.print("Updates approx every ");
            client.print(update);
            client.println(" seconds<br />");
            client.print("@");
            client.print(new_elapsed_seconds);
            client.println(" sec<br />");
            client.print("Ambient Temp is ");
            client.print(temp, 2);
            client.println(" deg C <br />");
            client.print("Served ");
            client.print(http_request_count);
            client.print(" http requests, ");
            client.print(timeout_http_count);
            client.println(" timeouts");
            client.println("<br />");

          client.println("</html>");

          Serial.println("done");
          http_request_count++;
          break;    // out of the while
        }
        if (c == '\n') 
        {
          // So we are here upon receipt of every newline char if current line is NOT blank
          // you're starting a new line
          currentLineIsBlank = true;
          // Serial.println("Got a newline");
        } 
        else if (c != '\r') 
        {
          // here if char was not a newline and not a carriage return
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
      else
      {
        // client connected but nothing available, don't wait forever!
        Serial.print("!");
        if (millis() > (start_millis + 1000UL))
        {
          // waited too long for finish of request
          Serial.println("Error! Break out of waiting for request to finish");
          timeout_http_count++;
          break;  // get out of while
        }
      }
    }   // end of while

    // client no longer connected, or request was ended
    // give the web browser time to receive the data
    delay(1);    // 1 msec seemed not enough, make it 10 -bboyes
    // Serial.println("Will stop client");
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
    // These serial.printf cause SPI to WIZnet 850io to halt!!
    // Serial.printf("Temp %f C\r\n", temp);
    // Serial.printf("Timeout count=%u\r\n", timeout_http_count);
    Serial.print("Temp is ");
    Serial.print(temp,4);
    Serial.print("C, Timeout count=");
    Serial.print(timeout_http_count);
    Serial.print(", ");
    Serial.print(http_request_count);
    Serial.println(" http requests served");
    Serial.println();
  }
  else
  {
    // no client exists this time through loop
    if (seconds_ten_tick)
    {
      seconds_ten_tick = false; // we've used it up
      Serial.print("'");
    } 
    if (minute_tick)
    {
      minute_tick = false;  // we've used it up
      Serial.println();     // keep periods from piling up on one line
    }  
  }
}

