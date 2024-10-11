#include <FastLED.h>

// FastLED
#define NUM_LEDS 12
#define DATA_PIN 18
CRGB leds[NUM_LEDS];

// Colors
CRGB myColor(255,0,0);

// Menu
short menu=0;

// Serial
bool stringComplete = false;
String inputString = "";

void setup() {
  Serial.begin(115200);
  inputString.reserve(200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(32);
}

void loop() {
  if(stringComplete){
    if(catchValue("menu")>=0)
      menu=catchValue("menu");
  }
  switch (menu) {
    case 0:
      fillColor(myColor);
      break;
    case 1: 
      fill_gradient_RGB(leds,NUM_LEDS,myColor,CRGB(0,0,255));
      break;
  }
  FastLED.show();
  inputString = "";
  stringComplete = false;
}

void fillColor(CRGB color){
  for(int i=0;i<NUM_LEDS;i++)
    leds[i] = color;
}

// Serial functions

int catchValue(String valName) {
  String inputValue = "-1";
  if (inputString.indexOf(valName) != -1) {
    inputValue = inputString.substring(valName.length(), inputString.length());
  }
  return inputValue.toInt();
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    } else
      inputString += inChar;
  }
}



