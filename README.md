# Comfortable Responsive Universal Technology for Crutch Health (CRUTCH)

## Abstract

CRUTCH: Comfortable Responsive Universal Technology for Crutch Health revolutionizes mobility with a blend of smart technology and advanced mechanical support. Equipped with responsive sensors, ESP32 communication, Xiao boards, and a system of springs and dampers, CRUTCH transforms traditional crutches into adaptive, health-boosting tools. The integration of springs and dampers reduces impact and provides a smoother, more cushioned experience, minimizing strain on the user's joints. With real-time tracking of posture, weight distribution, and movement through precise accelerometers, CRUTCH offers personalized feedback to encourage optimal alignment and prevent injury. This breakthrough project redefines support, ensuring each step is as safe, comfortable, and intelligent as possible.

---

## Introduction: Background

Currently, traditional crutch designs lack dynamic responsiveness and adequate shock absorption, often leading to user discomfort and upper body strain. Our C.R.U.T.C.H project aims to address these limitations by integrating a mass-spring-damper system, offering adaptive damping and propulsion to enhance mobility and user comfort across diverse needs.

## Introduction: Problem Statement

Traditional crutches fail to provide sufficient shock absorption and energy efficiency, leading to discomfort and strain for users. Our project seeks to solve this by integrating a mass-spring-damper system to enhance ergonomics and adaptability for diverse user needs.

## Main Project Goals

Our project, C.R.U.T.C.H, stands for Comfortable, Responsive, Universal Technology for Crutch Health. The aim is to address the shortcomings of current crutch designs by integrating a mass-spring-damper system to improve shock absorption, energy transfer, and user comfort.

---

## Project Breakdown

### Beginner Level

#### ESP32 to ESP32 Communication

ESP32-to-ESP32 communication is a key component of this project, enabling the direct and wireless exchange of data from various sensors, such as accelerometers and load cells, without relying on a central router. By leveraging protocols like ESP-NOW or Wi-Fi, two ESP32 boards can seamlessly transmit and receive information, ensuring efficient data collection and storage.

Within the CRUTCH system, this capability allows sensor data, including accelerometer readings, to be shared wirelessly between crutches or with a central device. As a result, healthcare providers and users gain real-time insights into movement patterns, walking stability, and overall health metrics. This direct communication channel ultimately enhances the system's efficiency, responsiveness, and ability to support improved patient safety and recovery outcomes.

#### ESP32 to Accelerometer Connection

An accelerometer is a sensor that measures acceleration, the rate of change in velocity over time. The MPU6050, a specific device integrating a 3-axis accelerometer and a 3-axis gyroscope, provides a comprehensive 6-degree-of-freedom motion tracking solution. By integrating this system with an ESP32 microcontroller, it becomes possible to efficiently detect motion and reliably transmit data, enabling robust monitoring and control applications. Such a setup can be employed to analyze walking patterns, detect irregularities such as uneven strides or improper crutch usage, and ultimately enhance user safety through real-time feedback.

**Workflow:** Data from accelerometer (MPU6050) → ESP32 processing → Communication via I2C

**Components:**
- **ESP32 Wroom:** Powerful microcontroller with built-in Wi-Fi and Bluetooth, ideal for wireless data logging and real-time sensor data transmission.
- **MPU6050 Accelerometer:** Integrated 3-axis accelerometer and 3-axis gyroscope sensor that measures acceleration, orientation, and movement patterns in real time.

#### ESP32 to HX711 Amplifier to Load Cells Connection

For our CRUTCH project we established communication between two ESP32 WROOM to HX711 Sparkfun Amplifier and 50kg Load Cells. The purpose of this setup was to measure the forces exerted during the dynamic use of our CRUTCH and to compare the forces experienced using a regular crutch versus the CRUTCH system that we created, which was equipped with a spring and damper mechanism. The data collected from this setup is important to help assess the impact-absorbing performance of the CRUTCH and its potential to help improve user comfortability and stability.

**Components:**
- **ESP32 Wroom:** A powerful microcontroller with Wi-Fi and Bluetooth capabilities that is ideal for wireless data logging and allows real-time transmission of load cell data for visualization.
- **HX711 SparkFun Amplifier:** A 24-bit ADC (Analog-to-Digital Converter) that converts the small signals from the load cells into digital data that is readable by our ESP32 WROOM.
- **50kg Load Cells:** A strain gauge sensor that measures forces applied during crutch use.

### Intermediate Level

#### Real-time Measurement of Data for Load Cells Connection and Experiment

Our group decided to run an experiment that would compare our CRUTCH with a regular crutch using our load cells setup in order to be able to quantify the advantages of our CRUTCH system, which integrates a spring-damper mechanism, compared to a regular crutch. By using load cells to measure and analyze the forces exerted during crutch use, we could objectively evaluate the performance and validate our design's benefits.

**Key Findings:**

1. **Reduced Peak Forces:**
   - Our CRUTCH significantly reduced peak forces compared to a regular crutch, with force differences as significant as 140 N versus 600 N.
   - This demonstrates the effectiveness of the spring-damper system in absorbing shock and distributing forces more evenly.

2. **Improved Shock Absorption:**
   - The spring-damper mechanism successfully absorbed impacts and minimized sharp force spikes, showcasing its ability to reduce strain on the user.

