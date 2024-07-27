# Ghostbusters Proton Pack

This project is a movie-accurate replica of the Ghostbusters proton pack, controlled by an ESP32-S3 microcontroller. It includes various animations for the cyclotron lights based on different modes such as 1984 and Afterlife versions.

## Features

- **1984 Animation**: Classic cyclotron light animation.
- **Afterlife Animation**: Modern chase effect animation.
- **Direction Control**: Toggle between clockwise and anti-clockwise animations.
- **Mode Selection**: Switch between different animation modes.

## Getting Started

### Prerequisites

- ESP32-S3 microcontroller
- WS2812B LED strip (40 LEDs)
- Visual Studio Code with PlatformIO

### Wiring Guide

| ESP32-S3 Pin | Component          |
|--------------|--------------------|
| GPIO 18      | Data line of LED strip |
| GPIO 17      | Direction toggle switch (Pull-up resistor) |
| GPIO 16      | Mode toggle switch (Pull-up resistor) |

### Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/proton-pack.git
    cd proton-pack
    ```

2. Open the project in Visual Studio Code with PlatformIO.

3. Connect the components as per the wiring guide.

4. Upload the code to the ESP32-S3.

### Configuration

- Adjust the number of LEDs, brightness, and other parameters in the `main.cpp` file as needed.

### Usage

- Toggle the switches to change the animation direction and mode.

## Contributing

Please read `CONTRIBUTING.md` for details on the code of conduct and the process for submitting pull requests.

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.

## Acknowledgments

- Inspired by the Ghostbusters franchise.
