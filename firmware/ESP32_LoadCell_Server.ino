// ESP32 Server connected to Load Cells via HX711 Amplifier
// Collects force/weight data and transmits wirelessly to client

#include <Wire.h>
#include <WiFi.h>
#include "SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h"

NAU7802 myScale;

// Calibration factor – Adjust this based on your calibration routine
float calibration_factor = 1000.0; // Example value; you need to calibrate this

// Wi-Fi credentials
const char* ssid = "ESP32_Server";
const char* password = "12345678";

// Wi-Fi server
WiFiServer server(80);

bool isTared = false; // Flag to check if tare is performed
unsigned long lastTareTime = 0;
const unsigned long tareInterval = 60000; // Retare every 60 seconds if unloaded

void setup() {
  Serial.begin(115200);
  Wire.begin(); // Initialize I2C communication
  
  // Initialize the NAU7802
  if (!myScale.begin()) {
    Serial.println("Failed to detect NAU7802. Check your wiring.");
    while (1); // Halt program
  }
  Serial.println("NAU7802 detected!");
  
  // Set the calibration factor
  myScale.setCalibrationFactor(calibration_factor);
  Serial.println("Calibration factor set.");
  
  // Set up Wi-Fi Access Point
  WiFi.softAP(ssid, password);
  Serial.println("Wi-Fi Access Point started.");
  
  // Start the server
  server.begin();
  Serial.println("Server started.");
}

void loop() {
  float forceInN = 0.0;
  
  // Perform tare operation only once at startup
  if (!isTared) {
    Serial.println("Taring the load cell. Please ensure it is unloaded…");
    delay(3000); // Wait for stabilization
    myScale.calculateZeroOffset(); // Set the zero offset
    Serial.println("Tare completed.");
    isTared = true;
  }
  
  // Check if a new reading is available
  if (myScale.available()) {
    forceInN = myScale.getWeight(true);
    
    // Clamp small or negative values to 0
    if (forceInN < 0.5) {
      forceInN = 0.0;
    }
    
    // Periodically retare the load cell if the weight is zero
    if (forceInN == 0.0 && millis() - lastTareTime > tareInterval) {
      myScale.calculateZeroOffset();
      lastTareTime = millis();
      Serial.println("Re-tared the load cell.");
    }
  }
  
  // Handle client connections
  WiFiClient client = server.available();
  if (client) {
    unsigned long timestampMillis = millis(); // Time in milliseconds
    float timestampSeconds = timestampMillis / 1000.0; // Time in seconds
    float timestampMinutes = timestampSeconds / 60.0; // Time in minutes
    
    // Send both seconds and minutes to the client
    String dataToSend = String(timestampSeconds, 3) + " seconds (" +
                        String(timestampMinutes, 3) + " minutes), " + String(forceInN) + " N";
    client.println(dataToSend); // Send data to client
    client.stop(); // Close connection
  }
  
  // Print timestamped force to the Serial Plotter
  unsigned long timestampMillis = millis();
  float timestampSeconds = timestampMillis / 1000.0;
  float timestampMinutes = timestampSeconds / 60.0;
  
  Serial.println(String(timestampSeconds, 3) + " seconds (" +
                 String(timestampMinutes, 3) + " minutes): " + String(forceInN) + " N");
  
  delay(100); // Reduce delay for smoother real-time plotting
}
