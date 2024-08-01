# Configuration Guide

## Introduction

This guide provides instructions on how to configure the Proton Pack project. The project is built using an ESP32-S3 and FastLED library to control WS2812B LEDs. The project also includes OTA (Over-the-Air) updates for easy firmware updates.

## Prerequisites

- Arduino IDE or PlatformIO with VS Code
- ESP32-S3 DevKitC
- WS2812B LED strip or ring
- Four toggle switches
- Wi-Fi network for OTA updates

## Configuration Steps

1. **Clone the repository**:
    ```sh
    git clone https://github.com/yourusername/proton-pack.git
    cd proton-pack
    ```

2. **Install dependencies**:
    - Install the FastLED library in your Arduino IDE or PlatformIO.

3. **Edit `secrets.h`**:
    - Create a file named `secrets.h` in the `include` directory.
    - Add your Wi-Fi SSID and password:
        ```cpp
        #define ssid "your-SSID"
        #define password "your-PASSWORD"
        #define otaPassword "your-OTA-PASSWORD"
        ```

4. **Edit `platformio.ini`** (if using PlatformIO):
    ```ini
    [env:esp32dev]
    platform = espressif32
    board = esp32-s3-devkitc-1
    framework = arduino
    upload_port = COM3  # Change to your actual port
    monitor_speed = 115200

    build_flags =
      -DSSID=\"${ssid}\"
      -DPASSWORD=\"${password}\"
      -DOTA_PASSWORD=\"${otaPassword}\"
    ```

5. **Configure pins**:
    - Edit the pin definitions in `main.cpp` if necessary:
        ```cpp
        #define CYCLOTRON_CAKE_LED_PIN 19     // GPIO for the first LED ring data line
        #define CYCLOTRON_LID_LED_PIN 18      // GPIO for the second LED ring data line
        #define CYCLOTRON_DIRECTION_SWITCH_PIN 15 // GPIO for direction toggle switch
        #define LID_STATE_PIN 14              // GPIO for cyclotron lid state toggle switch
        #define MODE_SELECT_PIN 17            // GPIO for mode selection voltage divider
        ```

6. **Customize LED settings**:
    - Adjust the number of LEDs and animation settings in `main.cpp`:
        ```cpp
        int afterlifeLedCount = 4; // Number of LEDs in the chase for Afterlife mode
        int frozenEmpireLedCount = 8; // Number of LEDs in the chase for Frozen Empire mode
        int chaseSpeed = 4; // Chase speed for Afterlife mode in milliseconds per step
        int frozenEmpireChaseSpeed = 8; // Chase speed for Frozen Empire mode in milliseconds per step
        CRGB frozenEmpireColor = CRGB::White; // Color for Frozen Empire mode
        ```

7. **Build and upload the firmware**:
    - Using Arduino IDE or PlatformIO, compile and upload the firmware to your ESP32-S3.

## Conclusion

Your Proton Pack project should now be configured and ready to use. Refer to the user guide for detailed usage instructions.
