## 2D Position Estimation using the Kalman Filtering Technique
This repository contains the code used in one of my undergrad lab projects. The 2D location of a Spark V robot had to be estimated, given the odometer readings of the two wheels. Every time a wheel turned 21.14deg, the corresponding odometer register incremented by 1. This corresponded to 0.65cm of travelled distance. Kalman filterning was used to minimize noise in input readings.

<img width="25%" alt="Screenshot 2020-08-24 at 7 22 11 PM" src="https://user-images.githubusercontent.com/18059416/91052620-56b12700-e63f-11ea-9a19-f3e4e71e8f16.png">

 A Kalman Filter essentially estimates a quantity as a function of its current (sensor) value and past few values. The Kalman equations are described in the Matlab code.

## Hardware Description
The original plan was to use the I2C port of the SPARKV to connect the HMC5883L Magnetometer and relay all data (including on-board position encoder data) wirelessly to MATLAB for processing over the Zigbee protocol. Unfortunately the I2C port malfunctioned during a critical phase and the following hardware was used instead:

1. Arduino Uno R3.<br>
2. HMC5883L Magnetometer interfaced with an Arduino using I2C.<br>
3. SPARKV (Atmega 2560 and onboard Position Encoder / Odometer).
4. 2 ZigBees and its TTL to USB hardware.

The GND of the Arduino and the SPARKV were shorted. A digital pin on the Atmega was connected to a digital pin on the Arduino. At a freqency of 7Hz, the Atmega sent its position encoder data via a ZigBee to MATLAB's serial monitor. It also sent a momentary high pulse to the Arduino. After detecting the pulse via polling, the Arduino queries the HMC5883L magnetometer for data via I2C and sends this data serially to MATLAB via the Arduino's USB wire.

In total, 2 COM ports were used. One for the ZigBee receiver and one for the Arduino.

## Results
The MATLAB code involving the Kalman filter is designed to correct the motion of SPARK V which is programmed to trace a square of side 0.5m. The blue square shows the correct path. The robot's position is scaled by about 3x.

<img width="50%" alt="Screenshot 2020-08-24 at 7 22 42 PM" src="https://user-images.githubusercontent.com/18059416/91052833-a7288480-e63f-11ea-8509-06e7a0adffbf.png">
