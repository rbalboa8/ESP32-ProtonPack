#include <FastLED.h>

// User-definable number of LEDs
#define NUM_LEDS 16
#define LED_PIN 38
#define BRIGHTNESS 64
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

// User-definable total animation time in milliseconds
#define TOTAL_ANIMATION_TIME 5000

// Calculate the interval for each LED based on the total animation time and the number of steps needed
const long interval = TOTAL_ANIMATION_TIME / ((NUM_LEDS * (NUM_LEDS + 1)) / 2);

unsigned long previousMillis = 0;

int currentLED = 0;
int fullLEDs = 0;

// Function declarations
void ledAnimation();
void otherFunction();

void setup() {
  // Initialize the FastLED library
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  // Run the LED animation
  ledAnimation();

  // Run other functions simultaneously
  otherFunction();
}

void ledAnimation() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Turn off all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    // Keep all full LEDs on
    for (int i = 0; i < fullLEDs; i++) {
      leds[i] = CRGB::Blue;
    }

    // Turn on the current LED if it is not at the full position
    if (currentLED < NUM_LEDS - fullLEDs) {
      leds[NUM_LEDS - currentLED - 1] = CRGB::Blue;
    }

    FastLED.show();

    // Move to the next LED
    currentLED++;
    if (currentLED >= NUM_LEDS - fullLEDs) {
      // Mark the current LED as full and unusable
      fullLEDs++;
      currentLED = 0; // Restart the traveling LED
    }
  }
}

void otherFunction() {
  // Add other code here that you want to run simultaneously
}
