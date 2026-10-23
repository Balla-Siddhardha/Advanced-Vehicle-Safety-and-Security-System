# Advanced-Vehicle-Safety-and-Security-System

**Overview:**   This project is related to Embedded Systems with features like Password based lock, Automatic speed limiter, Alcohol detection and transmit location details through GSM to emergency contacts during any accident.

<img width="1280" height="516" alt="block_diagram" src="https://github.com/user-attachments/assets/781f2adc-d956-4667-b1d6-1672fa6b9bdc" />
<p align="center">Fig:  Block Diagram</p>


**Technologies used:**  Arduino, C, GPS, GSM, Gyroscope.

**Hardware Components:**  Arduino Mega, 16*2 LCD Display, 4*4 Matrix Membrane Keypad, MQ-3 Alcohol sensor, IR Sensor, L298 Motor Driver, DC Motor(as vehicle engine), LM 393 Speed sensor, Gyroscope, NEO-6M GPS Module, SIM900D GSM Module, Buzzer, Potentiometer(as vehicle accelerator).

**Working Principle:**  

This project is designed to have a vehicle that enables safety and security features like-
1) **Password based vehicle lock system:**  Keypad module is interfaced to Arduino that enables to enter password to unlock vehicle.
2) **Vehicle speed limiter:**  Controlling vehicle speed through motor driver using PWM signals and speed sensor is used to detect the speed.
3) **Automatic speed reduction when alcohol consumption detected:**  Alcohol check happens regularly through Alcohol sensor mounted to helmet and if detected alcohol consumption, vehicle speed limit is automatically reduced 10 kmph within 30 seconds.
4) **Accident detection and alert system using GSM module:**  Gyroscope continuously detects any sudden change in angle or abnormal movement of vehicle which are usually can occur during accident, then GSM module gets location from GPS module and transmits "Help" message and location details to emergency contacts.

<img width="966" height="1280" alt="flowchart" src="https://github.com/user-attachments/assets/a6c366bb-1ed7-442d-a133-6822adad6982" />
<p align="center">Fig:  Flowchart</p>

**Testing and Results:**

