#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    16
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define BUTTON_PIN 2
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 10

int buttonState = 0;
static uint8_t startIndex = 0;
bool gameOver = false;
volatile int state = LOW;

void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    Serial.begin(9600);
    pinMode(BUTTON_PIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), stopGame, CHANGE);
}


void loop()
{
  if (startIndex == 16) {
    startIndex = 0;
  }
  if(!gameOver) { 
    for( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
    leds[startIndex] = CRGB::White;
    FastLED.show();

    FastLED.delay(1000 / UPDATES_PER_SECOND);
    startIndex = startIndex + 1;
  }
}

void stopGame() {
  if (!gameOver) {
    if(startIndex == 7) {
      Serial.print("YOU WIN");
      Serial.println();
    }
    else {
      Serial.print("YOU LOSE");
      Serial.println();
    }
  }
  gameOver = true;
    
}

