#include <FastLED.h>

#define LED_PIN     38
#define NUM_LEDS    5
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void setup() {
  // Initialize the FastLED library
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  // Run the LED animation
  ledAnimation();
}

void ledAnimation() {
  // Define the delay time between states (in milliseconds)
  const int delayTime = 500;

  // Turn off all LEDs initially
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(delayTime);

  // Turn on LEDs one by one from left to right
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;
    FastLED.show();
    delay(delayTime);
    leds[i] = CRGB::Black;
  }
}
