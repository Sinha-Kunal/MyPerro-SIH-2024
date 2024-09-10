# Arduino-based Smart Pet Collar

## Overview

This Arduino-based Smart Pet Collar is a compact, wearable device designed for monitoring your pet's activity, body temperature, and location. It uses an MPU6050 accelerometer for movement tracking, an MLX90614 temperature sensor for body temperature measurement, an A9G module for GPS tracking, and displays information on an I2C LCD screen.

## Features

- Pet activity monitoring (step counting)
- Body temperature measurement
- GPS location tracking
- Real-time display on LCD screen
- Serial output for debugging

## Hardware Requirements

- Arduino board (e.g., Arduino Uno, Nano)
- MPU6050 Accelerometer
- MLX90614 Infrared Temperature Sensor
- A9G GPS + GPRS Module
- I2C LCD Display (16x2 characters)
- Connecting wires
- Power source (rechargeable battery for portability)

## Software Dependencies

This project requires the following Arduino libraries:

- Wire.h (built-in)
- LCD-I2C.h
- Adafruit_MLX90614.h
- SoftwareSerial.h (for A9G communication)

Make sure to install these libraries through the Arduino IDE's Library Manager before compiling the code.

## Setup Instructions

1. Connect the hardware components:
   - MPU6050 to Arduino:
     - VCC to 3.3V
     - GND to GND
     - SDA to A4
     - SCL to A5
   - MLX90614 to Arduino:
     - VCC to 3.3V
     - GND to GND
     - SDA to A4
     - SCL to A5
   - I2C LCD to Arduino:
     - VCC to 5V
     - GND to GND
     - SDA to A4
     - SCL to A5
   - A9G GPS Module to Arduino:
     - VCC to 3.3V or 5V (check module specifications)
     - GND to GND
     - TX to a designated RX pin on Arduino
     - RX to a designated TX pin on Arduino

2. Install the required libraries in the Arduino IDE.

3. Update the code to include A9G GPS functionality:
   - Initialize SoftwareSerial for A9G communication
   - Add functions to parse GPS data
   - Incorporate GPS data reading in the main loop

4. Upload the modified code to your Arduino board.

## Usage

1. Securely attach the collar to your pet.
2. Power on the device.
3. The LCD will display "Pet Collar" followed by "Initializing..." during startup.
4. After initialization, the device will start tracking movement, measuring temperature, and acquiring GPS location.
5. The LCD will cycle through displays of:
   - Activity level (step count)
   - Current body temperature
   - GPS coordinates (Latitude and Longitude)
6. For debugging, connect the Arduino to a computer and open the Serial Monitor at 9600 baud to view detailed output.

## GPS Functionality

The A9G module provides GPS capabilities to track your pet's location. The device will periodically update and display the current GPS coordinates. You may need to implement additional features such as:

- Geofencing to alert when your pet leaves a designated area
- Data logging of GPS coordinates for tracking movement over time
- Integration with a mobile app for real-time location tracking

Refer to the A9G module documentation for detailed information on GPS data parsing and additional features.

## Customization

- Adjust the movement detection threshold in the code to suit different pet sizes and activity levels.
- Modify the temperature reading frequency to balance accuracy and power consumption.
- Implement power-saving modes to extend battery life.

## Limitations and Future Improvements

- Battery life may be limited due to continuous GPS usage. Consider implementing sleep modes or reducing update frequency.
- The collar size and weight should be appropriate for the pet. Miniaturization may be necessary for smaller animals.
- Adding water-resistant or waterproof casing would improve durability for outdoor use.
- Implementing cellular data capabilities (using the A9G's GPRS functionality) could enable real-time tracking without proximity to a base station.

## Troubleshooting

- If the LCD doesn't display anything, check the I2C address and wiring connections.
- If the MLX90614 sensor fails to initialize, ensure proper connections and power supply.
- For GPS issues, ensure the A9G module has a clear view of the sky and check the antenna connection.
- If movement tracking seems inaccurate, try adjusting the acceleration threshold in the code.

## Contributing

Feel free to fork this project and submit pull requests for any enhancements or bug fixes. For major changes, please open an issue first to discuss the proposed changes.

## License

This project is open-source and available under the MIT License.
