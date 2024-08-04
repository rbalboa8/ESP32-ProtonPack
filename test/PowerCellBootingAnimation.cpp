#include <Arduino.h>
#include <FastLED.h>

#define CYCLOTRON_CAKE_LED_PIN 19    // GPIO 19 for the LED ring data line
// User-definable number of LEDs
#define NUM_LEDS_POWERCELL 16
#define NUM_LEDS_CYCLOTRON_CAKE 45   // Total number of LEDs for the first ring excluding the power cell
#define LED_PIN 38
#define BRIGHTNESS 64
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
CRGB cyclotronCakeLights[NUM_LEDS_CYCLOTRON_CAKE + NUM_LEDS_POWERCELL]; // First LED ring + power cell

// User-definable total animation time in milliseconds
#define TOTAL_ANIMATION_TIME 5000

// Calculate the interval for each LED based on the total animation time and the number of steps needed
const long interval = TOTAL_ANIMATION_TIME / ((NUM_LEDS_POWERCELL * (NUM_LEDS_POWERCELL + 1)) / 2);

unsigned long previousMillis = 0;

int currentLED = 0;
int fullLEDs = 0;

// Function declarations
void ledAnimation();
void otherFunction();

void setup() {
  // Initialize the FastLED library
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS_POWERCELL).setCorrection(TypicalLEDStrip);
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
    fill_solid(leds, NUM_LEDS_POWERCELL, CRGB::Black);

    // Keep all full LEDs on
    for (int i = 0; i < fullLEDs; i++) {
      leds[i] = CRGB::Blue;
    }

    // Turn on the current LED if it is not at the full position
    if (currentLED < NUM_LEDS_POWERCELL - fullLEDs) {
      leds[NUM_LEDS_POWERCELL - currentLED - 1] = CRGB::Blue;
    }

    FastLED.show();

    // Move to the next LED
    currentLED++;
    if (currentLED >= NUM_LEDS_POWERCELL - fullLEDs) {
      // Mark the current LED as full and unusable
      fullLEDs++;
      currentLED = 0; // Restart the traveling LED
    }
  }
}

void otherFunction() {
  // Add other code here that you want to run simultaneously
}