3. **Enhanced User Comfort:**
   - The reduced forces and smoother force profiles indicate that our CRUTCH is more comfortable for users, potentially minimizing fatigue and long-term physical strain compared to a standard crutch.

**Conclusion from our Experiment:**

These results validate the design goals of our CRUTCH, proving that integrating a spring-damper system improves comfort, stability, and usability. This makes it a superior alternative to traditional crutches, especially for users requiring extended mobility support.

#### Stepper Motor Connection

**Purpose of Using a Stepper Motor:**

- The goal was to integrate a motorized mechanism that allows the user to adjust the stiffness of the damper with the use of a motor.
- This feature would provide:
  - Customizable support for users based on their recovery needs or preferences.
  - Adaptability to various terrains, such as smooth surfaces, gravel, or grass.
  - Increased flexibility, making the crutch suitable for a wide range of users and conditions.

**What We Achieved this semester:**

- Successfully operated the stepper motor using a compact and efficient setup:
  - Components used: Xiao ESP32 S3 microcontroller and an A4988 stepper motor driver.
  - Controlled via a computer interface to demonstrate functionality.

**Importance for our CRUTCH System:**

- The ability to adjust damper stiffness provides a tailored experience, reducing strain during use and improves overall comfort.
- Makes the crutch adaptable for users with different injuries or mobility needs, and for varied environmental conditions.
- Supports our project's focus on creating a lightweight, ergonomic, and user-friendly device.

**Future Work:**

- Simplified Control Mechanism:
  - Replace the computer interface with a button-operated system, making adjustments easier and more intuitive.
  - This aligns with our commitment to increasing accessibility and usability for the end-user.

#### Spring and Damper Mechanism Integration

From the top of the figure, our crutch is split into sections A and B respectively.

**Section A (Springs):** Part 1 is free to glide along the frame of the crutches, and part 2 is firmly secured to the frame. The springs connect these two parts, which are responsible for relieving the impact force when the crutches touch the ground.

**Section B (Dampers):** This serves to mitigate the initial reaction force transmitted from the ground to the user's armpits and arms.

All parts were modeled using Autodesk Fusion 360 and 3D printed.

### Advanced Level

#### Data Analysis of Simulations and Experiments on Crutch

We used a mathematical approach to model the mass-spring-damper system. The equation represents the dynamics, factoring in mass, damping, and stiffness. Using Laplace transform, we solved for displacement as a function of time under various force inputs.

**Simulation Results:**

- We implemented simulations using Simulink block diagrams to simulate the MSD system and plot visual graphs.
- We obtained a left-hand side graph when the system is undamped (regular crutch) and the right-hand side graph when the system is damped (C.R.U.T.C.H system).
- Simulations demonstrate how different damping and stiffness values affect displacement over time. By tuning these coefficients, we aim to optimize the crutch's responsiveness to user loads.
- Higher damping reduces overshooting, while varying spring stiffness adjusts energy return.

**Experimental Validation:**

- After we finished the simulations, we planned experiments to show our device functionality.
- Our experiment plan includes analyzing ground reaction forces to optimize the spring and damper coefficients.
- With optimized damping and propulsion, our design achieves smoother and more natural motion, highlighting the potential ergonomic benefits of our C.R.U.T.C.H system.

---
### Muhammad Ahmed Nazir Shaikh
- ESP32 to ESP32 Comms
- ESP32 to Accelerometer Comms
- CAD model development of CRUTCH
- Real-time plotting of Accelerometer data for live CRUTCH experiment
- Ideation and conceptualization for the CRUTCH project
- Designed the installation method of spring, damper, and new additional parts
- 3D modeling and printing of new additional parts of CRUTCH
- Shape optimization of each part with FEA
- Conceived and coordinated Project C.R.U.T.C.H
- Designed experiments to analyze ground reaction forces & crutch motion trajectory
- Carried out measurements for the C.R.U.T.C.H system validation
- Performed theoretical and computational analysis on mass-spring-damper system and ordinary differential equations
- Arduino Nano to Load Cells Comms
- ESP32 to Load Cells Comms
- Motor System Configuration with XIAO Setup
- Real-time data plotting and visualization for live CRUTCH experiment results

---

## Technologies & Tools Used

- **Microcontrollers:** ESP32 WROOM, Xiao ESP32 S3
- **Sensors:** MPU6050 (Accelerometer/Gyroscope), 50kg Load Cells
- **Communication:** HX711 Amplifier, WiFi (TCP), I2C
- **Motor Control:** A4988 Stepper Motor Driver
- **CAD & Simulation:** Autodesk Fusion 360, Simulink
- **Programming:** Arduino IDE, Python (matplotlib, serial)
- **Hardware Design:** 3D printing, FEA (Finite Element Analysis)

## Images
![IMG_6572-scaled-e1734538831558-1536x1536](https://github.com/user-attachments/assets/b7e089eb-321b-4cbf-8a11-7d43467a3301)


<img width="401" height="997" alt="Screenshot-2024-12-14-at-6 50 04 AM" src="https://github.com/user-attachments/assets/998e19bc-a472-4d31-8506-93ec73be98ae" />


