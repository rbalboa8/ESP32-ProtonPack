#include <Arduino.h>
#include <FastLED.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include "secrets.h" // Include the secrets file for Wi-Fi and OTA credentials

// Pin definitions
#define CYCLOTRON_CAKE_LED_PIN 19    // GPIO 19 for the first LED ring data line
#define CYCLOTRON_LID_LED_PIN 18     // GPIO 18 for the second LED ring data line
#define CYCLOTRON_DIRECTION_SWITCH_PIN 15 // GPIO 15 for the toggle switch to control direction
#define SWITCH1_PIN 16               // GPIO 16 for the first toggle switch
#define SWITCH2_PIN 17               // GPIO 17 for the second toggle switch
#define LID_STATE_PIN 14             // GPIO 14 for the toggle switch to control cyclotron lid state

#define NUM_LEDS_CYCLOTRON_CAKE 45   // Total number of LEDs for the first ring
#define NUM_LEDS_CYCLOTRON_LID 40    // Total number of LEDs for the second ring
#define BRIGHTNESS 255               // Maximum brightness of LEDs
#define LED_TYPE WS2812B             // Type of LED strip
#define COLOR_ORDER GRB              // Color order of the LED strip

CRGB cyclotronCakeLights[NUM_LEDS_CYCLOTRON_CAKE]; // First LED ring
CRGB cyclotronLidLights[NUM_LEDS_CYCLOTRON_LID];   // Second LED ring

// Cyclotron light parameters for the first LED ring (1984 mode)
int cyclotronCakeLightsSpacingConfig[4][2] = {
    {0, 5},    // Starting position and length of the first light
    {11, 5},   // Second light
    {21, 5},   // Third light
    {31, 5}    // Fourth light
};

// Cyclotron light parameters for the second LED ring (1984 mode)
int cyclotronLidLightsSpacingConfig[4][2] = {
    {0, 5},    // Starting position and length of the first light
    {10, 5},   // Second light
    {20, 5},   // Third light
    {30, 5}    // Fourth light
};

int EightyFourVersionLightsFadeDuration = 1000; // Duration for fade up and down in milliseconds
int EightyFourVersionLightsGapDuration = 0;     // Duration for gap between lights in milliseconds

// Enum for cyclotron direction
enum CyclotronDirection { Clockwise, AntiClockwise };
CyclotronDirection direction = Clockwise; // Initial direction

// Enum for animation modes
enum AnimationMode { Mode1984, ModeAfterlife, ModeFrozenEmpire };
AnimationMode animationMode = Mode1984; // Default animation mode

// Enum for cyclotron lid state
enum CyclotronLidState { CyclotronLidOn, CyclotronLidOff };
CyclotronLidState lidState = CyclotronLidOff; // Initial state
CyclotronLidState previousLidState = CyclotronLidOff; // Track the previous state

// User-defined variables for Afterlife and Frozen Empire modes
int afterlifeLedCount = 4;              // Number of LEDs in the chase for Afterlife mode
int maxBrightness = 255;                // Maximum brightness
int minBrightness = 1;                  // Default minimum brightness set to 1
int chaseSpeed = 4;                     // Default chase speed in milliseconds per step (1 to 255, lower values are faster, higher values are slower)

int frozenEmpireLedCount = 8;           // Default number of LEDs in the chase for Frozen Empire mode
int frozenEmpireMinBrightness = 5;      // Default minimum brightness for Frozen Empire mode
int frozenEmpireChaseSpeed = 8;         // Default chase speed for Frozen Empire mode (double the afterlife speed)
CRGB frozenEmpireColor = CRGB::White;   // Default color for Frozen Empire mode

const int maxRetries = 5; // Maximum number of retries for Wi-Fi connection
int connectionAttempts = 0;
bool shouldAttemptConnection = true;

unsigned long previousMillis = 0;
const long interval = 60000; // 60 seconds interval for retrying Wi-Fi connection

unsigned long lastUpdate = 0;
int currentLight = 0;
int fadeDirection = 1;
int fadeValue = 0;

// Function declarations
void connectToWiFi();
void setupOTA();
void run1984Animation(CRGB* leds, int numLeds, int lightsConfig[][2]);
void runAfterlifeAnimation(CRGB* leds, int numLeds);
void runFrozenEmpireAnimation(CRGB* leds, int numLeds);
void runMainFunctions();
void updateLidState();
void clearLEDs(CRGB* leds, int numLeds);

