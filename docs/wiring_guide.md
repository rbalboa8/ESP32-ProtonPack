# Wiring Guide

## Introduction

This guide provides wiring instructions for setting up the Proton Pack project with the ESP32-S3 and WS2812B LEDs.

## Components

- ESP32-S3 DevKitC
- WS2812B LED strip or ring
- Three toggle switches
- Breadboard and jumper wires (optional)

## Wiring Diagram

### Connections

1. **WS2812B LED Strip/Ring**:
    - **Data In**: Connect to GPIO 18 on the ESP32-S3.
    - **5V**: Connect to a 5V power source (ensure it shares a common ground with the ESP32-S3).
    - **GND**: Connect to the ground (GND) on the ESP32-S3.

2. **Direction Toggle Switch**:
    - **One side**: Connect to GPIO 15 on the ESP32-S3.
    - **Other side**: Connect to GND.
    - **Pull-up resistor**: Use the internal pull-up resistor by setting the pin mode to `INPUT_PULLUP` in the code.

3. **Mode Toggle Switch 1**:
    - **One side**: Connect to GPIO 16 on the ESP32-S3.
    - **Other side**: Connect to GND.
    - **Pull-up resistor**: Use the internal pull-up resistor by setting the pin mode to `INPUT_PULLUP` in the code.

4. **Mode Toggle Switch 2**:
    - **One side**: Connect to GPIO 17 on the ESP32-S3.
    - **Other side**: Connect to GND.
    - **Pull-up resistor**: Use the internal pull-up resistor by setting the pin mode to `INPUT_PULLUP` in the code.

### Detailed Wiring Steps

1. **Connect the LED Strip/Ring**:
    - Solder or connect the data line from the LED strip/ring to GPIO 18 on the ESP32-S3.
    - Connect the power line to a 5V source.
    - Connect the ground line to the GND on the ESP32-S3.

2. **Connect the Direction Toggle Switch**:
    - Connect one side of the switch to GPIO 15.
    - Connect the other side to GND.
    - Use the internal pull-up resistor in your code:
        ```cpp
        pinMode(SWITCH_PIN, INPUT_PULLUP);
        ```

3. **Connect Mode Toggle Switch 1**:
    - Connect one side of the switch to GPIO 16.
    - Connect the other side to GND.
    - Use the internal pull-up resistor in your code:
        ```cpp
        pinMode(SWITCH1_PIN, INPUT_PULLUP);
        ```

4. **Connect Mode Toggle Switch 2**:
    - Connect one side of the switch to GPIO 17.
    - Connect the other side to GND.
    - Use the internal pull-up resistor in your code:
        ```cpp
        pinMode(SWITCH2_PIN, INPUT_PULLUP);
        ```

### Wiring Diagram

```plaintext
ESP32-S3 DevKitC       WS2812B LED Strip/Ring
+--------------+       +----------------------+
|              |       |                      |
|           5V +-------+ 5V                   |
|          GND +-------+ GND                  |
|         GPIO18 +-----+ Data In              |
|              |       |                      |
|              |       |                      |
+--------------+       +----------------------+

ESP32-S3 DevKitC       Direction Toggle Switch
+--------------+       +----------------------+
|              |       |                      |
|        GPIO15 +-----+ One side              |
|          GND  +-----+ Other side            |
|              |       |                      |
+--------------+       +----------------------+

ESP32-S3 DevKitC       Mode Toggle Switch 1
+--------------+       +----------------------+
|              |       |                      |
|        GPIO16 +-----+ One side              |
|          GND  +-----+ Other side            |
|              |       |                      |
+--------------+       +----------------------+

ESP32-S3 DevKitC       Mode Toggle Switch 2
+--------------+       +----------------------+
|              |       |                      |
|        GPIO17 +-----+ One side              |
|          GND  +-----+ Other side            |
|              |       |                      |
+--------------+       +----------------------+
