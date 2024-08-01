# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

# Changelog

## [1.0.2] - 2024-07-27
### Added
- Added functionality to select animation mode (1984, Afterlife, Frozen Empire) using a voltage divider on the analog input pin.
- Added a new CyclotronLidState to switch between two LED rings for animations.
- Implemented Frozen Empire animation with user-defined color and other configurable parameters.

### Changed
- Updated code to use a 12-bit ADC for accurate voltage readings on ESP32.
- Switched analog input pin for mode selection to GPIO 17.
- Changed pin definitions:
  - `CYCLOTRON_CAKE_LED_PIN` to GPIO 19
  - `CYCLOTRON_LID_LED_PIN` to GPIO 18
- Changed number of LEDs for Cyclotron Cake and Lid to 45 and 40 respectively.
- Changed `CyclotronCakeLightsSpacingConfig` and `CyclotronLidLightsSpacingConfig` for better alignment with the new LED counts.
- Renamed several variables for better readability:
  - `LED_PIN` to `CYCLOTRON_CAKE_LED_PIN`
  - `LED_PIN2` to `CYCLOTRON_LID_LED_PIN`
  - `SWITCH_PIN` to `CYCLOTRON_DIRECTION_SWITCH_PIN`
  - `NUM_LEDS1` to `NUM_LEDS_CYCLOTRON_CAKE`
  - `NUM_LEDS2` to `NUM_LEDS_CYCLOTRON_LID`
  - `CyclotronLidLights1` to `cyclotronCakeLights`
  - `CyclotronLidLights2` to `cyclotronLidLights`
  - `cyclotronLightsConfig1` to `cyclotronCakeLightsSpacingConfig`
  - `cyclotronLightsConfig2` to `cyclotronLidLightsSpacingConfig`
  - `fadeDuration` to `EightyFourVersionLightsFadeDuration`
  - `gapDuration` to `EightyFourVersionLightsGapDuration`

### Fixed
- Fixed issue with mode selection not functioning correctly by adjusting threshold values for the 12-bit ADC.
- Ensured that the LEDs on the previous ring are cleared when switching between Cyclotron Cake and Lid states.

### Removed
- Commented out all serial debugging lines to clean up the code for production use.

## [1.1.0]

### Added
- Added functionality to control cyclotron animations for a Ghostbusters proton pack using the ESP32-S3.
- Introduced OTA updates with password protection for firmware updates over Wi-Fi.
- Added a toggle switch on pin 15 for animation direction control (Clockwise and AntiClockwise).
- Added two toggle switches on pins 16 and 17 for selecting animation modes (1984, Afterlife, Frozen Empire).
- Implemented 1984 animation mode with configurable cyclotron light spacing and fade duration.
- Implemented Afterlife animation mode with a LED chase effect, user-defined number of LEDs, and chase speed.
- Implemented Frozen Empire animation mode with a spark effect, user-defined number of LEDs, and chase speed.
- Added real-time monitoring of a toggle switch on pin 14 to switch between two LED rings for cyclotron animations.
- Added user-defined variables for the number of LEDs and spacing configurations for each cyclotron light ring.

### Changed
- Changed LED pin assignments: CYCLOTRON_CAKE_LED_PIN to 19, CYCLOTRON_LID_LED_PIN to 18.
- Changed number of LEDs for the cyclotron lid to 40.
- Changed number of LEDs for the cyclotron cake to 45.
- Renamed various variables and constants for better readability and consistency:
  - `LED_PIN` to `CYCLOTRON_CAKE_LED_PIN`
  - `LED_PIN2` to `CYCLOTRON_LID_LED_PIN`
  - `SWITCH_PIN` to `CYCLOTRON_DIRECTION_SWITCH_PIN`
  - `NUM_LEDS1` to `NUM_LEDS_CYCLOTRON_CAKE`
  - `NUM_LEDS2` to `NUM_LEDS_CYCLOTRON_LID`
  - `CyclotronLidLights1` to `cyclotronCakeLights`
  - `CyclotronLidLights2` to `cyclotronLidLights`
  - `cyclotronLightsConfig1` to `cyclotronCakeLightsSpacingConfig`
  - `cyclotronLightsConfig2` to `cyclotronLidLightsSpacingConfig`
  - `fadeDuration` to `EightyFourVersionLightsFadeDuration`
  - `gapDuration` to `EightyFourVersionLightsGapDuration`
- Commented out all Serial debugging lines for a cleaner codebase.
- Updated `cyclotronCakeLightsSpacingConfig` and `cyclotronLidLightsSpacingConfig` values to match the new LED counts and desired spacing.

### Fixed
- Fixed the OTA update process to include a maximum retry limit for Wi-Fi connection attempts.
- Corrected the handling of LED ring switching to clear previous ring's LEDs before switching.

## [1.0.1] - 2024-07-27
### Added
- New Frozen Empire animation mode with customizable color.
- OTA (Over-the-Air) update functionality.

### Changed
- Changed SWITCH_PIN to GPIO 15.
- Modified the Afterlife and Frozen Empire animations for better effect.

### Fixed
- Resolved issues with animation timing and direction.

## [1.0.0] - 2024-07-20

### Added
- Initial release of the proton pack project with 1984 and Afterlife animations.
- Initial setup and configuration of the project.
- Basic LED control and animation for cyclotron lights.
- Direction and mode toggle switches.

### Changed
- N/A

### Fixed
- N/A