/*
  Simple Habitat Client Test

  Based on SALT TempServer test program, which is
  based on Arduino Ethernet>Webserver example:
  created 18 Dec 2009
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe
  modified 02 Sept 2015
  by Arturo Guadalupi

  2017 Aug 06 bboyes, using Ethernet2, test server API
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
char t_mac_str[18];    // A formatted string in hex xx:xx:xx:xx:xx:xx = 17 + null term

uint32_t teensy_usb_sernum;
uint32_t uid[4];

IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
//IPAddress server_ip(192,168,1,254);    // Yoga S1 at home office
//IPAddress server_ip(192,168,1,194);    // Win7 desktop office
IPAddress server_ip(50,116,0,218);  // Julio virtual at slashome

//uint8_t server_port = 105;    // server is listening on this port
uint16_t server_port = 8081;     // Julio virtual at slashome

IPAddress client_ip(192,168,1,150);

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

// Initialize the Ethernet client library
// with the IP address and port you want to use
EthernetClient client;

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
  Serial.println("Habitat Client Test");

  Serial.printf("Build %s %s\r\n", __TIME__, __DATE__);

  Serial.printf("%u msec to start serial\r\n", new_millis);

  kinetisUID(uid);
  Serial.printf("Teensy3 128-bit UniqueID int array: %08X-%08X-%08X-%08X\n", uid[0], uid[1], uid[2], uid[3]);

  //  pinMode(12, INPUT);   // help make sure MISO is input to Teensy

  teensy_usb_sernum = teensyUsbSN();
  Serial.printf("USB Serialnumber: %u \n", teensyUsbSN());

  teensyMAC(t_mac);
  Serial.printf("Teensy MAC Address: %02X:%02X:%02X:%02X:%02X:%02X \n", t_mac[0], t_mac[1], t_mac[2], t_mac[3], t_mac[4], t_mac[5]);

  // start the Ethernet connection
  Ethernet.begin(t_mac, client_ip);

  Serial.print("Client at ");
  Serial.println(Ethernet.localIP());
  
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

  Serial.print("Try to connect to server at ");
  Serial.print(server_ip);
  Serial.printf(":%u\r\n", server_port);

  if (client.connect(server_ip, server_port)) 
    {
        Serial.printf("@ %u sec, connected to server, Temp is %.3f C\r\n", new_elapsed_seconds, temp);
        Serial.print("at ");
        Serial.print(client.remoteIP());
        Serial.printf(":%u\r\n", client.remotePort());
        if (socket_status) printSocketStatus(4);

        start_millis = new_millis;  // for timeout check
        // Serial.printf("new client at %u sec\r\n", new_elapsed_seconds);

        // Make a HTTP request:
        client.println("GET /api/v1/time");
        client.println("X-NAP-Habitat-ID: ");
        client.println(teensyMAC());
        client.println("Connection: close");        // actually we want to keep it open
        client.println();
    }
    else
    {
      Serial.printf("could not connect to server at ");
      Serial.print(client.remoteIP());
      Serial.printf(", port %u\r\n", client.remotePort());

      if (socket_status) printSocketStatus(4);
    }

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
        // Serial.print(".");

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

  delay(50);

    while (client.available()) 
      {
        char c = client.read();
        Serial.print(c);
      }

    // if the server's disconnected, stop the client:
    if (!client.connected()) 
    {
      Serial.println();
      Serial.println("disconnecting.");
      client.stop();

      while(true);  // connection closed, can't go on.

    }

      // if (seconds_ten_tick)
      // {
      //   seconds_ten_tick = false; // we've used it up
      //   Serial.print("'");
      // } 
      // if (minute_tick)
      // {
      //   minute_tick = false;  // we've used it up
      //   Serial.println();     // keep periods from piling up on one line
      // }  
    

}



