#include <FastLED.h>
#include <Adafruit_DotStar.h>
#include <math.h> // DIDN't USE BUT YA KNOW
//UNO SETUP
#define NUM_LEDS 255 
#define DATA_PIN    4
#define CLOCK_PIN   5
#define BRIGHTNESS 20
//FAST LED VARS
#define LED_TYPE    APA102
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 2000
CRGBPalette16 currentPalette = CloudColors_p;
TBlendType    currentBlending = LINEARBLEND;

const int BUTTON = 1; //THIS IS THE BUTTON PRESS
const int LED = 0; //THIS WAS FOR DEBUGGING BUTTON PRESS
int BUTTONstate = 0;
//LED ARRAY PARTY
CRGB leds[NUM_LEDS];
#define ringCount 10

uint8_t rings[ringCount][2] = { //LED RANGES
    {254,254},    //0 Center Point
    {248,253},    //1
    {236,247},    //2
    {216,235},    //3
    {192,215},    //4
    {164,191},    //5
    {132,163},    //6
    {92,131},    //7
    {48,91},    //8
    {0,47},     //9 Outter Ring
};
float * ringSteps256;
float myacos(float x); //ATEMPTING TRIG
uint8_t lastRing = ringCount - 1;


//256 THIS IDEA WAS TAKEN FROM A GITHUB I'D HAVE TO REFIND
uint16_t angleToPixel256(uint8_t angle, uint8_t ring){ ///THIS HELPS CALCULATE THE ANGLE ON THE SPECIFIC RING
  if(ring >= ringCount) return 0;
  return rings[ring][0] + int(angle/ringSteps256[ring]);
}
//Fill in the ringSteps arrays for later use.
inline void setupRings(){
  uint8_t count = 0;
  ringSteps256 = (float*)malloc(ringCount * sizeof(float));
  for(int r=0; r<ringCount; r++)
  {
    count = (rings[r][1] - rings[r][0] + 1);
    ringSteps256[r] = (256.0/float(count)); //DIVIDING FOR DISTANCE AS STATED
  }
}
void setPixel256(uint8_t angle, uint8_t ring, CRGB color){ //THIS IS TO SET A SPECIFIC PIXEL AT AN ANGLE A COLOR
  uint16_t pixel = angleToPixel256(angle, ring);
  leds[pixel] = color;
}
void drawRadius256(uint8_t angle, CRGB color, uint8_t startRing, uint8_t endRing){ // THIS LETS YOU DRAW A ANGLE FROM A RING TO A RING A COLOR
  angle +=4;
  if(startRing > lastRing) startRing = 0;
  if(endRing > lastRing) endRing = lastRing;
  for(uint8_t r=startRing; r<=endRing; r++)
  {
    setPixel256(angle, r, color);
  }
}
void fillRing256(uint8_t ring, CRGB color, uint8_t startAngle, uint8_t endAngle){//THIS LETS YOU DRAW AN ANGLE TO AN ANGLE ON A SPECIFIC RING
  startAngle += 64;//I DID THIS TO OFFSET THE POKEBALLS SO THAT THE VIDEOS AND THE POKEBALLS BOTH ARE ALIGNED HORIZONTALLY
  endAngle += 66;
  uint8_t start = angleToPixel256(startAngle, ring);
  uint8_t end = angleToPixel256(endAngle, ring);
  if(start > end)
  {
    for(int i=start; i<=rings[ring][1]; i++)
    {
      leds[i] = color;
    }
    for(int i=rings[ring][0]; i<=end; i++)
    {
      leds[i] = color;
    }
  }
  else if(start == end)
  {
    for(int i=rings[ring][0]; i<=rings[ring][1]; i++)
    {
      leds[i] = color;
    } 
  }
  else
  {
    for(int i=start; i<=end; i++)
    {
      leds[i] = color;
    }
  }if (start <= 230){
    leds[start] = CRGB::Black;
    leds[end] = CRGB::Black;
  }
}
//MY EASY FILL FUNCTIONS
void fillBottomOfBall(CRGB color){
  for(int currRing = 5;currRing <=9; currRing++){
    int startLED = rings[currRing][0] + (((rings[currRing][1] - rings[currRing][0]) / 2) + 1);
    int lastLED = rings[currRing][1];
    for(int currLED = startLED + 1 ;currLED <= lastLED; currLED++){
      leds[currLED] = color;
    }
  }
}
void fillTopOfBall(CRGB color){
  for(int currRing = 5;currRing <=9; currRing++){
    int startLED = rings[currRing][0];
    int lastLED = rings[currRing][1]- (((rings[currRing][1] - rings[currRing][0]) / 2));
    for(int currLED = startLED + 1;currLED < lastLED; currLED++){
      leds[currLED] = color;
    }
  }
}
void fillCenterOfBall(CRGB color){
  for(int currRing = 0;currRing <=3; currRing++){
    if (currRing != 2){
    int startLED = rings[currRing][0];
    int lastLED = rings[currRing][1];
    for(int currLED = startLED;currLED <= lastLED; currLED++){
      leds[currLED] = color;
    }
}}}

