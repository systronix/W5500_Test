/**
ILI9341 Test

PJRC's example of using XPT2046 touchscreen controller 
on the common LCD boards TJCTM24028-SPI which are 
320x240 touchscreens using the ILI9341 controller 
chip, with SPI interface

Function:
Report X, Y, and Z (pressure) of a touch to the USB serial port
and display the data on the LCD screen.

TJCTM24028-SPI are available for under $10 on eBay. 
PJRC sells tested
copies of this screen and also designed a purple dev
board which plugs a Teensy 3.2 or 3.1 into the screen.

The dev boards are at OSHPark:
https://www.oshpark.com/shared_projects/TG395I75
but there's no BOM so refer to the older version.

PJRC forum for this display at the not-well-named topic
https://forum.pjrc.com/threads/30559-2-8-ILI9341-restive-touch-miso-not-connected

Some important notes:
The XPT2046 library assumes the upper left corner of the screen is 0,0
when the strip of header pins is on the right and the SD card slot
is towards you. Logical enough.

The ILI9341 library does not make the same assumption unless
you use setRotation(1). Practically, what this means is
that all the Adafruit examples will appear to have their
X and Y swapped.
**/

/**
Revisions:
2017 May 08 bboyes  SALT boards have a peripheral reset on Teensy P22. The PJRC adapter board
  ties display reset to 3.3V. Added control of this pin as PERIPHERAL_RESET
2016 Jan 15 bboyes  Change TFT_CS and TFT_DC pins in attempt to use ILI9341 touchscreen with 
WIZ820io Ethernet adapter.
2015 Nov 14  bboyes  Bringing up custom board DemoB with backlight PWM, laser control
2015 Nov 03  bboyes  Added output to screen and serial port of pressure.
This is the example program provided by PRJC with their XPT2046_Touchscreen
library (available on github).

**/

#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <XPT2046_Touchscreen.h>
//#include <SPI.h>

#define CS_PIN  8   // resistive touch controller XPT2406 uses SPI

#define TFT_CS 20    // 10 is default, different on ethernet/touch combo
#define TFT_DC 21    // 9 is default, different on ethernet/touch combo

#define ETHERNET_RESET 9	// WIZ820io
#define PERIPHERAL_RESET 22 // for ILI9341 and other peripherals

// MOSI=11, MISO=12, SCK=13

XPT2046_Touchscreen ts(CS_PIN);


// from ILI9341_t3.cpp, constructor with all pins defined 
// ILI9341_t3(uint8_t cs, uint8_t dc, uint8_t rst, uint8_t mosi, uint8_t sclk, uint8_t miso)
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, PERIPHERAL_RESET, 11, 13, 12);
//ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, 255, 11, 13, 12);

// uint8_t backlight=5;
 uint8_t laser=4;
 uint8_t vbsense_pin = 0;  // battery sense on analog 0, p14
 uint16_t vbsense;
// 
// uint8_t buzzer_pin = 6;
 
char log_message[128];


void setup() {
  Serial.begin(115200);
  while((!Serial) && (millis()<5000));    // wait until serial monitor is open or timeout
  Serial.print(millis());

  Serial.println("ILI9341 Test");

  strcpy (log_message, "Build: ");
  strcat (log_message, __TIME__);
  strcat (log_message, " MDT, ");
  strcat (log_message, __DATE__);  
  strcat (log_message, 0x00);
  Serial.println(log_message);
  
  // yes this is deprecated but I don't know a better way to set clock
  // when we don't use the SPI methods directly
  // DIV16 gives 2 MHz SCK
  // DIV 4 gives 2 MHz
  // SPI.setClockDivider(SPI_CLOCK_DIV16);

  // This might be the right way
  // default SPI.SPIsettings(4000000, MSBFIRST, SPI_MODE0);
  // With clock 4000000, SCK is breifly 24 MHz then becomes 2 MHz
  // 2000000 or 8000000 also give 2 MHz SCK
  // SPISettings(4000000, MSBFIRST, SPI_MODE0);    


  pinMode(PERIPHERAL_RESET, INPUT);
  // pinMode(PERIPHERAL_RESET, OUTPUT);
  // digitalWrite(PERIPHERAL_RESET, HIGH);
  delay(500);

  /**
   * WIZ820io/W5200 must be at least reset to avoid it clashing with SPI
   */
  pinMode(ETHERNET_RESET, OUTPUT);
  digitalWrite(ETHERNET_RESET, LOW);
  delay(1);
  digitalWrite(ETHERNET_RESET, HIGH);  

  // reset the touchscreen
  // pinMode(PERIPHERAL_RESET, OUTPUT);
  // digitalWrite(PERIPHERAL_RESET, LOW);
  // delay(10);
  // digitalWrite(PERIPHERAL_RESET, HIGH);
  // delay(100);

  // SPISettings(8000000, MSBFIRST, SPI_MODE0);    // SCK is 24 MHz with 4000000
 
  tft.begin();    // SPI lib begin() called from tft.begin() sets up SPI, and drives the PERIPHERAL RESET too

  tft.setRotation(1);

  tft.fillScreen(ILI9341_GREEN);

  delay(200);

  tft.fillScreen(ILI9341_BLACK);

  delay(200);

  // do 
  // {
  //     tft.fillScreen(ILI9341_GREEN);
  //     Serial.println("Fill green");
  //     delay(1000);
  // } while (true);

  ts.begin();
  
}


