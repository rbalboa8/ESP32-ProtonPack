# User Guide

## Introduction

This user guide provides instructions on how to use the Proton Pack project, including how to select different modes and control the LED animations.

## Components

- ESP32-S3 DevKitC
- WS2812B LED strip or ring
- Four toggle switches

## Setup

1. **Power on the device**:
    - Connect the ESP32-S3 to a power source.

2. **Mode Selection**:
    - Use the voltage divider connected to GPIO 17 to select the animation mode:
        - **1984 Pack Mode**: Voltage range 0V to ~1.1V
        - **Afterlife Pack Mode**: Voltage range ~1.1V to ~2.2V
        - **Frozen Empire Pack Mode**: Voltage range ~2.2V to 3.3V

3. **Direction Control**:
    - Use the direction toggle switch (connected to GPIO 15) to control the direction of the animation:
        - **Clockwise**: Switch HIGH
        - **AntiClockwise**: Switch LOW

4. **Cyclotron Lid State**:
    - Use the Cyclotron Lid state toggle switch (connected to GPIO 14) to switch between the Cyclotron Cake lights and the Cyclotron Lid lights:
        - **Cyclotron Lid On**: Switch LOW
        - **Cyclotron Lid Off**: Switch HIGH

## Animation Modes

### 1984 Pack Mode

- LEDs fade up and down in a sequential pattern.
- Adjust the fade duration and gap duration in `main.cpp`:
    ```cpp
    int EightyFourVersionLightsFadeDuration = 1000; // Duration for fade up and down in milliseconds
    int EightyFourVersionLightsGapDuration = 0;     // Duration for gap between lights in milliseconds
    ```

### Afterlife Pack Mode

- LEDs chase around the ring with a defined number of LEDs.
- Adjust the LED count and chase speed in `main.cpp`:
    ```cpp
    int afterlifeLedCount = 4; // Number of LEDs in the chase
    int chaseSpeed = 4;        // Chase speed in milliseconds per step
    ```

### Frozen Empire Pack Mode

- LEDs create a spark effect with a user-defined color.
- Adjust the LED count, chase speed, and color in `main.cpp`:
    ```cpp
    int frozenEmpireLedCount = 8; // Number of LEDs in the chase
    int frozenEmpireChaseSpeed = 8; // Chase speed in milliseconds per step
    CRGB frozenEmpireColor = CRGB::White; // Color for the sparks
    ```

## OTA Updates

1. **Connect to Wi-Fi**:
    - Ensure the ESP32-S3 is connected to a Wi-Fi network using the credentials in `secrets.h`.

2. **Perform OTA Update**:
    - Use the Arduino IDE or PlatformIO to perform an OTA update:
        - In Arduino IDE: Go to `Sketch` > `Upload Using OTA`.
        - In PlatformIO: Use the `Upload` button or run the `platformio run --target upload --upload-port IP_ADDRESS` command.

## Conclusion

You should now be able to use and control your Proton Pack project. For any issues or troubleshooting, refer to the configuration guide or consult the project documentation on GitHub.