void setup() {
    // Serial.begin(115200); // Commented out for now

    // Set up the direction switch pin with internal pull-up resistor
    pinMode(CYCLOTRON_DIRECTION_SWITCH_PIN, INPUT_PULLUP);
    // Set up the mode switch pins with internal pull-up resistor
    pinMode(SWITCH1_PIN, INPUT_PULLUP);
    pinMode(SWITCH2_PIN, INPUT_PULLUP);
    // Set up the lid state switch pin with internal pull-up resistor
    pinMode(LID_STATE_PIN, INPUT_PULLUP);

    // Read the switch states at startup to set the animation mode
    bool switch1State = digitalRead(SWITCH1_PIN);
    bool switch2State = digitalRead(SWITCH2_PIN);

    if (!switch1State && !switch2State) {
        animationMode = Mode1984; // Both switches OFF
    } else if (switch1State && !switch2State) {
        animationMode = ModeAfterlife; // Switch 1 ON, Switch 2 OFF
    } else if (!switch1State && switch2State) {
        animationMode = ModeFrozenEmpire; // Switch 1 OFF, Switch 2 ON
    }

    // Initialize FastLED
    FastLED.addLeds<LED_TYPE, CYCLOTRON_CAKE_LED_PIN, COLOR_ORDER>(cyclotronCakeLights, NUM_LEDS_CYCLOTRON_CAKE).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE, CYCLOTRON_LID_LED_PIN, COLOR_ORDER>(cyclotronLidLights, NUM_LEDS_CYCLOTRON_LID).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    // Connect to Wi-Fi and setup OTA
    connectToWiFi();
    setupOTA();
}

void loop() {
    // Read the direction switch state
    if (digitalRead(CYCLOTRON_DIRECTION_SWITCH_PIN) == LOW) {
        direction = AntiClockwise; // Switch LOW: AntiClockwise
    } else {
        direction = Clockwise; // Switch HIGH: Clockwise
    }

    // Update lid state in real time
    updateLidState();

    unsigned long currentMillis = millis();

    // Attempt to reconnect to Wi-Fi if disconnected and retry attempts are allowed
    if (WiFi.status() != WL_CONNECTED && shouldAttemptConnection) {
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            connectToWiFi();
        }
    } else if (WiFi.status() == WL_CONNECTED) {
        ArduinoOTA.handle(); // Handle OTA only when Wi-Fi is connected
    }

    // Run the selected animation
    runMainFunctions();
}

void connectToWiFi() {
    if (connectionAttempts >= maxRetries) {
        // Serial.println("Max retries reached. Stopping further connection attempts."); // Commented out for now
        shouldAttemptConnection = false;
        return;
    }

    // Serial.print("Connecting to WiFi... Attempt "); // Commented out for now
    // Serial.println(connectionAttempts + 1); // Commented out for now
    WiFi.begin(ssid, password);

    unsigned long startAttemptTime = millis();

    // Attempt to connect for 10 seconds
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
        delay(500);
        // Serial.print("."); // Commented out for now
    }

    if (WiFi.status() == WL_CONNECTED) {
        // Serial.println("\nConnected to WiFi"); // Commented out for now
        // Serial.print("IP address: "); // Commented out for now
        // Serial.println(WiFi.localIP()); // Commented out for now
        connectionAttempts = 0; // Reset attempts on successful connection
    } else {
        // Serial.println("\nFailed to connect to WiFi"); // Commented out for now
        connectionAttempts++;
    }
}

void setupOTA() {
    // Set OTA password
    ArduinoOTA.setPassword(otaPassword);

    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
            type = "sketch";
        } else { // U_SPIFFS
            type = "filesystem";
        }
        // Serial.println("Start updating " + type); // Commented out for now
    });

    ArduinoOTA.onEnd([]() {
        // Serial.println("\nEnd"); // Commented out for now
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        // Serial.printf("Progress: %u%%\r", (progress / (total / 100))); // Commented out for now
    });

    ArduinoOTA.onError([](ota_error_t error) {
        // Serial.printf("Error[%u]: ", error); // Commented out for now
        if (error == OTA_AUTH_ERROR) {
            // Serial.println("Auth Failed"); // Commented out for now
        } else if (error == OTA_BEGIN_ERROR) {
            // Serial.println("Begin Failed"); // Commented out for now
        } else if (error == OTA_CONNECT_ERROR) {
            // Serial.println("Connect Failed"); // Commented out for now
        } else if (error == OTA_RECEIVE_ERROR) {
            // Serial.println("Receive Failed"); // Commented out for now
        } else if (error == OTA_END_ERROR) {
            // Serial.println("End Failed"); // Commented out for now
        }
    });

    ArduinoOTA.begin();
}

void updateLidState() {
    CyclotronLidState newLidState;
    
    // Update the lid state based on the real-time pin reading
    if (digitalRead(LID_STATE_PIN) == LOW) {
        newLidState = CyclotronLidOn; // Switch LOW: CyclotronLidOn
        // Serial.println("CyclotronLidState: ON"); // Commented out for now
    } else {
        newLidState = CyclotronLidOff; // Switch HIGH: CyclotronLidOff
        // Serial.println("CyclotronLidState: OFF"); // Commented out for now
    }

    if (newLidState != lidState) {
        previousLidState = lidState;
        lidState = newLidState;
        clearLEDs((previousLidState == CyclotronLidOn) ? cyclotronCakeLights : cyclotronLidLights, (previousLidState == CyclotronLidOn) ? NUM_LEDS_CYCLOTRON_CAKE : NUM_LEDS_CYCLOTRON_LID);
    }
}

