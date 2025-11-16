# Project File Index and Quick Reference

## Directory Structure

```
CRUTCH/
├── firmware/                        # ESP32 Arduino firmware
│   ├── ESP32_Accelerometer_Sender.ino        # Sends MPU6050 data via WiFi
│   ├── ESP32_Accelerometer_Receiver.ino      # Receives accelerometer data
│   ├── ESP32_LoadCell_Server.ino             # Load cell server (sensor interface)
│   ├── ESP32_LoadCell_Client.ino             # Load cell client (data receiver)
│   └── Xiao_StepperMotor_Control.ino         # Stepper motor damper control
├── python/                          # Python data logging & visualization
│   ├── load_cell_data_logger.py              # Real-time load cell plotting
│   ├── accelerometer_data_logger.py          # Real-time accelerometer plotting
│   └── requirements.txt                       # Python dependencies
├── hardware/                        # Hardware specifications & wiring
│   └── HARDWARE_DOCUMENTATION.md             # Wiring diagrams, pinouts, specs
├── mechanical/                      # CAD & design documentation
│   └── DESIGN_DOCUMENTATION.md               # CAD models, 3D printing, FEA
├── simulations/                     # MATLAB/Simulink analysis
│   └── SIMULATION_ANALYSIS.md                # MSD system models & results
├── README.md                        # Project overview & team info
├── SETUP_GUIDE.md                   # Complete installation & setup guide
└── PROJECT_INDEX.md                 # This file
```

---

## File Descriptions

### Firmware Files (.ino)

#### `firmware/ESP32_Accelerometer_Sender.ino`
- **Purpose:** Reads MPU6050 accelerometer data and transmits via WiFi
- **Hardware:** ESP32 WROOM + MPU6050
- **Communication:** WiFi TCP to 192.168.4.1:8080
- **Output Format:** "X: value, Y: value, Z: value"
- **Upload To:** ESP32 Dev Module
- **Status:** ✅ Production Ready

#### `firmware/ESP32_Accelerometer_Receiver.ino`
- **Purpose:** Receives accelerometer data and forwards to Serial Monitor
- **Hardware:** ESP32 WROOM
- **Communication:** WiFi Access Point (AP)
- **Output:** Serial console display
- **Upload To:** ESP32 Dev Module
- **Status:** ✅ Production Ready

#### `firmware/ESP32_LoadCell_Server.ino`
- **Purpose:** Collects load cell data via HX711 and creates WiFi server
- **Hardware:** ESP32 WROOM + HX711 Amplifier + Load Cells
- **Communication:** WiFi TCP Server on port 80
- **Features:** Auto-tare, force calculation, timestamp
- **Upload To:** ESP32 Dev Module
- **Status:** ✅ Production Ready

#### `firmware/ESP32_LoadCell_Client.ino`
- **Purpose:** Connects to server and forwards load cell data to computer
- **Hardware:** ESP32 WROOM
- **Communication:** WiFi client connection
- **Output:** Serial for real-time plotting
- **Upload To:** ESP32 Dev Module
- **Status:** ✅ Production Ready

#### `firmware/Xiao_StepperMotor_Control.ino`
- **Purpose:** Controls stepper motor for adjustable damper stiffness
- **Hardware:** Xiao ESP32 S3 + A4988 Driver + Stepper Motor
- **Communication:** Serial command interface
- **Input Format:** "M: 100 D: forward S: 500"
- **Upload To:** Xiao ESP32 S3
- **Status:** ✅ Production Ready

---

### Python Scripts (.py)

#### `python/load_cell_data_logger.py`
- **Purpose:** Real-time load cell data visualization and logging
- **Input:** Serial data from ESP32 client
- **Output:** 
  - CSV file: `load_cell_data_YYYYMMDD_HHMMSS.csv`
  - PNG plot: `load_cell_plot_YYYYMMDD_HHMMSS.png`
- **Features:** Live plotting, automatic data logging, dynamic axis scaling
- **Requirements:** pyserial, matplotlib, numpy
- **Run:** `python3 load_cell_data_logger.py`
- **Status:** ✅ Production Ready

#### `python/accelerometer_data_logger.py`
- **Purpose:** Real-time accelerometer 3-axis data visualization
- **Input:** Serial data from ESP32 receiver
- **Output:**
  - CSV file: `accelerometer_data_YYYYMMDD_HHMMSS.csv`
  - PNG summary: `accelerometer_plot_YYYYMMDD_HHMMSS.png`
- **Features:** 3-subplot display (X, Y, Z axes), real-time streaming
- **Requirements:** pyserial, matplotlib, numpy
- **Run:** `python3 accelerometer_data_logger.py`
- **Status:** ✅ Production Ready

---

### Documentation Files (.md)

#### `README.md`
- **Purpose:** Main project documentation
- **Sections:** Abstract, introduction, project breakdown by difficulty level, team info
- **Updated:** November 2025
- **Audience:** Project overview readers, new team members

#### `SETUP_GUIDE.md`
- **Purpose:** Complete installation and configuration guide
- **Sections:**
  - Firmware setup (Arduino IDE, libraries, board config)
  - Hardware assembly checklist
  - Python environment setup
  - Data logger usage
  - Troubleshooting guide
- **Audience:** Developers setting up the project

#### `hardware/HARDWARE_DOCUMENTATION.md`
- **Content:**
  - Wiring diagrams for all connections
  - Component specifications
  - Pin assignments
  - WiFi communication specs
  - Safety considerations
  - Datasheet references
