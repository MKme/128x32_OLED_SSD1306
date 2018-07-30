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

This sketch simply prints a button status to OLED and blinks the LED  Yeah boring eh?
Use 1-10K resistor from button signal pin to ground as pull down.
Other button pin to VCC

*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status


void setup()   {   
           
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
// initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}
 


void loop() {
   buttonstate();
   writetext();
   }
   
void buttonstate()
   {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
       }
        }
   
void writetext()
  {
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(buttonState);
  display.display();
  //delay(2000);
  display.clearDisplay();
}


