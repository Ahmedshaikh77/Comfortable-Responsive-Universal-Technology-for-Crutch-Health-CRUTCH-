// ESP32 Client connected to Computer
// Receives load cell data from Server ESP32 and forwards to Serial Monitor/Plotter

#include <WiFi.h>

// Server Wi-Fi credentials
const char* ssid = "ESP32_Server";
const char* password = "12345678";

// Server details
const char* host = "192.168.4.1"; // Default IP for ESP32 in softAP mode
const int port = 80;

void setup() {
  Serial.begin(115200); // Use the same baud rate as Serial Plotter
  delay(2000); // Allow time for Serial Monitor/Plotter to connect
  Serial.println("Client setup started…");
  
  // Connect to the server's Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi…");
  }
  Serial.println("Connected to Wi-Fi.");
}

void loop() {
  WiFiClient client;
  
  // Connect to the server
  if (client.connect(host, port)) {
    // Wait for server response
    while (client.connected() && client.available() == 0);
    if (client.available()) {
      String forceData = client.readStringUntil('\n');
      
      // Print timestamped data for Serial Plotter
      if (forceData.length() > 0) {
        Serial.println(forceData); // Output: seconds (minutes): force
      }
    }
    
    client.stop(); // Close the connection
  } else {
    Serial.println("0.000 seconds (0.000 minutes),0"); // Plot 0 for both timestamp and force if connection fails
  }
  
  delay(100); // Reduce delay for smoother real-time plotting
}
