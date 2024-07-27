# Wiring Guide

This document provides the wiring instructions for the Ghostbusters Proton Pack project.

## Components

- ESP32-S3 microcontroller
- WS2812B LED strip (40 LEDs)
- Toggle switches (2)
- Resistors (for pull-up configuration)

## Wiring Diagram

| ESP32-S3 Pin | Component                        |
|--------------|----------------------------------|
| GPIO 18      | Data line of LED strip           |
| GPIO 17      | Direction toggle switch (Pull-up resistor) |
| GPIO 16      | Mode toggle switch (Pull-up resistor) |

### Connections

1. **LED Strip**:
    - Connect the data line of the WS2812B LED strip to GPIO 18.
    - Connect the power (5V) and ground (GND) lines of the LED strip to the appropriate pins on the ESP32-S3.

2. **Direction Toggle Switch**:
    - Connect one terminal of the toggle switch to GPIO 17.
    - Connect the other terminal to ground (GND).
    - Use a pull-up resistor (10kΩ) between GPIO 17 and 3.3V.

3. **Mode Toggle Switch**:
    - Connect one terminal of the toggle switch to GPIO 16.
    - Connect the other terminal to ground (GND).
    - Use a pull-up resistor (10kΩ) between GPIO 16 and 3.3V.

## Diagram

![Wiring Diagram](path-to-your-wiring-diagram-image)

Ensure all connections are secure before powering up the ESP32-S3.

