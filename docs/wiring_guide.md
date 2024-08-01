# Wiring Guide

## Introduction

This guide provides wiring instructions for setting up the Proton Pack project with the ESP32-S3 and WS2812B LEDs.

## Components

- ESP32-S3 DevKitC
- WS2812B LED strip or ring
- Four toggle switches
- Breadboard and jumper wires (optional)

## Wiring Diagram

### Connections

1. **WS2812B LED Strip/Ring 1 (Cyclotron Cake Lights)**:
    - **Data In**: Connect to GPIO 19 on the ESP32-S3.
    - **5V**: Connect to a 5V power source (ensure it shares a common ground with the ESP32-S3).
    - **GND**: Connect to the ground (GND) on the ESP32-S3.

2. **WS2812B LED Strip/Ring 2 (Cyclotron Lid Lights)**:
    - **Data In**: Connect to GPIO 18 on the ESP32-S3.
    - **5V**: Connect to a 5V power source (ensure it shares a common ground with the ESP32-S3).
    - **GND**: Connect to the ground (GND) on the ESP32-S3.

3. **Direction Toggle Switch**:
    - **One side**: Connect to GPIO 15 on the ESP32-S3.
    - **Other side**: Connect to GND.
    - **Pull-up resistor**: Use the internal pull-up resistor by setting the pin mode to `INPUT_PULLUP` in the code.

4. **Lid State Toggle Switch**:
    - **One side**: Connect to GPIO 14 on the ESP32-S3.
    - **Other side**: Connect to GND.
    - **Pull-up resistor**: Use the internal pull-up resistor by setting the pin mode to `INPUT_PULLUP` in the code.

5. **Mode Selection with Voltage Divider**:
    - **Voltage Divider Output**: Connect to GPIO 17 on the ESP32-S3.
    - **Resistors**: Connect a voltage divider circuit with resistors to divide the voltage from 3.3V to 0V.

### Detailed Wiring Steps

1. **Connect the First LED Strip/Ring (Cyclotron Cake Lights)**:
    - Solder or connect the data line from the LED strip/ring to GPIO 19 on the ESP32-S3.
    - Connect the power line to a 5V source.
    - Connect the ground line to the GND on the ESP32-S3.

2. **Connect the Second LED Strip/Ring (Cyclotron Lid Lights)**:
    - Solder or connect the data line from the LED strip/ring to GPIO 18 on the ESP32-S3.
    - Connect the power line to a 5V source.
    - Connect the ground line to the GND on the ESP32-S3.

3. **Connect the Direction Toggle Switch**:
    - Connect one side of the switch to GPIO 15.
    - Connect the other side to GND.
    - Use the internal pull-up resistor in your code:
        ```cpp
        pinMode(CYCLOTRON_DIRECTION_SWITCH_PIN, INPUT_PULLUP);
        ```

4. **Connect the Lid State Toggle Switch**:
    - Connect one side of the switch to GPIO 14.
    - Connect the other side to GND.
    - Use the internal pull-up resistor in your code:
        ```cpp
        pinMode(LID_STATE_PIN, INPUT_PULLUP);
        ```

5. **Connect the Voltage Divider for Mode Selection**:
    - Connect the voltage divider circuit to the analog input pin GPIO 17.
    - Ensure the voltage divider provides a range of voltages between 0V and 3.3V to the pin.

### Wiring Diagram

```plaintext
ESP32-S3 DevKitC       WS2812B LED Strip/Ring 1 (Cyclotron Cake Lights)
+--------------+       +----------------------+
|              |       |                      |
|           5V +-------+ 5V                   |
|          GND +-------+ GND                  |
|         GPIO19 +-----+ Data In              |
|              |       |                      |
|              |       |                      |
+--------------+       +----------------------+

ESP32-S3 DevKitC       WS2812B LED Strip/Ring 2 (Cyclotron Lid Lights)
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

ESP32-S3 DevKitC       Lid State Toggle Switch
+--------------+       +----------------------+
|              |       |                      |
|        GPIO14 +-----+ One side              |
|          GND  +-----+ Other side            |
|              |       |                      |
+--------------+       +----------------------+

ESP32-S3 DevKitC       Mode Selection with Voltage Divider
+--------------+       +----------------------+
|              |       |                      |
|        GPIO17 +-----+ Voltage Divider Output|
|              |       |                      |
+--------------+       +----------------------+
