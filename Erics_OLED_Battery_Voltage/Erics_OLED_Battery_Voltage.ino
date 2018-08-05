/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers
Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98
This example is for a 128x32 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)
Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!
Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information


Erics Notes:
Adafruit GitHub Lib D/L: https://github.com/adafruit/Adafruit_SSD1306
Arduino Nano:
SDA connected to pin Analog 4
SCL connected to pin Analog 5
Monochrome OLEDs based on SSD1306 drivers

This sketch simply prints battery voltage  Nothing more.  Yeah boring eh?

Added Battery Voltage Monitoring:
Changed A0 to be used for Bus Voltage monitoring (on board LiPo)
Will use voltage divider with 2 10Kohm resistors to monitor the 7.4V supply from battery
http://forum.arduino.cc/index.php/topic,13728.0.html
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

const float referenceVolts = 5.0;        // the default reference on a 5 volt board 
const int batteryPin = 0;          // +V from battery is connected to analog pin 0
float battv;

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();
}
 
void loop() {
  checkbatt();
   // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("MKME Test New OLED");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void checkbatt()
 {
int val = analogRead(batteryPin);  // read the value from the A0 battery monitoring pin with voltage divider
  battv = (val / 511.0) * referenceVolts ; // divide val by (1023/2)because the resistors divide the voltage in h
 }

