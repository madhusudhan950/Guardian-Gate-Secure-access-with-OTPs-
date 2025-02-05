# Guardian-Gate-Secure-access-with-OTPs-
Designed and implemented an OTP-based access control system using GSM (M660A) technology. 
- Enhanced security by allowing authorized users to gain access within a time-limited OTP window.
- Developed the embedded firmware for real-time authentication.

# Embedded Systems Project

## Overview
This project is an embedded systems application developed in C, focusing on hardware control and interaction. It includes functionalities such as I2C communication, LCD display handling, keypad input processing, and door control mechanisms.

## Features
- **LCD Display Control**: Manages an LCD for output display.
- **Keypad Input Handling**: Reads and processes input from a keypad.
- **I2C Communication**: Interfaces with peripherals using the I2C protocol.
- **Door Mechanism Control**: Implements logic to open and close a door.
- **Interrupt Handling**: Utilizes interrupts for efficient processing.
- **Timing Delays**: Implements delay functions for hardware synchronization.

## File Structure
```
fin/
├── delay.c          # Implements timing delay functions
├── delay.h          # Header file for delay functions
├── dooropen.c       # Controls the door opening mechanism
├── i2c.c            # Handles I2C communication
├── i2c_lcd_kepad_main.c  # Main program for LCD and keypad interaction
├── interrupt.c      # Manages hardware interrupts
├── kp.c            # Keypad input handling
├── lcd.c           # LCD control functions
├── lcd.h           # Header file for LCD functions
├── otp.c           # Handles One-Time Password (OTP) operations
```

## Requirements
- Embedded development board (e.g., PIC, AVR, ARM-based microcontroller)
- LCD module
- Keypad
- I2C-compatible devices
- Compiler supporting embedded C (e.g., MPLAB, Keil, GCC for ARM)

## Setup & Usage
1. **Compile the Code**: Use an appropriate compiler and toolchain for your microcontroller.
2. **Flash the Firmware**: Upload the compiled binary to your embedded system.
3. **Connect Peripherals**: Ensure the LCD, keypad, and other hardware components are connected correctly.
4. **Run the System**: Power the device and interact using the keypad and LCD.

## Contribution
Feel free to contribute by submitting issues or pull requests.

## License
This project is licensed under the MIT License.

