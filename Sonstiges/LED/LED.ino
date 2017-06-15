#include <Adafruit_DotStar.h>
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 14 // 180 // Number of LEDs in strip
#define NUMSTRIPES 1
#define STRIPELENGTH 14

#define DATAPIN    4
#define CLOCKPIN   5

Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

#include <Arduino.h>
#include <Wire.h>

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
    Serial.begin(9600);
   
}

uint8_t  animation    = 0;
uint32_t    gelb = 0xFFFF00;
uint32_t    orange = 0xFF0000;
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
