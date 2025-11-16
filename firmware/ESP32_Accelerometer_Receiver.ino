// ESP32 Receiver connected to Computer
// Receives accelerometer data from Sender ESP32 and forwards to Serial Monitor

#include <WiFi.h>

// Wi-Fi credentials
const char* ssid = "esp-32-server";
const char* password = "12345678";

// Create Wi-Fi server
WiFiServer server(8080);

void setup() {
  Serial.begin(115200);
  
  // Set up Wi-Fi Access Point
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(IP);
  
  // Start server
  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // Wait for client
  
  if (client) {
    String data = client.readStringUntil('\n'); // Read data
    Serial.println("Received: " + data);        // Forward to Serial Monitor
    client.stop();
  }
}
