/*
  Temp Server

  Based on Arduino Ethernet>Webserver example:
  created 18 Dec 2009
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe
  modified 02 Sept 2015
  by Arturo Guadalupi

  2017 Jul 27 bboyes, rebuild with newly synched SPI library of PJRC
  Modified 2017 May 08 bboyes added output of temp to ILI9341 Color Touchscreen


 
 */

#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include <Ethernet2.h>
#include <TeensyID.h>
#include <Systronix_TMP102.h> // best version of I2C library is #included by the library. Don't include it here!

#define RES_TOUCH_CS_PIN  8     // resistive touch controller XPT2406 uses SPI
#define TFT_CS 20    // 10 is default, different on ethernet/touch combo
#define TFT_DC 21    // 9 is default, different on ethernet/touch combo

#define ETH_RST 9   // ethernet reset pin
#define ETH_CS  10  // ethernet chip select

#define SD_CS 4     // on PJRC WIZ8XX adapter, not on SALT

#define PERIPHERAL_RESET 22 // for ILI9341 and other peripherals

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

uint32_t seconds_without_client = 0;
uint32_t max_without_client = 0;

boolean verbose = true;
boolean silent = true;

boolean socket_status = true;
uint8_t inbyte = 0;

uint16_t rawtemp;

float temp = 0.0;

//Systronix_TMP102 tmp102_48(0x48);    // We can pass constructor a value
Systronix_TMP102 tmp102_48;    // We can pass constructor a value
uint16_t configOptions;


// MOSI=11, MISO=12, SCK=13
XPT2046_Touchscreen ts(RES_TOUCH_CS_PIN);
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

int8_t stat = -1;

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
   * This is Ethernet CS and SD CS
   */
  pinMode(SD_CS, INPUT_PULLUP);
  pinMode(ETH_CS, INPUT_PULLUP);

  pinMode (RES_TOUCH_CS_PIN, INPUT_PULLUP);  // resistive touch controller

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

  // reset peripherals
  pinMode(PERIPHERAL_RESET, OUTPUT);
  digitalWrite(PERIPHERAL_RESET, LOW);
  delay(1);
  digitalWrite(PERIPHERAL_RESET, HIGH);
  delay(100);

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_GREEN);
  ts.begin();

  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  // Wait here for up to 10 seconds to see if we will use Serial Monitor, so output is not lost
  while((!Serial) && (millis()<10000));    // wait until serial monitor is open or timeout,

  new_millis = millis();
  Serial.println("Teensy Temperature Server");

  Serial.printf("Build %s %s\r\n", __TIME__, __DATE__);

  Serial.printf("%u msec to start serial\r\n", new_millis);

  kinetisUID(uid);
  Serial.printf("Teensy3 128-bit UniqueID int array: %08X-%08X-%08X-%08X\n", uid[0], uid[1], uid[2], uid[3]);

  //  pinMode(12, INPUT);   // help make sure MISO is input to Teensy

  teensy_usb_sernum = teensyUsbSN();
  Serial.printf("USB Serialnumber: %u \n", teensyUsbSN());

  teensyMAC(t_mac);
  Serial.printf("Teensy MAC Address: %02X:%02X:%02X:%02X:%02X:%02X \n", t_mac[0], t_mac[1], t_mac[2], t_mac[3], t_mac[4], t_mac[5]);

  // start the Ethernet connection and the server:
  Ethernet.begin(t_mac, ip);

  Serial.print("Server at ");
  Serial.println(Ethernet.localIP());
  
  printSocketStatus(4);
  Serial.println("Start listening:");
    // start listening for clients
  server.begin();  
  printSocketStatus(4);

  // start TMP102 library
  tmp102_48.setup(0x48);
  tmp102_48.begin();
  
  Serial.printf("TMP102 Sensor at 0x%02X\r\n", tmp102_48.base_get());

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
  stat = tmp102_48.register_write(TMP102_CONF_REG_PTR, configOptions);
  if (SUCCESS != stat) Serial.print (" writeReg error! ");  

  // leave the pointer set to read temperature
  stat = tmp102_48.pointer_write(TMP102_TEMP_REG_PTR);  

  Serial.println();

  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setFont(Arial_40);
  tft.setCursor(5, 20);
  tft.print("TempServer");

  Serial.printf("Setup Complete!\nSend V/v to toggle verbose, h/H to toggle hush/silent, s/S socket status\n");

  delay(2000);

}

