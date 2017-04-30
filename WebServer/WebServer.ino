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

uint8_t t_mac[6]; // hold internal MAC from Teensy 

uint32_t teensy_usb_sernum;
uint32_t uid[4];

IPAddress ip(192, 168, 1, 10);
uint8_t gateway[] = {192, 168, 1, 1};
uint8_t subnet[] = {255, 255, 255, 0};

uint32_t new_millis = 0;
uint32_t old_millis = 0;  // millis saved every tiem through loop, if new > old
uint32_t old_sec_millis;  // millis saved every second tick

uint16_t rawtemp;

float temp = 0.0;

//Systronix_TMP102 tmp102_48(0x48);    // We can pass constructor a value
Systronix_TMP102 tmp102_48;    // We can pass constructor a value
uint16_t configOptions;

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
   */
  pinMode(4, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode (CS_PIN, INPUT_PULLUP);  // disable resistive touch controller

  pinMode (TFT_CS, INPUT_PULLUP);    // disable LCD display
  pinMode (TFT_DC, INPUT_PULLUP);    // 

  delay(1);  // allow time for pins to reach 3.3V  

  // Wait here for up to 10 seconds to see if we will use Serial Monitor, so output is not lost
  while((!Serial) && (millis()<10000));    // wait until serial monitor is open or timeout,

  new_millis = millis();
  Serial.println("Teensy Web Server");

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
  Ethernet.begin(t_mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  // start TMP102 library
  tmp102_48.setup(0x48);
  tmp102_48.begin();
  
  Serial.print("TMP102 Sensor at 0x");
  Serial.println(tmp102_48.BaseAddr, HEX);

  // start with default config
  Serial.print ("SetCFG=");
  Serial.print (TMP102_CFG_DEFAULT_WR, HEX);
  Serial.print (" ");
//  stat = tmp102_48.writeRegister(TMP102_CONF_REG_PTR, TMP102_CFG_DEFAULT_WR);
  stat = tmp102_48.init(TMP102_CFG_DEFAULT_WR);
//  if ( 0!= stat) Serial.print (" writeReg error! ");
  if (SUCCESS != stat) Serial.print (" writeReg error! ");  

  configOptions = 0x0;  // 
  configOptions |= TMP102_CFG_EM;  // set Extended Mode
  configOptions |= TMP102_CFG_RATE_1HZ;  // 1Hz conversion
  configOptions |= TMP102_CFG_SD;        // sleep between conversions
  
  Serial.print ("SetCFG=");
  Serial.print (configOptions, HEX);
  Serial.print (" ");
  stat = tmp102_48.writeRegister(TMP102_CONF_REG_PTR, configOptions);
  if (SUCCESS != stat) Serial.print (" writeReg error! ");  

  // leave the pointer set to read temperature
  stat = tmp102_48.writePointer(TMP102_TEMP_REG_PTR);  
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");

    configOptions |= TMP102_CFG_OS;        // start One Shot conversion
    stat = tmp102_48.writeRegister (TMP102_CONF_REG_PTR, configOptions);

    // pointer set to read temperature
    stat = tmp102_48.writePointer(TMP102_TEMP_REG_PTR);     
    // read two bytes of temperature
    stat = tmp102_48.readRegister (&rawtemp);
    temp = tmp102_48.raw13ToC(rawtemp);

    uint8_t update = 10;


    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.print("Refresh: ");
          client.println(update);  // refresh the page automatically every X sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");


          client.print("<b>SALT 2.1</b> - Updates approx every ");
          client.print(update);
          client.print(" seconds<br />");
          client.print("@");
          client.print(millis()/1000);
          client.println(" sec<br />");
          client.print("Ambient Temp is ");
          client.print(temp, 2);
          client.println(" deg C <br />");

          // // output the value of each analog input pin
          // for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
          //   int sensorReading = analogRead(analogChannel);
          //   client.print("analog input ");
          //   client.print(analogChannel);
          //   client.print(" is ");
          //   client.print(sensorReading);
          //   client.println("<br />");
          // }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

