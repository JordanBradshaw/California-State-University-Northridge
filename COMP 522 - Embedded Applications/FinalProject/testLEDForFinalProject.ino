#include <FastLED.h>
#define LED_PIN     5
#define NUM_LEDS    24
#define BRIGHTNESS  10
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 150

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
int ran=0;
int preCounter=0;

void setup() {
  delay(3000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  currentPalette=LavaColors_p;
  currentBlending=LINEARBLEND;
}

void FillLEDsWithPokeBallColors() {
  for (int i=0; i<NUM_LEDS; i++) {
    if (i < (NUM_LEDS/4)||i >((NUM_LEDS/4)*3)) {
      leds[i]=CRGB::White;
    }
    else if (i==(NUM_LEDS/4)||i==((NUM_LEDS/4)*3)) {
      leds[i]=CRGB::Black;
    }
    else {
      leds[i]=CRGB::Red;
    }
  }
}

void FillLEDsWithUltraBallColors() {
  for (int i=0; i<NUM_LEDS; i++) {
    if (i < (NUM_LEDS/4)||i >((NUM_LEDS/4)*3)) {
      leds[i]=CRGB::White;
    }
    else if (i==(NUM_LEDS/4)||i==((NUM_LEDS/4)*3)) {
      leds[i]=CRGB::Black;
    }
    else {
      int y=map(i, (NUM_LEDS/4), ((NUM_LEDS/4)*3), 1, 8);
      if (y==2||y==6) {
        //if ((i%4) == 1){
        leds[i]=CRGB::Yellow;
      }
      else {
        leds[i]=CRGB::Black;
      }
    }
  }
}


void FillLEDsWithNestBallColors() {
  for (int i=0; i<NUM_LEDS; i++) {
    if (i < (NUM_LEDS/4)||i >((NUM_LEDS/4)*3)) {
      leds[i]=CRGB::White;
    }
    else if (i==(NUM_LEDS/4)||i==((NUM_LEDS/4)*3)) {
      leds[i]=CRGB::Black;
    }
    else {
      int y=map(i, (NUM_LEDS/4), ((NUM_LEDS/4)*3), 1, 16);
      if (y==2||y==14) {//FIRST STRIPE
        leds[i]=CRGB::Red;
      }
      else if (y==4||y==12) {//SECOND STRIPE
        leds[i]=CRGB::Red;
      }
      else {
        leds[i]=CRGB::Black;
      }
    }
  }
}

void FillLEDsWithMoonBallColors() {
  for (int i=0; i<NUM_LEDS; i++) {
    if (i < (NUM_LEDS/4)||i >((NUM_LEDS/4)*3)) {
      leds[i]=CRGB::Grey;
    }
    else if (i==(NUM_LEDS/4)||i==((NUM_LEDS/4)*3)) {
      leds[i]=CRGB::Black;
    }
    else {
      int y=map(i, (NUM_LEDS/4), ((NUM_LEDS/4)*3), 1, 5);
      if (y==1||y==2) {//HALF Turquoise
        leds[i]=CRGB::Turquoise;
      }
      else if (y==3) {//Gonna Have to make moon with this
        leds[i]=CRGB::Yellow;
      }
      else {
        leds[i]=CRGB::Black;
      }
    }
  }
}

void loop() {
  if (preCounter<200) {
    static uint8_t startIndex=0;
    startIndex=startIndex+1; /* motion speed */
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
    FastLED.delay(1000/UPDATES_PER_SECOND);
    preCounter++;
  }
  else if (preCounter==200) {
    PokeballLibrary();
    FastLED.setBrightness(0);
    for (int i=0; i<255;i++) {
      FastLED.setBrightness(i);
      FastLED.show();
      FastLED.delay(1000/UPDATES_PER_SECOND);
      delay(5);
    }
    preCounter++;
    delay(50);
  }
  else if (preCounter>200) {
    PokeballLibrary();
    FastLED.show();
    FastLED.delay(1000/UPDATES_PER_SECOND);
    delay(2000);
  }
}
void PokeballLibrary() {
  if (ran==0) {
    FillLEDsWithPokeBallColors();
  }
  else if (ran==1) {
    FillLEDsWithUltraBallColors();
  }
  else if (ran==2) {
    FillLEDsWithMoonBallColors();
  }
  else if (ran==3) {
    FillLEDsWithNestBallColors();
    ran=-1;
  }
  ran++;
}

void FillLEDsFromPaletteColors(uint8_t colorIndex) {
  uint8_t brightness=255;
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i]=ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
    colorIndex+=3;
  }
}
