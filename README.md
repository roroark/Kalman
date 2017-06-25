## Position Estimation using the Kalman Filtering Technique
Most of the code in this repository is standard code available online. The SPARKV Experiment code provided in its CD forms the skeleton of the Embedded C code. Majority of the work done involved tailoring the code to meet my needs and figuring out why things refused to work without warning owing to the unnecessary complexity of the circuit.

## Hardware Description
The original plan was to use the I2C port of the SPARKV to connect the HMC5883L Magnetometer and relay all data (including on-board position encoder data) wirelessly to MATLAB for processing over the Zigbee protocol. Unfortunately the I2C port malfunctioned during a critical phase and the following hardware was used instead:

1. Arduino Uno R3.<br>
2. HMC5883L Magnetometer interfaced with an Arduino using I2C.<br>
3. SPARKV (Atmega 2560 and onboard Position Encoder / Odometer).
4. 2 ZigBees and its TTL to USB hardware.

The GND of the Arduino and the SPARKV were shorted. A digital pin on the Atmega was connected to a digital pin on the Arduino. At a freqency of 7Hz, the Atmega sent its position encoder data via a ZigBee to MATLAB's serial monitor. It also sent a momentary high pulse to the Arduino. After detecting the pulse via polling, the Arduino queries the HMC5883L magnetometer for data via I2C and sends this data serially to MATLAB via the Arduino's USB wire.

In total, 2 COM ports were used. One for the ZigBee receiver and one for the Arduino.

<b>Note:</b> MATLAB Code will be updated shortly.