uint8_t update = 5;

boolean wastouched = true;
uint16_t xmax, xmin=4095, ymax, ymin=4095, zmax, zmin=4095;
uint16_t xnow, ynow, znow;
uint32_t touch_start, touch_total, touch_secs;  // in millis unless _secs

uint8_t outcount = 0;

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
        seconds_without_client++; // increment, it will be cleared if there is a client
        if (seconds_without_client > max_without_client) max_without_client = seconds_without_client;
        Serial.print(".");

        // read the temperature to have it ready for any clients
        configOptions |= TMP102_CFG_OS;        // start One Shot conversion
        stat = tmp102_48.register_write (TMP102_CONF_REG_PTR, configOptions);

        // pointer set to read temperature
        stat = tmp102_48.pointer_write(TMP102_TEMP_REG_PTR);     
        // read two bytes of temperature
        stat = tmp102_48.register_read (&rawtemp);
        temp = tmp102_48.raw13ToC(rawtemp);

        if (0 == (total_elapsed_seconds % 10))
        {
            seconds_ten_tick = true;
        }

        if (0 == (total_elapsed_seconds % 60))
        {
            minute_tick = true;
        }

      // wipe to black the part of screen with changing values
      // note: for 48 pt font, Y span of 48 leaves one pixel not cleared...
      tft.fillRect(5, 15, 319, 60, ILI9341_BLACK);    
      tft.setTextColor(ILI9341_YELLOW);
      tft.setFont(Arial_48);
      tft.setCursor(80, 20);
      tft.print(temp);    
    }

  /**
  * Get any serial input from user
  */

  if (Serial.available()>0)
  {
    inbyte = Serial.read();
    switch (inbyte)
    {

    case 's':
    case 'S':
      // detailed socket status when we get a new client connection
      socket_status = !socket_status;
      Serial.printf("\r\nSocket Status: %s ", socket_status ? "true" : "false");
      break;

    case 'v':
    case 'V':
      verbose = !verbose;
      if (verbose) silent = false;
      Serial.printf("\r\nverbose: %s ", verbose ? "true" : "false");
      break;

    case 'h':
    case 'H':
      // hush mode
      silent = !silent;
      if (silent) verbose = false;  // can't have silent and verbose
      Serial.printf("\r\nsilent: %s ", silent ? "true" : "false");
      break;      

    default:
      break;  
    }
  }    


    // listen for incoming clients
    EthernetClient client = server.available();
    if (client) 
    {
        Serial.printf("@ %u sec, Got new client, Temp is %.3f C\r\n", new_elapsed_seconds, temp);
        Serial.print("From ");
        Serial.print(client.remoteIP());
        Serial.printf(", port %u\r\n", client.remotePort());
        //Serial.printf("From %u and %u\r\n", client.remoteIP(), client.remotePort());
        if (socket_status) printSocketStatus(8);

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
                if (verbose) Serial.write(c);   // echo incoming request to serial monitor

                // if you've gotten to the end of the line (received a newline
                // character) and the line is blank, the http request has ended,
                // so you can send a reply
                // if (c == '\n') Serial.println ("newline");
                if (c == '\n' && currentLineIsBlank) 
                {
                    if (verbose) Serial.println("Request is complete");
                    // we could be here if we get a request consisting of one blank line, in theory
                    // send a standard http response header
                    if (verbose) Serial.println("Sending Response...");
                    http_request_count++;

                    //if (socket_status) printSocketStatus(8);

                    outcount = client.println("HTTP/1.1 200 OK");
                    if (!outcount) Serial.println("Could not print to client");
                    outcount = client.println("Content-Type: text/html; charset=UTF-8");
                    if (!outcount) Serial.println("Could not print to client");
                    outcount = client.println("Connection: close");  // the connection will be closed after completion of the response
                    if (!outcount) Serial.println("Could not print to client");
                    outcount = client.print("Refresh: ");        // changing this to a print vs println breaks it
                    if (!outcount) Serial.println("Could not print to client");
                    client.println(update);  // refresh the page automatically every X sec
                    client.println("<meta name=\"robots\" content=\"noindex\" />");
                    client.println(); // blank line must be here to separate HTTP request response from html which follows
                    //outcount = client.println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">");
                    //outcount = client.println("<!DOCTYPE html>");
                    // http://www.htmlhelp.com/tools/validator/doctype.html
                    // <!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML//EN">   // declares for HTML 2.0
                    outcount = client.println("<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">");
                    if (!outcount) Serial.println("Could not print to client");  else if (verbose) Serial.printf ("Sent %u\n", outcount);
                    outcount = client.println("<html>");
                    if (!outcount) Serial.println("Could not print to client");
                    outcount = client.println("<head>");
                    outcount = client.println("<title>Simple Temperature Server</title>");
                    outcount = client.println("</head>");
                    if (verbose) Serial.println("Sent head");
                    outcount = client.println("<body>");

                    outcount = client.println("<h2>SALT TMP102 Temperature Server</h2>");
                    if (!outcount) Serial.println("Could not print to client");
                    // Serial.printf("Build %s %s\r\n", __TIME__, __DATE__);
                    client.print("Build ");
                    client.print(__TIME__);
                    client.print(" ");
                    client.print(__DATE__);
                    client.print("<br>");
                    if (verbose) Serial.println("Sent body header and build");
                    client.print("Updates approx every ");
                    client.print(update);
                    client.print(" seconds<br>");
                    client.print("@");
                    client.print(new_elapsed_seconds);
                    client.print(" sec: ");
                    client.print(temp, 2);
                    client.print(" deg C <br>");
                    if (verbose) Serial.println("Sent temperature");
                    client.print(" You: ");
                    client.print(client.remoteIP());
                    client.print(", port ");
                    client.print(client.remotePort());
                    client.print("<br>");
                    client.print(http_request_count);
                    client.print(" http requests, ");
                    client.print((float)http_request_count/(float)new_elapsed_seconds);
                    client.print(" per sec. ");
                    client.print(timeout_http_count);
                    client.print(" timeouts, ");
                    client.print(max_without_client);
                    client.print(" max sec w/o client");
                    client.print("<br>");
                    client.println("</body>");
                    if (verbose) Serial.println("Sent all of body");
                    client.println("</html>");
                    client.println();

                    Serial.println("    ----");
                    
                    seconds_without_client = 0; // reset to zero
                    break;    // out of the while client.connected ??? Is this really correct?
                }   // end of responding to complete request
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
            }   // end of if client.available
            else
            {
                // client connected but nothing available, don't wait forever!
                // 1000 msec seems like a good timeout
                Serial.print("!");
                if (millis() > (start_millis + 1000UL))
                {
                    // waited too long for finish of request
                    Serial.println("Error! Break out of waiting for request to finish");
                    timeout_http_count++;
                    break;  // get out of while
                }
            }
        }   // end of while client.connected

        // client no longer connected, or request was ended
        // give the web browser time to receive the data
        delay(1);    // 1 msec seemed not enough, make it 10? 
        // Serial.println("Will stop client");
        // Serial.println("Out of while...");
        // close the connection:
        client.stop();
        if (verbose) Serial.println("client stopped");
        // // These serial.printf cause SPI to WIZnet 850io to halt in Ard1.8.1/TD1.35 or temp never printed in Ard1.8.2/TD1.36!!
        // Serial.printf("Temp %f C\r\n", temp);
        // Serial.printf("Timeout count=%u\r\n", timeout_http_count);
        // Serial.flush();
        if (socket_status) printSocketStatus(8);

        if (verbose) Serial.printf("%u http requests, %.2f per sec, %u timeouts\r\n", 
          http_request_count, (float)http_request_count/(float)new_elapsed_seconds, timeout_http_count);

        if (verbose) Serial.printf("%u sec max w/o client\r\n", max_without_client);
        Serial.printf("--------\r\n\n");


    }   // end of if-client
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



