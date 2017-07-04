#include <Adafruit_DotStar.h>
#include <SPI.h>       
#define NUMPIXELS 52 // Number of LEDs in strip
#define NUMSTRIPES 4
#define STRIPELENGTH 13

#define DATAPIN    4
#define CLOCKPIN   5
#define DATA2    6
#define CLOCK2   7
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
  Adafruit_DotStar strip2 = Adafruit_DotStar(
  NUMPIXELS, DATA2, CLOCK2, DOTSTAR_BRG);


uint8_t  animation    = 1;
uint32_t    gelb = 0xFFFF00;
uint32_t    orange = 0x55FF00;
uint32_t    weiss = 0xFFFFFF;
uint32_t    rot = 0x00FF00;
uint32_t    aus = 0x000000;
int anders=STRIPELENGTH;


void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(DATAPIN, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
    pinMode(DATA2, OUTPUT);
  pinMode(CLOCK2, OUTPUT);
  strip.begin(); // Initialize pins for output
  strip2.begin();
  strip.show();  // Turn all LEDs off ASAP
  strip2.show();
}

// Runs 10 LEDs at a time along strip, cycling through red, green and blue.
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

int      head  = 0, tail = -10; // Index of first 'on' and 'off' pixels
uint32_t color = 0xffffff   ;   // 'On' color (starts red)

void loop() {
while (Serial.available())
  {
    animation =Serial.read();
  }

if(animation == 0){
    anders=STRIPELENGTH;
    for(int i=0;i<NUMPIXELS;i++){
         strip.setPixelColor(i,gelb);
         strip2.setPixelColor(i,gelb);
    }
    }else if(animation ==3){
    for(int j=0;j<NUMSTRIPES;j++){
      for(int i=0;i<STRIPELENGTH;i++){
        if(i!=anders){
          strip.setPixelColor(i+j*STRIPELENGTH,gelb);
          strip2.setPixelColor(i+j*STRIPELENGTH,gelb);
        }
      }
      strip.setPixelColor(anders+j*STRIPELENGTH,rot);
      strip2.setPixelColor(anders+j*STRIPELENGTH,rot);
    }
     anders--; 
     delay(5);
     if(anders==-2){
      anders=-1;
     }
    }else if(animation==2){
       anders=STRIPELENGTH;
       for(int i=0;i<NUMPIXELS;i++){
         strip.setPixelColor(i,weiss);
         strip2.setPixelColor(i,weiss);
         }
    }else if(animation==1){
      for(int i=0; i<NUMSTRIPES;i++){
        for(int j=0;j<STRIPELENGTH/2;j++){
          strip.setPixelColor(j+i*STRIPELENGTH,gelb);
          strip2.setPixelColor(j+i*STRIPELENGTH,gelb);
        }
         for(int j=STRIPELENGTH/2;j<STRIPELENGTH;j++){
          strip.setPixelColor(j+i*STRIPELENGTH,orange);
          strip2.setPixelColor(j+i*STRIPELENGTH,orange);
        }
     }
    }else if(animation==4){
       anders=STRIPELENGTH;
       for(int i=0;i<NUMPIXELS;i++){
         strip.setPixelColor(i,aus);
         strip2.setPixelColor(i,aus);
         }
    }
    
  

strip.show();
strip2.show();
delay(100);
}

