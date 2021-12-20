#ifndef ScrollPatternService_h
#define ScrollPatternService_h

#include "FastLED.h"

class ScrollPatternService
{
    private:

      #define LED_TYPE WS2812B
      #define COLOR_ORDER GRB
      #define PIN 7
      #define NUM_LEDS 100
      
      CRGB leds[NUM_LEDS];
      
      #define NumberOfColors 3
      int BlockLEDCounter;
      int ColorCounter;
      
      int BlockWidth = 16;
      int WaveDelay = 100;
      bool Instant = true;

      void setupPattern(CRGB Color1, CRGB Color2, CRGB Color3) 
      {
        int LedPosition;
        
        if(Instant) 
        {
          // Fill initial pattern
          for(int i=0; i < NUM_LEDS; i=i + (NumberOfColors*BlockWidth) ) 
          {
            for (ColorCounter=0; ColorCounter < NumberOfColors; ColorCounter++) 
            {
              for(BlockLEDCounter=0; BlockLEDCounter < BlockWidth; BlockLEDCounter++) 
              {
                LedPosition = i + (ColorCounter*BlockWidth) + BlockLEDCounter;
                
                if( LedPosition  <  NUM_LEDS) 
                {
                  switch (ColorCounter) 
                  {
                    case 0: leds[LedPosition] = Color1; break;
                    case 1: leds[LedPosition] = Color2; break;
                    case 2: leds[LedPosition] = Color3; break;
                  }
                }
              }
            }
          }
        }
        else
        {
          // Black for all LEDs
          fill_solid(leds,NUM_LEDS,CRGB::Black);
        }
      
        FastLED.show();
        
        // Scrolling bars
        BlockLEDCounter = 0;
        ColorCounter = 0;
      }

    public:
        
        void setup()
        {
          FastLED.addLeds<LED_TYPE,PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
        }

        void runPattern(CRGB Color1, CRGB Color2, CRGB Color3, bool isFirstCall)
        {
          if(isFirstCall)
          {
            setupPattern(Color1, Color2, Color3);
          }
          
          memmove( &leds[1], &leds[0], (NUM_LEDS-1) * sizeof(CRGB) );
        
          switch (ColorCounter) 
          {
            case 0: leds[0] = Color3; break;
            case 1: leds[0] = Color2; break;
            case 2: leds[0] = Color1; break;
          }
        
          FastLED.show();
          
          BlockLEDCounter++;
          
          if (BlockLEDCounter==BlockWidth) 
          {
            BlockLEDCounter = 0;
            ColorCounter++;
            if (ColorCounter==NumberOfColors) 
            {
              ColorCounter = 0;
            }
          }
          
          delay(WaveDelay);
        }
};

ScrollPatternService scrollPatternService;

#endif
