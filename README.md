# Ghostbusters Proton Pack Project

## Overview

This project aims to create a movie-accurate Ghostbusters Proton Pack using an ESP32-S3 microcontroller and WS2812B LEDs. The pack features multiple animation modes inspired by different Ghostbusters movies and includes Over-the-Air (OTA) updates for easy firmware updates.

## Features

- **1984 Pack Mode**: Classic cyclotron lights animation.
- **Afterlife Pack Mode**: LED chase animation.
- **Frozen Empire Pack Mode**: Spark effect animation with customizable colors.
- **Direction Control**: Toggle switch to change the direction of the animations.
- **OTA Updates**: Easily update the firmware over Wi-Fi.

## Getting Started

### Prerequisites

- ESP32-S3 DevKitC
- WS2812B LED strip or ring
- Three toggle switches
- Arduino IDE or PlatformIO with VS Code
- Wi-Fi network for OTA updates

### Hardware Setup

1. **Connect the WS2812B LEDs**:
    - **Data In**: Connect to GPIO 18 on the ESP32-S3.
    - **5V**: Connect to a 5V power source.
    - **GND**: Connect to the ground (GND) on the ESP32-S3.

2. **Connect the Direction Toggle Switch**:
    - **One side**: Connect to GPIO 15.
    - **Other side**: Connect to GND.

3. **Connect the Mode Toggle Switches**:
    - **Switch 1**: Connect to GPIO 16 and GND.
    - **Switch 2**: Connect to GPIO 17 and GND.

### Software Setup

1. **Clone the repository**:
    ```sh
    git clone https://github.com/yourusername/proton-pack.git
    cd proton-pack
    ```

2. **Install dependencies**:
    - Install the FastLED library in your Arduino IDE or PlatformIO.

3. **Edit `secrets.h`**:
    - Create a file named `secrets.h` in the `include` directory.
    - Add your Wi-Fi SSID, password, and OTA password:
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

5. **Build and upload the firmware**:
    - Using Arduino IDE or PlatformIO, compile and upload the firmware to your ESP32-S3.

## Usage

1. **Power on the device**:
    - Connect the ESP32-S3 to a power source.

2. **Select Mode**:
    - Use the mode toggle switches to select the animation mode:
        - **1984 Pack Mode**: Both switches OFF
        - **Afterlife Pack Mode**: Switch 1 ON, Switch 2 OFF
        - **Frozen Empire Pack Mode**: Switch 1 OFF, Switch 2 ON

3. **Control Direction**:
    - Use the direction toggle switch to change the direction of the animations:
        - **Clockwise**: Switch HIGH
        - **AntiClockwise**: Switch LOW

## OTA Updates

1. **Ensure Wi-Fi Connection**:
    - Ensure the ESP32-S3 is connected to the Wi-Fi network using the credentials in `secrets.h`.

2. **Perform OTA Update**:
    - Use the Arduino IDE or PlatformIO to perform an OTA update:
        - In Arduino IDE: Go to `Sketch` > `Upload Using OTA`.
        - In PlatformIO: Use the `Upload` button or run the `platformio run --target upload --upload-port IP_ADDRESS` command.

## Documentation

- [Configuration Guide](configuration_guide.md)
- [User Guide](user_guide.md)
- [Wiring Guide](wiring_guide.md)
- [Changelog](CHANGELOG.md)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

- This project uses the FastLED library.
- Thanks to the open-source community for their contributions.

## Contact

For more information, contact [your name or email].

