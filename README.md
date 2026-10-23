# Advanced Vehicle Safety and Security System
**Overview:**   This project is related to Embedded System with features like Password based lock, Automatic speed limiter, Alcohol detection and transmit location details through GSM to emergency contacts during any accident.


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


<img width="400" height="200" alt="Password based lock system" src="https://github.com/user-attachments/assets/f4631664-7a21-436e-8323-1d35a6feeef7" />

Fig:  Password based lock system

<img width="400" height="200" alt="Speed limiting" src="https://github.com/user-attachments/assets/c91d9904-ad4b-4938-8edc-726d9ab57074" />

Fig:  Speed limiting

<img width="400" height="200" alt="Alcohol Detection" src="https://github.com/user-attachments/assets/1c9b403c-6186-4cf3-8d80-e657bce86a8a" />

Fig:  Alcohol Detection

<img width="400" height="200" alt="Accident detection timer" src="https://github.com/user-attachments/assets/49dba6ba-0fc6-4473-a491-e6e761e0bf3c" />

Fig:  Accident detection timer

<img width="400" height="200" alt="Accident detection message sent" src="https://github.com/user-attachments/assets/cc0fe526-937b-4a80-87c8-a920610cc300" />

Fig:  Accident detection message sent

**Limitations:**

1. The system may be vulnerable to password guessing or unauthorized access if a simple password is used.
2. The alcohol sensor may produce false readings due to environmental factors.
3. The gyroscope may generate false accident alerts due to sudden braking, potholes, or sharp turns. Minor accidents may go undetected if the sensor thresholds are not properly calibrated.
4. GPS signals may be weak indoors or in tunnels, while GSM network failures or poor signal strength may delay or prevent emergency messages from being delivered.


**Future Improvements:**

1. **Advanced Vehicle Authentication:** Integrate RFID, biometric authentication, or a mobile application with encrypted communication to improve vehicle security.
2. **Improved Alcohol Detection:** Use a properly calibrated alcohol detection system with better selectivity, continuous monitoring, and a fail-safe mechanism to prevent unsafe vehicle operation.
3. **IoT-Based Monitoring:** Develop a mobile application or web dashboard to monitor vehicle speed, alcohol detection status, lock status, and accident alerts remotely.

**My contribution:**
1. Served as the team leader and coordinated the project development activities.
2. Designed the circuit layout based on the project requirements.
3. Developed the program code to implement the project functionality.
4. Assembled the hardware setup by making the required circuit connections and interfacing the components.
