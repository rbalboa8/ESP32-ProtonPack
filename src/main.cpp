#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN 18        // GPIO 18 for LED data line
#define SWITCH_PIN 17     // GPIO 17 for the toggle switch to control direction
#define MODE_PIN 16       // GPIO 16 for the toggle switch to select animation mode
#define NUM_LEDS 40
#define BRIGHTNESS 255
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

// Cyclotron light parameters for 1984 mode
int cyclotronLights[4][2] = {
    {0, 5},    // Starting position and length of the first light
    {10, 5},   // Second light
    {20, 5},   // Third light
    {30, 5}    // Fourth light
};

int fadeDuration = 1000; // Fade up and down duration in milliseconds
int gapDuration = 0;     // Gap between lights in milliseconds

enum CyclotronDirection { Clockwise, AntiClockwise };
CyclotronDirection direction = Clockwise; // Initial direction

enum AnimationMode { Mode1984, ModeAfterlife };
AnimationMode animationMode = Mode1984; // Default mode

int afterlifeLedCount = 4; // Default number of LEDs in the chase for Afterlife mode
int maxBrightness = 255;
int minBrightness = 1; // Default minimum brightness set to 1
int chaseSpeed = 4;    // Default chase speed in milliseconds per step (1 to 255, lower values are faster, higher values are slower)

// Function declarations
void run1984Animation();
void runAfterlifeAnimation();

unsigned long previousMillis = 0;
int currentLight = 0;
int fadeDirection = 1;
int fadeValue = 0;

void setup() {
    pinMode(SWITCH_PIN, INPUT_PULLUP); // Set up the direction switch pin with internal pull-up resistor
    pinMode(MODE_PIN, INPUT_PULLUP);   // Set up the mode switch pin with internal pull-up resistor

    // Read the mode switch at startup to set the animation mode
    if (digitalRead(MODE_PIN) == LOW) {
        animationMode = ModeAfterlife;
    } else {
        animationMode = Mode1984;
    }

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
    // Read the direction switch state
    if (digitalRead(SWITCH_PIN) == LOW) {
        direction = AntiClockwise;
    } else {
        direction = Clockwise;
    }

    if (animationMode == Mode1984) {
        run1984Animation();
    } else if (animationMode == ModeAfterlife) {
        runAfterlifeAnimation();
    }

    FastLED.show();
}

// Function to run the 1984 animation
void run1984Animation() {
    unsigned long currentMillis = millis();
    static unsigned long lastUpdate = 0;

    // Calculate fade value
    int delta = (fadeDuration / 256);
    if (currentMillis - lastUpdate > delta) {
        lastUpdate = currentMillis;
        fadeValue += fadeDirection;

        // Reverse fade direction at the end points
        if (fadeValue >= 255 || fadeValue <= 0) {
            fadeDirection *= -1;
            if (fadeValue <= 0) {
                // Move to the next light in the sequence
                if (direction == Clockwise) {
                    currentLight = (currentLight + 1) % 4;
                } else {
                    currentLight = (currentLight - 1 + 4) % 4;
                }
                if (currentLight == 0 && gapDuration > 0) {
                    delay(gapDuration); // Only delay if gapDuration is greater than 0
                }
            }
        }
    }

    // Set LEDs for the current light
    for (int i = 0; i < 4; i++) {
        int startPos = cyclotronLights[i][0];
        int length = cyclotronLights[i][1];
        for (int j = startPos; j < startPos + length; j++) {
            if (i == currentLight) {
                leds[j] = CRGB::Red;
                leds[j].fadeToBlackBy(255 - fadeValue);
            } else {
                leds[j] = CRGB::Black;
            }
        }
    }
}

// Function to run the Afterlife animation
void runAfterlifeAnimation() {
    unsigned long currentMillis = millis();
    static unsigned long lastUpdate = 0;
    static int headPos = 0;

    // Update the head position for the chase effect
    if (currentMillis - lastUpdate > chaseSpeed) {
        lastUpdate = currentMillis;

        if (direction == Clockwise) {
            headPos = (headPos + 1) % NUM_LEDS;
        } else {
            headPos = (headPos - 1 + NUM_LEDS) % NUM_LEDS;
        }
    }

    // Set all LEDs to black
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }

    // Illuminate LEDs based on the chase effect
    for (int i = 0; i < afterlifeLedCount; i++) {
        int pos;
        if (direction == Clockwise) {
            pos = (headPos - i + NUM_LEDS) % NUM_LEDS;
        } else {
            pos = (headPos + i + NUM_LEDS) % NUM_LEDS;
        }
        int brightness = maxBrightness - ((maxBrightness - minBrightness) / afterlifeLedCount) * i;
        leds[pos] = CRGB::Red;
        leds[pos].fadeLightBy(255 - brightness);
    }
}
