#include <FastLED.h>
#define NUM_LEDS 12
#define DATA_PIN 18
CRGB leds[NUM_LEDS];

class color{
  public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
  color(uint8_t r,uint8_t g,uint8_t b){
    red=r;
    green=g;
    blue=b;
  }
};

color start(255,0,0);
color stop(0,0,255);

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  for(int i=0;i<NUM_LEDS;i++)
    leds[i] = CRGB(start.red,start.green,start.blue);
  FastLED.show();
}
