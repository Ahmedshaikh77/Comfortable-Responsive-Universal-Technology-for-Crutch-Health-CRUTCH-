# CRUTCH: Comfortable Responsive Universal Technology for Crutch Health

**CRUTCH** is an intelligent assistive mobility system that transforms traditional crutches into adaptive, health-enhancing devices through the integration of embedded sensors, wireless communication, and an optimized mass-spring-damper mechanical system. Designed for user comfort, injury prevention, and real-time data monitoring, CRUTCH sets a new benchmark in rehabilitative technology.



## Features

- **Wireless Communication:** ESP32-to-ESP32 data transfer using Wi-Fi (TCP) for seamless wireless logging.
- **Motion Analysis:** Real-time acceleration and orientation tracking via MPU6050 accelerometer/gyroscope.
- **Force Sensing:** Load cell integration through HX711 amplifier for precise ground reaction force measurement.
- **Stepper Motor Integration:** Adjustable damping via Xiao ESP32 S3 + A4988 motor driver for personalized stiffness control.
- **Python Data Logger & Visualizer:** Real-time force plotting and CSV export for experimental analysis.
- **Mechanical Design Optimization:** Spring-damper system modeled in Fusion 360 and evaluated using shape optimization techniques.
- **Simulink Simulation:** Mass-spring-damper system modeled to evaluate damping effect and user motion trajectory.

---

## Project Structure

```plaintext
CRUTCH-Assistive-Tech/
├── firmware/                # Arduino sketches for ESP32 units
├── python/                  # Real-time plotting and data logging scripts
├── hardware/                # Wiring diagrams and circuit integration images
├── mechanical/              # CAD designs and optimized parts
├── simulations/             # MSD models, trajectory analysis, Simulink results
├── images/                  # Visual documentation of physical setup
├── LICENSE
└── README.md
