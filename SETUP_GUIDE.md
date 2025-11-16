# CRUTCH Project Setup Guide

## Table of Contents
1. [Firmware Setup](#firmware-setup)
2. [Hardware Assembly](#hardware-assembly)
3. [Python Environment](#python-environment)
4. [Running Data Logger](#running-data-logger)
5. [Troubleshooting](#troubleshooting)

---

## Firmware Setup

### Requirements
- Arduino IDE (Latest version)
- ESP32 Board Package for Arduino
- Required Libraries:
  - Adafruit MPU6050
  - Adafruit Sensor
  - HX711 (by Bogdan Necula)
  - SparkFun Qwiic Scale NAU7802

### Installation Steps

#### 1. Install Arduino IDE
```bash
# macOS (using Homebrew)
brew install arduino-ide

# Or download from https://www.arduino.cc/en/software
```

#### 2. Add ESP32 Board to Arduino IDE
1. Open Arduino IDE
2. Go to: Preferences (Arduino → Preferences)
3. Find "Additional Board Manager URLs"
4. Add URL: `https://dl.espressif.com/dl/package_esp32_index.json`
5. Go to: Tools → Board Manager
6. Search for "ESP32" and install "esp32 by Espressif Systems"

#### 3. Install Required Libraries
1. Go to: Sketch → Include Library → Manage Libraries
2. Search and install each:
   - `Adafruit MPU6050`
   - `Adafruit Unified Sensor`
   - `HX711` (by bogde)
   - `SparkFun Qwiic Scale NAU7802`

#### 4. Board Configuration
1. Tools → Board → ESP32 Dev Module (or Xiao ESP32 S3)
2. Tools → Port → Select your serial port
3. Tools → Upload Speed → 115200

#### 5. Upload Firmware

**For Accelerometer (Sender):**
```bash
# Open file: firmware/ESP32_Accelerometer_Sender.ino
# Click Upload (Ctrl+U / Cmd+U)
```

**For Load Cell (Server/Client):**
```bash
# Open file: firmware/ESP32_LoadCell_Server.ino
# Click Upload
# (Repeat for Client)
```

**For Stepper Motor:**
```bash
# Open file: firmware/Xiao_StepperMotor_Control.ino
# Select Board: Xiao ESP32 S3
# Click Upload
```

### Verification
Open Tools → Serial Monitor (baud: 115200) to verify:
- ESP32 boots successfully
- WiFi connection established
- Sensor detection messages appear

---

## Hardware Assembly

### Accelerometer Setup
**See:** `hardware/HARDWARE_DOCUMENTATION.md`

**Quick Checklist:**
- [ ] ESP32 SDA → MPU6050 SDA (GPIO 21)
- [ ] ESP32 SCL → MPU6050 SCL (GPIO 22)
- [ ] Power connections (3.3V, GND)
- [ ] Verify I2C communication

### Load Cell Setup
**See:** `hardware/HARDWARE_DOCUMENTATION.md`

**Quick Checklist:**
- [ ] Load cell → HX711 (4-wire connection)
- [ ] HX711 → ESP32 (SCK, DT, GND, VCC)
- [ ] Power supply (check voltage ratings)
- [ ] Run calibration code

### Stepper Motor Setup
**See:** `hardware/HARDWARE_DOCUMENTATION.md`

**Quick Checklist:**
- [ ] A4988 → Xiao (Step, Dir, GND)
- [ ] Motor → A4988 (Motor wires)
- [ ] Power supply connected (12V, GND)
- [ ] Microstep configuration set

---

## Python Environment

### macOS Setup

#### 1. Install Python 3
```bash
# Using Homebrew
brew install python3

# Verify installation
python3 --version
```

#### 2. Create Virtual Environment
```bash
cd python/
python3 -m venv venv
source venv/bin/activate
```

#### 3. Install Dependencies
```bash
pip install -r requirements.txt
```

#### 4. Verify Imports
```bash
python3 -c "import serial; import matplotlib; print('All imports OK')"
```

### Linux Setup
```bash
sudo apt-get install python3 python3-pip python3-venv
cd python/
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
```

### Windows Setup
```powershell
python -m venv venv
venv\Scripts\activate
pip install -r requirements.txt
```

---

## Running Data Logger

### Step 1: Identify Serial Port
**macOS:**
```bash
ls /dev/tty.*
# Look for: /dev/tty.usbserial-XXXXXX or /dev/tty.USBMODEM14201
```

**Linux:**
```bash
ls /dev/ttyUSB*
ls /dev/ttyACM*
```

**Windows:**
```powershell
Get-WmiObject Win32_SerialPort | Select-Object Name, DeviceID
```

### Step 2: Update Serial Port in Script

**For Load Cell Data Logger:**
```python
# Edit: python/load_cell_data_logger.py
SERIAL_PORT = '/dev/tty.usbserial-XXXXXX'  # Replace with your port
```

**For Accelerometer Data Logger:**
```python
# Edit: python/accelerometer_data_logger.py
SERIAL_PORT = '/dev/tty.usbserial-XXXXXX'  # Replace with your port
```

### Step 3: Run Logger
```bash
cd python/
source venv/bin/activate
python3 load_cell_data_logger.py
# OR
python3 accelerometer_data_logger.py
```

### Output Files

After running the logger, you'll get:
- **CSV File:** `load_cell_data_YYYYMMDD_HHMMSS.csv`
  - Contains: Timestamp, Force readings
  - Can be imported to Excel/MATLAB for analysis

- **Plot PNG:** `load_cell_plot_YYYYMMDD_HHMMSS.png`
  - Real-time plot of collected data

---

## Troubleshooting

### WiFi Connection Issues

**Problem:** ESP32 won't connect to WiFi
```
Solution:
1. Check SSID and password in firmware (match between sender/receiver)
2. Ensure both ESP32 boards are powered
3. Check router/access point is broadcasting 2.4GHz (not 5GHz)
4. Restart both devices
```

### Serial Port Issues

**Problem:** "Serial port cannot be found"
```bash
# Check available ports
python3 -c "import serial; print(serial.tools.list_ports.comports())"

# On macOS - alternative method
system_profiler SPUSBDataType | grep -A4 "Serial"
```

**Problem:** "Permission denied" (Linux)
```bash
# Add user to dialout group
sudo usermod -a -G dialout $USER
# Restart for changes to take effect
```

### Sensor Not Responding

**Accelerometer:**
```
Solution:
1. Check I2C wiring (SDA/SCL correct GPIO pins)
2. Verify 3.3V power is connected
3. Run I2C scanner sketch to find device address
4. Check for bent pins or loose connections
```

**Load Cells:**
```
Solution:
1. Verify HX711 is connected correctly
2. Check load cells are properly connected to HX711
3. Run calibration code with known weight
4. Adjust calibration factor if readings are off
```

### Data Not Being Logged

**Problem:** Python script runs but no data appears
```bash
# Check serial connection
python3 -c "import serial; s = serial.Serial('/dev/ttyUSB0', 115200); print(s.readline())"

# Verify ESP32 is sending data
# (Check with Arduino IDE Serial Monitor first)
```

---

## Performance Optimization

### For Real-Time Plotting
- Reduce plot update interval (change `interval=100` in FuncAnimation)
- Limit plotted points to last 50 (already done in logger)
- Close other applications to free up CPU

### For Accurate Data Collection
- Use shielded cables for sensor lines
- Keep data logger script running on dedicated machine
- Close Serial Monitor while logger runs
- Check for USB cable quality (use high-quality USB 2.0 cables)

---

## Advanced Configuration

### Changing WiFi Credentials
In firmware files, update:
```cpp
const char* ssid = "your_ssid";
const char* password = "your_password";
```

### Adjusting Sensor Sensitivity
**Accelerometer (in sender code):**
```cpp
// Set range: ±2g, ±4g, ±8g, ±16g
mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
mpu.setGyroRange(MPU6050_RANGE_500_DEG);
```

**Load Cells (in server code):**
```cpp
// Adjust calibration factor based on testing
myScale.setCalibrationFactor(2280.f); // Custom value
```

---

## Additional Resources

- [Arduino IDE Documentation](https://docs.arduino.cc/software/ide-v2)
- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/)
- [Adafruit MPU6050 Library](https://github.com/adafruit/Adafruit_MPU6050)
- [HX711 Library](https://github.com/bogde/HX711)
- [Python Serial Documentation](https://pyserial.readthedocs.io/)

---

**Last Updated:** November 2025