//TEMPLATES HARD CODED :(
void ultraBallTemplate(){
  FastLED.clear();
  fillBottomOfBall(CRGB::White);
  fillCenterOfBall(CRGB::White);
  fillRing256(9,CRGB::Yellow,210,50);
  fillRing256(8,CRGB::Yellow,195,65);
  fillRing256(7,CRGB::Yellow,255-60,65);
  fillRing256(6,CRGB::Yellow,30,65);
  fillRing256(6,CRGB::Yellow,255-60,255-25);
  fillRing256(5,CRGB::Yellow,40,65);
  fillRing256(5,CRGB::Yellow,255-55,255-35);
  FastLED.show();
}
void moonBallTemplate(){
  FastLED.clear();
  fillBottomOfBall(CRGB::White);
  fillCenterOfBall(CRGB::White);
  fillRing256(9,CRGB::Turquoise,195,0);
  fillRing256(8,CRGB::Turquoise,195,0);
  fillRing256(7,CRGB::Turquoise,195,5);
  fillRing256(6,CRGB::Turquoise,195,15);
  fillRing256(5,CRGB::Turquoise,195,10);
  setPixel256(30+65,8,CRGB::Grey);
  setPixel256(35+65,8,CRGB::Grey);
  setPixel256(45+65,8,CRGB::Grey);
  setPixel256(60,9,CRGB::Yellow);
    setPixel256(60,8,CRGB::Yellow);
    setPixel256(65,7,CRGB::Yellow);
    setPixel256(75,7,CRGB::Yellow);
    FastLED.show();
}
void quickBallTemplate(){
  FastLED.clear();
  fillTopOfBall(CRGB::Blue);
  fillBottomOfBall(CRGB::Blue);
  fillCenterOfBall(CRGB::White);
  fillRing256(5,CRGB::Yellow,0,254);
  drawRadius256(32,CRGB::Yellow,5,9);
  drawRadius256(96,CRGB::Yellow,5,9);
  drawRadius256(160,CRGB::Yellow,5,9);
  drawRadius256(224,CRGB::Yellow,5,9);
    drawRadius256(34,CRGB::Yellow,5,9);
  drawRadius256(98,CRGB::Yellow,5,9);
  drawRadius256(162,CRGB::Yellow,5,9);
  drawRadius256(226,CRGB::Yellow,5,9);
    drawRadius256(30,CRGB::Yellow,5,9);
  drawRadius256(94,CRGB::Yellow,5,9);
  drawRadius256(158,CRGB::Yellow,5,9);
  drawRadius256(222,CRGB::Yellow,5,9);
  setPixel256(60,5,CRGB::Yellow);
  setPixel256(0,5,CRGB::Black);
  setPixel256(130,5,CRGB::Black);
  FastLED.show();
}
void pokeBallTemplate(){
 FastLED.clear();
 fillBottomOfBall(CRGB::White);
  fillCenterOfBall(CRGB::White);
   fillTopOfBall(CRGB::Red);
   FastLED.show();
}
//FAST LED
void FillLEDsFromPaletteColors( uint8_t colorIndex){
    uint8_t brightness = 255;
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
//FAST LED INTRO && SCALE BRIGHTNESS AND THEN DIM
void setup() { 
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);
  setupRings();  
  Serial.begin(115200);
  LEDS.addLeds<APA102,DATA_PIN,CLOCK_PIN,BGR>(leds,NUM_LEDS);
  LEDS.setBrightness(5);
  FastLED.clear();
  int loadCount=0;
  while(loadCount < 255){
  FastLED.clear();
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; // motion speed 
  FillLEDsFromPaletteColors(startIndex);
  FastLED.show();
  loadCount++;
  //FastLED.delay(1/4);
  //FastLED.delay(1000 / UPDATES_PER_SECOND);
  }
  FastLED.clear();
  pokeBallTemplate();
  int loadBrightness = 0;
  while(loadBrightness <= 200){
    if (loadBrightness <=200){
      LEDS.setBrightness(loadBrightness);
      FastLED.show();
    }
    loadBrightness++;
  }
    while(loadBrightness >= BRIGHTNESS){
    if (loadBrightness >=BRIGHTNESS){
      LEDS.setBrightness(loadBrightness);
      FastLED.show();
    }
    loadBrightness--;
  }
}

int currentBall = 0;
uint16_t pixel = 0;
uint8_t angle256 = 0;

//STATE BASED
void loop(){
  LEDS.setBrightness(BRIGHTNESS);
  FastLED.clear();
  BUTTONstate = digitalRead(BUTTON);
  if (BUTTONstate == HIGH){
    switch (currentBall){
  case 0:
  pokeBallTemplate();
  break;
  case 1:
  ultraBallTemplate();
  break;
  case 2:
  quickBallTemplate();
  break;
  case 3:
  moonBallTemplate();
  break;
  default:
  quickBallTemplate();
  break;
  }
  }
  else if (BUTTONstate == LOW){
    currentBall = (currentBall +1)%4;
    delay(500);
  }
}
