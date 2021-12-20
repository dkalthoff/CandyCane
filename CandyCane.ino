#include "FastLED.h"
#include "ScrollPatternService.h"

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 600
CRGB leds[NUM_LEDS];
#define PIN 7

int counter = 0;

void setup()
{
  Serial.begin(9600); // open the serial port at 9600 bps:
  delay(3000);

  FastLED.addLeds<LED_TYPE,PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
}

void loop() 
{
  Serial.print("Loop count: ");
  Serial.print(counter);
  
  Serial.print(" | Should run pattern setup: ");
  Serial.println(counter == 0 || counter == 500);

  if(counter < 500) 
  {
    scrollPatternService.runPattern(leds, CRGB::Red, CRGB::Red, CRGB::White, counter == 0);
  }
  else
  {
    scrollPatternService.runPattern(leds, CRGB::Green, CRGB::White, CRGB::Red, counter == 500);
  }

  counter++;
  
  if(counter >= 1000) { counter = 0; }
}
