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

#define RES_TOUCH_CS_PIN  8     // resistive touch controller XPT2406 uses SPI
#define TFT_CS 20    // 10 is default, different on ethernet/touch combo
#define TFT_DC 21    // 9 is default, different on ethernet/touch combo

#define ETH_RST 9   // ethernet reset pin
#define ETH_CS  10  // ethernet chip select

#define SD_CS 4     // on PJRC WIZ8XX adapter, not on SALT

#define PERIPHERAL_RESET 22 // for ILI9341 and other peripherals


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 10);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(8080);



void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while((!Serial) && (millis()<10000));    // wait until serial monitor is open or timeout,

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


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    Ethernet.getSocketStatus(4);
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
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("Simple Server Teensy 3.2 and WIZ850io");
          client.println("<br>");
          client.print("millis=");
          client.println(millis());
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

