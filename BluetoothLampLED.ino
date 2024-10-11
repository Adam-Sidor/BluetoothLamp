#include <FastLED.h>

// FastLED
#define NUM_LEDS 12
#define DATA_PIN 18
CRGB leds[NUM_LEDS];

// Colors
CRGB myColor(255, 0, 0);
CRGB gradientColor1(0, 0, 0);
CRGB gradientColor2(0, 0, 0);
uint8_t brightness = 255;

// Menu
short menu = 0;

// Serial
bool stringComplete = false;
String inputString = "";

void setup() {
  Serial.begin(115200);
  inputString.reserve(200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  if (stringComplete) {
    //option recive
    if (catchValue("menu") >= 0)
      menu = catchValue("menu");
    if (catchValue("brightness") >= 0)
      brightness = catchValue("brightness");

    //myColor recive
    if (catchValue("red") >= 0)
      myColor.red = catchValue("red");
    if (catchValue("green") >= 0)
      myColor.green = catchValue("green");
    if (catchValue("blue") >= 0)
      myColor.blue = catchValue("blue");

    //gradientColor1 recive
    if (catchValue("g1red") >= 0)
      gradientColor1.red = catchValue("g1red");
    if (catchValue("g1green") >= 0)
      gradientColor1.green = catchValue("g1green");
    if (catchValue("g1blue") >= 0)
      gradientColor1.blue = catchValue("g1blue");

    //gradientColor2 recive
    if (catchValue("g2red") >= 0)
      gradientColor2.red = catchValue("g2red");
    if (catchValue("g2green") >= 0)
      gradientColor2.green = catchValue("g2green");
    if (catchValue("g2blue") >= 0)
      gradientColor2.blue = catchValue("g2blue");
  }
  switch (menu) {
    case 0:
      fillColor(myColor);
      break;
    case 1:
      fill_gradient_RGB(leds, NUM_LEDS, gradientColor1, gradientColor2);
      break;
  }
  FastLED.setBrightness(brightness);
  FastLED.show();
  inputString = "";
  stringComplete = false;
}

//Functions
void fillColor(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++)
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