- **Audience:** Hardware engineers, assembly technicians

#### `mechanical/DESIGN_DOCUMENTATION.md`
- **Content:**
  - CAD model specifications (Parts 1-4)
  - Spring-damper system details
  - FEA (Finite Element Analysis) results
  - 3D printing parameters
  - Assembly instructions
  - Material specifications
- **Audience:** Mechanical engineers, manufacturing

#### `simulations/SIMULATION_ANALYSIS.md`
- **Content:**
  - Mathematical model (differential equations)
  - Laplace transform analysis
  - Simulink block diagram description
  - Simulation scenarios
  - Results and analysis
  - Experimental validation
  - Optimization recommendations
- **Audience:** Controls engineers, simulation specialists

---

## Quick Start Guide

### For Software Developers
1. Read: `README.md` → `SETUP_GUIDE.md`
2. Install: Arduino IDE + Board Packages + Libraries
3. Flash: Firmware files to ESP32 boards
4. Test: Check Serial Monitor for data
5. Run: Python loggers for data visualization

### For Hardware Engineers
1. Read: `hardware/HARDWARE_DOCUMENTATION.md`
2. Assemble: Components according to wiring diagrams
3. Test: Individual sensor connections with Arduino IDE
4. Calibrate: Load cells using provided calibration code
5. Integrate: All systems together

### For Mechanical Team
1. Read: `mechanical/DESIGN_DOCUMENTATION.md`
2. Review: CAD models and FEA results
3. Print: 3D parts with specified parameters
4. Assemble: According to assembly instructions
5. Test: Load testing and motion analysis

### For Data Analysis
1. Connect: Load cells via HX711 to ESP32
2. Run: `python3 python/load_cell_data_logger.py`
3. Collect: Real-time force data (3-5 minutes per test)
4. Export: CSV file with timestamps and forces
5. Analyze: In Excel, MATLAB, or Python

---

## System Architecture

```
┌─────────────────────────────────────┐
│         CRUTCH Physical System      │
│                                     │
│  ┌─────────┐      ┌──────────┐    │
│  │  Xiao   │      │   ESP32  │    │
│  │ ESP32S3 │      │  WROOM   │    │
│  └────┬────┘      └────┬─────┘    │
│       │                │           │
│   ┌───▼────┐     ┌─────▼─────┐   │
│   │ A4988  │     │ MPU6050   │   │
│   │ Motor  │     │ Accel     │   │
│   └───┬────┘     └─────┬─────┘   │
│       │                │           │
│   ┌───▼────┐     ┌─────▼─────┐   │
│   │Stepper │     │   WiFi    │   │
│   │ Motor  │     │ Network   │   │
│   └────────┘     └─────┬─────┘   │
└──────────────────────┬──────────────┘
                       │
        ┌──────────────┼──────────────┐
        │              │              │
    ┌───▼────┐  ┌─────▼─────┐  ┌────▼────┐
    │ Serial │  │  Computer │  │ Server  │
    │Monitor │  │ (Python)  │  │ ESP32   │
    └────────┘  └───────────┘  └─────────┘
                      │
                ┌─────▼─────┐
                │ CSV + PNG  │
                │   Plots    │
                └────────────┘
```

---

## Dependencies

### Hardware Required
- 2× ESP32 WROOM modules
- 1× Xiao ESP32 S3 module
- 1× MPU6050 accelerometer/gyroscope
- 1× HX711 load cell amplifier
- 2× 50kg load cells
- 1× A4988 stepper motor driver
- 1× NEMA 17 stepper motor
- Springs (k ≈ 500 N/m)
- Pneumatic/hydraulic damper

### Software Required
- Arduino IDE (v2.0+)
- ESP32 Board Package
- Python 3.8+
- Required Python packages: `pip install -r python/requirements.txt`

### Libraries Required
- Adafruit_MPU6050
- Adafruit_Sensor
- HX711 (bogde)
- SparkFun_Qwiic_Scale_NAU7802

---

## Testing Checklist

- [ ] All firmware files compile without errors
- [ ] ESP32 boards connect to power successfully
- [ ] MPU6050 appears at I2C address 0x68
- [ ] Load cells calibrated with known weight
- [ ] WiFi communication established between devices
- [ ] Serial Monitor shows data output
- [ ] Python loggers run and generate CSV/PNG files
- [ ] Stepper motor responds to serial commands
- [ ] Real-time plots update smoothly (>10 fps)

---

## Known Issues & Solutions

| Issue | Solution |
|-------|----------|
| WiFi won't connect | Match SSID/password in both firmwares |
| MPU6050 not found | Check I2C wiring (SDA/SCL pins) |
| Load cell reads zeros | Run calibration with known weight |
| Plot updates slowly | Reduce matplotlib interval (line 95 in loggers) |
| Python import errors | Install all packages: `pip install -r requirements.txt` |

---

## Version History

| Version | Date | Changes |
|---------|------|---------|
| 1.0 | Nov 2025 | Initial release with complete firmware and docs |

---

## Contributing

To add new features:
1. Create a new branch: `git checkout -b feature/description`
2. Make changes following existing code style
3. Test thoroughly on hardware
4. Commit with clear messages: `git commit -m "Add: feature description"`
5. Push and create pull request

---

## License

This project is part of the Duke MEMS Capstone program.

---

**Last Updated:** November 15, 2025  
**Repository:** https://github.com/Ahmedshaikh77/Comfortable-Responsive-Universal-Technology-for-Crutch-Health-CRUTCH-
