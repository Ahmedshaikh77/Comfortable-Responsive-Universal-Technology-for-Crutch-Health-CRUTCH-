# Hardware Documentation

## Wiring Diagrams and Component Specifications

### ESP32 to MPU6050 Accelerometer Connection

**Components:**
- ESP32 WROOM Microcontroller
- MPU6050 3-axis Accelerometer/Gyroscope
- Jumper Wires (SDA, SCL, GND, VCC)

**Wiring Configuration:**
```
ESP32 Pin          → MPU6050 Pin
GPIO 21 (SDA)      → SDA
GPIO 22 (SCL)      → SCL
GND                → GND
3.3V               → VCC
```

**I2C Communication:**
- Protocol: I2C (Inter-Integrated Circuit)
- Clock Speed: 400 kHz
- Address: 0x68

---

### ESP32 to HX711 Amplifier to Load Cells Connection

**Components:**
- ESP32 WROOM Microcontroller
- HX711 24-bit ADC Amplifier
- 50kg Load Cells (Strain Gauge)
- Jumper Wires

**Load Cell to HX711 Wiring:**
```
Load Cell Wire Color → HX711 Pin
Red                  → E+ (Excitation +)
Black                → E- (Excitation -)
Green                → A- (Input -)
White                → A+ (Input +)
```

**HX711 to ESP32 Wiring:**
```
HX711 Pin  → ESP32 Pin
VCC        → 5V
GND        → GND
SCK        → GPIO 5
DT         → GPIO 4
```

---

### Stepper Motor Control (Xiao ESP32 S3 + A4988)

**Components:**
- Xiao ESP32 S3 Microcontroller
- A4988 Stepper Motor Driver
- NEMA 17 Stepper Motor
- Power Supply (12V, 2A minimum)

**A4988 to Xiao Wiring:**
```
A4988 Pin  → Xiao Pin
STEP       → GPIO 7
DIR        → GPIO 8
GND        → GND
VMOT       → 12V
GND (Motor) → GND
```

**A4988 Configuration:**
- Microsteps: Set jumpers for 1/8 stepping (3 jumpers on MS1, MS2, MS3)
- Current Limiting: Adjust trimmer for stepper motor current (0.5A typical for NEMA 17)

---

### WiFi Communication Specifications

**Access Point Mode (Server):**
- SSID: ESP32_Server or esp-32-server
- Password: 12345678
- IP Address: 192.168.4.1 (Default)
- Port: 80 (HTTP) or 8080 (Custom)

**Serial Configuration:**
- Baud Rate: 115200
- Data Bits: 8
- Stop Bits: 1
- Parity: None

---

## Component Datasheets

### ESP32 WROOM
- **Voltage:** 3.3V
- **GPIO Pins:** 25 Digital I/O
- **ADC Channels:** 12 (12-bit)
- **Communication:** I2C, SPI, UART, WiFi, Bluetooth
- **Max Current:** 80mA per GPIO

### MPU6050
- **Interface:** I2C
- **Accelerometer Range:** ±2g, ±4g, ±8g, ±16g
- **Gyroscope Range:** ±250, ±500, ±1000, ±2000 °/s
- **I2C Address:** 0x68 or 0x69
- **Operating Voltage:** 3V - 5V

### HX711
- **Resolution:** 24-bit
- **Channels:** 2 independent channels
- **Sampling Rate:** 80 Hz
- **Supply Voltage:** 2.7V - 5.5V
- **Interface:** Digital I/O

### A4988 Stepper Driver
- **Microstepping:** Up to 1/16 step
- **Max Current:** 2A
- **Max Voltage:** 35V
- **Logic Voltage:** 3.3V - 5V

---

## Safety Considerations

1. **Power Supply:** Use regulated 12V, 2A supply for stepper motor
2. **Voltage Levels:** Ensure 3.3V logic compatibility
3. **Thermal Management:** Monitor A4988 temperature during operation
4. **Cable Management:** Use shielded cables for signal lines to reduce noise
5. **Capacitors:** Add 0.1µF capacitors near VCC pins for decoupling
