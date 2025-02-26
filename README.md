# CH32V003J4M6-Servo Library

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: CH32V003](https://img.shields.io/badge/Platform-CH32V003-blue.svg)](http://www.wch-ic.com/products/CH32V003.html)

A lightweight servo motor control library specifically designed for the CH32V003J4M6 microcontroller. This library provides easy-to-use functions for controlling standard RC servo motors using the Timer1 PWM capabilities.

## Features

- Simple initialization and control interface
- Support for standard RC servo motors (50Hz PWM)
- Angle control from 0° to 180°
- Compatible with CH32V003J4M6 pins:
  - PA2 (TIM1_CH2N)
  - PC4 (TIM1_CH4)
- Automatic pulse width calculation
- Built-in angle constraints

## Hardware Support

- Microcontroller: CH32V003J4M6
- Compatible Pins:
  - PA2 (Pin 3)
  - PC4 (Pin 7)

## Installation

1. If using PlatformIO:
   ```ini
   lib_deps =
       https://github.com/shakir-abdo/CH32V003J4M6-servo.git
   ```

2. If using manual installation:
   - Download this repository
   - Copy the `src` folder to your project
   - Include the header file in your project

## Usage

```c
#include "servo.h"

int main() {
    SystemInit();

    // Create servo instance
    Servo myServo;

    // Initialize servo on PA2
    servo_init(&myServo, SERVO_PIN_PA2);

    while(1) {
        // Move to 0 degrees
        servo_write(&myServo, 0);
        Delay_Ms(1000);

        // Move to 90 degrees
        servo_write(&myServo, 90);
        Delay_Ms(1000);

        // Move to 180 degrees
        servo_write(&myServo, 180);
        Delay_Ms(1000);
    }
}
```

## API Reference

### Functions

- `void servo_init(Servo* servo, ServoPin pin)`
  - Initializes the servo on the specified pin
  - Parameters:
    - `servo`: Pointer to Servo structure
    - `pin`: Pin selection (SERVO_PIN_PA2 or SERVO_PIN_PC4)

- `void servo_write(Servo* servo, uint8_t angle)`
  - Sets the servo to the specified angle
  - Parameters:
    - `servo`: Pointer to Servo structure
    - `angle`: Desired angle (0-180 degrees)

- `uint8_t servo_read(Servo* servo)`
  - Returns the current angle of the servo
  - Parameters:
    - `servo`: Pointer to Servo structure
  - Returns: Current angle (0-180 degrees)

## Wiring

1. Connect servo power wire (red) to VCC (5V)
2. Connect servo ground wire (brown/black) to GND
3. Connect servo signal wire (yellow/orange) to either:
   - PA2 (Pin 3)
   - PC4 (Pin 7)

## License

MIT License

## Author

Shakir Abdo (shicolare1@gmail.com)

