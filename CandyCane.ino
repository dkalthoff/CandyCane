#include "FastLED.h"
#include "ScrollPatternService.h"

int counter = 0;

void setup()
{
  Serial.begin(9600);
  delay(3000);

  scrollPatternService.setup();
}

void loop() 
{
  Serial.print("Loop count: ");
  Serial.print(counter);
  
  Serial.print(" | Should run pattern setup: ");
  Serial.println(counter == 0 || counter == 500);

  if(counter < 500) 
  {
    scrollPatternService.runPattern(CRGB::Red, CRGB::Red, CRGB::White, counter == 0);
  }
  else
  {
    scrollPatternService.runPattern(CRGB::Green, CRGB::White, CRGB::Red, counter == 500);
  }
  
  if(counter > 1000) { counter = 0; } else { counter++; }
}
