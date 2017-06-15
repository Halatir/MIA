// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!

#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 14 // 180 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    4
#define CLOCKPIN   5
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);
#include <Arduino.h>
#include <Wire.h>         // this #include still required because the RTClib depends on it

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
  // #define Serial SerialUSB
#endif


void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
    Serial.begin(9600);
   
}

// Runs 10 LEDs at a time along strip, cycling through red, green and blue.
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

int      head  = 0, tail = -10; // Index of first 'on' and 'off' pixels
uint32_t    color = 0xF2522A;   // 'On' color (starts red)
uint8_t  animation    = 0;
uint32_t    gelb = 0x0000FF;
uint32_t    orange = 0xFF8800;
uint32_t    weiss = 0xFFFFFF;

/*Lampenzustände
0=Basiswert -->Gelb
1=Tischweisung --> Weiß
2=Kellner rufen --> Gelb unten Orange oben
*/
void loop() {

  while (Serial.available())
  {
    animation =Serial.read();
  }

  //Hier LED Farben programmieren
  if(animation == 0){
    for(int i=0;i<NUMPIXELS;i++){
         strip.setPixelColor(i,gelb);
    }
  }else if(animation == 1){
     for(int i=0;i<NUMPIXELS;i++){
         strip.setPixelColor(i,orange);
    }
  }else if(animation ==2){
     for(int i=0;i<NUMPIXELS;i++){
         strip.setPixelColor(i,weiss);
    }
  }
  strip.show();
  //delay(500);

 /* strip.setPixelColor(head, color); // 'On' pixel at head
  strip.setPixelColor(tail, 0xF2A82A);     // 'Off' pixel at tail
  strip.show();                     // Refresh strip
  delay(150);                        // Pause 20 milliseconds (~50 FPS)

  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
          //  Next color (R->G->B) ... past blue now?
         color = 0xFF4500;           //   Yes, reset to red
  }
  if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index
  */
}