#include <FastLED.h>

#define LED_PIN      1      // which pin your pixels are connected to
#define C_PIN      2        // Circle LED pin
#define NUM_LEDS    8       // how many LEDs you have
#define NUM_C_LEDS    16    // how many LEDs you have
#define BRIGHTNESS 150      // 0-255, higher number is brighter. 
#define SATURATION 255      // 0-255, 0 is pure white, 255 is fully saturated color
#define SPEED       10      // How fast the colors move.  Higher numbers = faster motion
#define STEPS        2      // How wide the bands of color are.  1 = more like a gradient, 10 = more like stripes


#define COLOR_ORDER GRB  // Try mixing up the letters (RGB, GBR, BRG, etc) for a whole new world of color combinations

CRGB leds[NUM_LEDS + NUM_C_LEDS];
CRGBPalette16 currentPalette;
CRGBPalette16 targetPalette( PartyColors_p );
TBlendType    currentBlending;
int ledMode = 3;


const TProgmemPalette16 Custom_Colors PROGMEM =
{
  CRGB::DarkGoldenrod,
  CRGB::DarkGoldenrod, 
  CRGB::Red,
  CRGB::Red,

  CRGB::Purple,
  CRGB::Purple,
  CRGB::DarkRed,
  CRGB::DarkRed,

  CRGB::DarkOrange,
  CRGB::DarkOrange,
  CRGB::DarkMagenta,
  CRGB::DarkMagenta,

  CRGB::Red,
  CRGB::Red,
  CRGB::Orange,
  CRGB::Orange
};


void setup() {
  delay( 2000 ); // power-up safety delay
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<WS2812B, C_PIN, COLOR_ORDER>(leds, NUM_C_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  currentBlending =LINEARBLEND;
}

void loop() {

  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */

  switch (ledMode) {

  case 0:
    currentPalette = HeatColors_p;    //Red & Yellow, Fire Colors
    break;
  case 1:
    currentPalette = ForestColors_p;    
    break;
  case 2: 
    currentPalette = OceanColors_p;  
    break;
  case 3: 
    currentPalette = Custom_Colors;  //My custom palette from above
    break;
  case 4:
    currentPalette = RainbowColors_p;  
    break;
  case 5:
    currentPalette = RainbowStripeColors_p;   
    break;      
  case 6:
    currentPalette = PartyColors_p; 
    break;
  } 

  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
  FastLED.delay(1000 / SPEED);  
}

void FillLEDsFromPaletteColors( uint8_t colorIndex) {
  for( int i = 0; i < NUM_LEDS + NUM_C_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS, currentBlending);
    colorIndex += STEPS;              
  }
}

void shortKeyPress() {
  ledMode++;
  if (ledMode > 6) {
    ledMode=0; 
  }  
}
    
