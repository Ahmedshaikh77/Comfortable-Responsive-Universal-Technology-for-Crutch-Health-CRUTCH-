// ESP32 Sender connected to MPU6050 Accelerometer
// Sends real-time acceleration data via WiFi to Receiver ESP32

#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Wi-Fi credentials
const char* ssid = "esp-32-server";
const char* password = "12345678";

// IP Address of Receiver ESP32
const char* receiverIP = "192.168.4.1";
const int port = 8080;

// MPU6050 setup
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  
  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip. Check wiring!");
    while (1);
  }
  Serial.println("MPU6050 initialized!");
  
  // Wi-Fi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to esp-32-server…");
  }
  Serial.println("Connected to Wi-Fi!");
}

void loop() {
  // Get accelerometer data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  // Prepare data with labels
  String data = "X: " + String(a.acceleration.x) + ", Y: " + 
                String(a.acceleration.y) + ", Z: " + String(a.acceleration.z);
  
  // Send data to receiver ESP32
  WiFiClient client;
  if (client.connect(receiverIP, port)) {
    client.println(data);
    Serial.println("Data sent: " + data);
    client.stop();
  } else {
    Serial.println("Failed to connect to receiver");
  }
  
  delay(500); // Adjust this for data frequency
}
