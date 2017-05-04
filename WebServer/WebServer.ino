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

uint8_t update = 5;
char log_message[128];

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  // Wait here for up to 10 seconds to see if we will use Serial Monitor, so output is not lost
  while((!Serial) && (millis()<10000));    // wait until serial monitor is open or timeout,

  strcpy (log_message, "Build: ");
  strcat (log_message, __TIME__);
  strcat (log_message, " MDT, ");
  strcat (log_message, __DATE__);  
  strcat (log_message, 0x00);

  Serial.println("Simple Webserver Example");

  Serial.println(log_message);

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
          client.print("Refresh: ");  // refresh the page automatically every XX sec
          client.println(update);
          client.println();   // must have this blank line or browser won't display anything!
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");


            client.print("Simple Webserver Test <br />");
            client.println("<br />");
            client.println(log_message);
            client.println("<br />");
            client.print("Updates approx every ");
            client.print(update);
            client.println(" seconds<br />");
            client.print("msec: ");
            client.print(millis());
            client.println("<br />");

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
    Serial.printf("A serial printf at %u millis\r\n", millis());
    Serial.printf("Another printf with just text\r\n");
  }
}