void runMainFunctions() {
    if (animationMode == Mode1984) {
        run1984Animation((lidState == CyclotronLidOn) ? cyclotronCakeLights : cyclotronLidLights, (lidState == CyclotronLidOn) ? NUM_LEDS_CYCLOTRON_CAKE : NUM_LEDS_CYCLOTRON_LID, (lidState == CyclotronLidOn) ? cyclotronCakeLightsSpacingConfig : cyclotronLidLightsSpacingConfig);
    } else if (animationMode == ModeAfterlife) {
        runAfterlifeAnimation((lidState == CyclotronLidOn) ? cyclotronCakeLights : cyclotronLidLights, (lidState == CyclotronLidOn) ? NUM_LEDS_CYCLOTRON_CAKE : NUM_LEDS_CYCLOTRON_LID);
    } else if (animationMode == ModeFrozenEmpire) {
        runFrozenEmpireAnimation((lidState == CyclotronLidOn) ? cyclotronCakeLights : cyclotronLidLights, (lidState == CyclotronLidOn) ? NUM_LEDS_CYCLOTRON_CAKE : NUM_LEDS_CYCLOTRON_LID);
    }

    FastLED.show();
}

void run1984Animation(CRGB* leds, int numLeds, int lightsConfig[][2]) {
    unsigned long currentMillis = millis();

    // Calculate fade value
    int delta = (EightyFourVersionLightsFadeDuration / 256);
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
                if (currentLight == 0 && EightyFourVersionLightsGapDuration > 0) {
                    delay(EightyFourVersionLightsGapDuration); // Only delay if EightyFourVersionLightsGapDuration is greater than 0
                }
            }
        }
    }

    // Set LEDs for the current light
    for (int i = 0; i < 4; i++) {
        int startPos = lightsConfig[i][0];
        int length = lightsConfig[i][1];
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

void runAfterlifeAnimation(CRGB* leds, int numLeds) {
    unsigned long currentMillis = millis();
    static unsigned long lastUpdate = 0;
    static int headPos = 0;

    // Update the head position for the chase effect
    if (currentMillis - lastUpdate > chaseSpeed) {
        lastUpdate = currentMillis;

        if (direction == Clockwise) {
            headPos = (headPos + 1) % numLeds;
        } else {
            headPos = (headPos - 1 + numLeds) % numLeds;
        }
    }

    // Set all LEDs to black
    for (int i = 0; i < numLeds; i++) {
        leds[i] = CRGB::Black;
    }

    // Illuminate LEDs based on the chase effect
    for (int i = 0; i < afterlifeLedCount; i++) {
        int pos;
        if (direction == Clockwise) {
            pos = (headPos - i + numLeds) % numLeds;
        } else {
            pos = (headPos + i + numLeds) % numLeds;
        }
        int brightness = maxBrightness - ((maxBrightness - minBrightness) / afterlifeLedCount) * i;
        leds[pos] = CRGB::Red;
        leds[pos].fadeLightBy(255 - brightness);
    }
}

void runFrozenEmpireAnimation(CRGB* leds, int numLeds) {
    unsigned long currentMillis = millis();
    static unsigned long lastUpdate = 0;
    static int headPos = 0;

    // Update the head position for the chase effect
    if (currentMillis - lastUpdate > frozenEmpireChaseSpeed) {
        lastUpdate = currentMillis;

        if (direction == Clockwise) {
            headPos = (headPos + 1) % numLeds;
        } else {
            headPos = (headPos - 1 + numLeds) % numLeds;
        }
    }

    // Set all LEDs to black
    for (int i = 0; i < numLeds; i++) {
        leds[i] = CRGB::Black;
    }

    // Illuminate LEDs based on the chase effect
    for (int i = 0; i < frozenEmpireLedCount; i++) {
        int pos;
        if (direction == Clockwise) {
            pos = (headPos - i + numLeds) % numLeds;
        } else {
            pos = (headPos + i + numLeds) % numLeds;
        }

        // Calculate the brightness based on the distance from the center
        int centerIndex = frozenEmpireLedCount / 2;
        int distanceFromCenter = abs(i - centerIndex);
        int brightness = maxBrightness - ((maxBrightness - frozenEmpireMinBrightness) / centerIndex) * distanceFromCenter;

        // Use user-defined color for sparks effect
        leds[pos] = frozenEmpireColor;
        leds[pos].fadeLightBy(255 - brightness);
    }
}

void clearLEDs(CRGB* leds, int numLeds) {
    for (int i = 0; i < numLeds; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.show();
}