boolean wastouched = true;  // so no touch starts with "No Touch" on display vs blank
uint16_t xmax, xmin=4095, ymax, ymin=4095, zmax, zmin=4095;
uint16_t xnow, ynow, znow;
uint32_t touch_start, touch_total, touch_secs;  // in millis unless _secs

void loop() {
  boolean istouched = ts.touched();
  if (istouched) 
  {
    TS_Point p = ts.getPoint();
    if (!wastouched) {
      // it's a new touch starting... 
      // ...do things needed at start only of new touch
      
      touch_start = millis();
      
      tft.fillScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_YELLOW);
      tft.setFont(Arial_48);
      tft.setCursor(5, 20);
      tft.print("Touch");
      
      
      tft.setTextColor(ILI9341_CYAN);
      tft.setFont(Arial_18);
      tft.setCursor(35, 90);  
      tft.print("now");
      tft.setCursor(110, 90);
      tft.print("min");
      tft.setCursor(185, 90);
      tft.print("max");
      tft.setCursor(260, 90);
      tft.print("delta");
    

    }
    // fall through after start of touch actions
    // not a new touch start; how long have we been touching?
    touch_total = millis() - touch_start;
    // wipe to black the part of screen with changing values
    // note: for 48 pt font, Y span of 48 leaves one pixel not cleared...
    tft.fillRect(200, 20, 119, 49, ILI9341_BLACK);    
    tft.setTextColor(ILI9341_YELLOW);
    tft.setFont(Arial_48);
    tft.setCursor(200, 20);
    touch_secs = touch_total/1000;
    tft.print(touch_secs);    
          
    if (0 == touch_secs % 5) stats_reset();
    stats_calc(p.x, p.y, p.z);
    // wipe to black the part of screen with changing values
    tft.fillRect(30, 120, 289, 89, ILI9341_BLACK);    
    
    
    tft.setTextColor(ILI9341_GREEN);
    tft.setFont(Arial_18);
    tft.setCursor(5, 120);
    tft.print("X");
    tft.setCursor(35, 120);
    tft.print(p.x);
    tft.setCursor(110, 120);
    tft.print(xmin);
    tft.setCursor(185, 120);
    tft.print(xmax);
    tft.setCursor(260, 120);
    tft.print(xmax-xmin);
    
    tft.setCursor(5, 150);
    tft.print("Y");
    tft.setCursor(35,150);
    tft.print(p.y);
    tft.setCursor(110, 150);
    tft.print(ymin);
    tft.setCursor(185, 150);
    tft.print(ymax);
    tft.setCursor(260, 150);
    tft.print(ymax-ymin);
    
    tft.setCursor(5, 180);
    tft.print("Z");
    tft.setCursor(35,180);
    tft.print(p.z);
    tft.setCursor(110, 180);
    tft.print(zmin);
    tft.setCursor(185, 180);
    tft.print(zmax);
    tft.setCursor(260, 180);
    tft.print(zmax-zmin);


    
    Serial.print("x = ");
    Serial.print(p.x);
    Serial.print(", y = ");
    Serial.print(p.y);
    Serial.print(", z = ");
    Serial.println(p.z);
  } else {
    if (wastouched) {
      tft.fillScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_RED);
      tft.setFont(Arial_48);
      tft.setCursor(120, 50);
      tft.print("No");
      tft.setCursor(80, 120);
      tft.print("Touch");
      // reset all min and max if no touch
      stats_reset();
      Serial.println("no touch");
      
    }
    
  }
  wastouched = istouched;
  delay(100);
}

/**
Caclulate min max and delta for X Y Z
**/
void stats_calc (uint16_t x, uint16_t y, uint16_t z)
{
  xmax = x > xmax ? x : xmax;  
  ymax = y > ymax ? y : ymax;
  zmax = z > zmax ? z : zmax;
  
  xmin = x < xmin ? x : xmin;  
  ymin = y < ymin ? y : ymin;
  zmin = z < zmin ? z : zmin;  
}

/**
Reset stats, useful at first touch
and after a few seconds while touching
**/
void stats_reset (void)
{
  xmin=4095; xmax=0; ymin=4095; ymax=0; zmin=4095; zmax=0;
}
