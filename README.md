# LED Project

Welcome to the LED Project! This project demonstrates how to control multiple LEDs using buttons and a potentiometer on an Arduino. The project uses interrupts to handle button presses efficiently and allows for dynamic control of LED brightness through a potentiometer or serial commands.

**Note:** This was a quick school project with several shortcomings. For example, the serial commands are hardcoded, which affects the program's flexibility and efficiency. Improvements are suggested below.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Hardware Setup](#hardware-setup)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Future Improvements](#future-improvements)
- [Contributing](#contributing)
- [License](#license)

## Overview
This project is ideal for learning how to use external interrupts on an Arduino to manage button presses, control LEDs, and read analog input from a potentiometer. The project allows you to:
- Toggle LEDs on or off using buttons connected to interrupt pins.
- Adjust the brightness of an LED using a potentiometer.
- Control the LEDs via commands sent through the Serial Monitor.

## Features
- Uses hardware interrupts for button presses to ensure fast response.
- Debounce logic to handle mechanical switch noise.
- Control LED brightness dynamically with a potentiometer.
- Serial commands to enable/disable buttons or set LED states and brightness.

## Requirements
### Hardware
- Arduino board (e.g., Arduino Uno)
- 3 LEDs (Green, Red, Blue)
- Resistors (220 ohms recommended for each LED and 10K ohms for each pushbutton)
- 2 Pushbuttons
- Potentiometer
- Breadboard
- Jumper wires

### Software
- Arduino IDE

## Hardware Setup
1. **Connect LEDs:**
   - Green LED (Pin 8), Red LED (Pin 9), Blue LED (Pin 6) through 220-ohm resistors.
   - Each cathode connects to GND.

2. **Connect Pushbuttons:**
   - Button 1 to Pin 3 (with internal pull-up resistor enabled).
   - Button 2 to Pin 2 (with internal pull-up resistor enabled).

3. **Connect Potentiometer:**
   - Middle pin to Analog Pin A0.
   - Other two pins to 5V and GND.

4. Assemble the components on a breadboard as per the provided circuit diagram:

![Circuit Diagram](assets/circuit_diagram.png)

## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/MohamedAlsheik/LED_Project.git
   ```
2. Open the project in the Arduino IDE.
3. Select the appropriate board and port under the `Tools` menu.
4. Upload the provided code to your Arduino.

## Usage
1. After uploading the code:
   - Press **Button 1** to toggle the Green LED.
   - Press **Button 2** to toggle the Red LED.
   - Adjust the potentiometer to control the brightness of the Blue LED.
2. Open the Serial Monitor in the Arduino IDE to send commands, such as:
   - `enable button 1` or `disable button 1` to enable/disable Button 1.
   - `ledpower <value>` to set the Blue LED brightness (value range: 0-10).

## Demonstration
Watch the demonstration video for this project:

[Demo Video on Google Drive](https://drive.google.com/file/d/1_Q56H07AvdmEtlXS1-Cle4uujxg9MW9M/view?usp=sharing)

## Project Structure
```
LED_Project
├── Arduino_LED_Interrupts.ino  # Main Arduino source code
├── assets/                     # Media files (circuit diagram, demo video)
├── README.md                   # Project documentation (this file)
└── LICENSE                     # License information
```

## Future Improvements
- Add debounce capacitors to improve hardware reliability.
- Extend functionality for more LEDs and sensors.
- Implement a more advanced serial command interface.
- Refactor the code to make it more modular and remove hardcoded serial commands for improved scalability.

## Contributing
Contributions are welcome! Feel free to fork the repository, create a new branch, and submit a pull request with your changes.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Feel free to reach out if you encounter any issues or have suggestions for improvement!
