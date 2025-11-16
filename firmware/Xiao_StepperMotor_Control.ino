// Stepper Motor Control with Xiao ESP32 S3
// Controls damper stiffness adjustment via stepper motor and A4988 driver

#define dirPin 8
#define stepPin 7
#define stepsPerRevolution 3200

// Variables to store input data
int numSteps = 0;
String direction = "";
int speed = 500; // Default speed (delay in microseconds)

void setup() {
  // Initialize serial communication:
  Serial.begin(9600);
  
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
  // Print instructions to Serial Monitor:
  Serial.println("Enter command in format 'M: (num steps) D: (forward/back) S: (speed in microseconds)'");
}

void loop() {
  if (Serial.available() > 0) {
    // Read the input string from Serial Monitor:
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove any extra whitespace
    
    // Parse the input string:
    if (parseCommand(input)) {
      // Set the direction:
      if (direction == "forward") {
        digitalWrite(dirPin, HIGH);
      } else if (direction == "back") {
        digitalWrite(dirPin, LOW);
      }
      
      // Rotate the stepper motor for the specified number of steps:
      for (int i = 0; i < numSteps; i++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed); // Use the specified speed
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
      }
      
      // Acknowledge the command:
      Serial.println("Command executed: " + input);
    } else {
      Serial.println("Invalid command. Please use 'M: (num steps) D: (forward/back) S: (speed in microseconds)'");
    }
  }
}

// Function to parse the command from Serial Monitor
bool parseCommand(String command) {
  // Check if the input contains "M:", "D:", and "S:":
  if (command.startsWith("M:") && command.indexOf("D:") > 0 && command.indexOf("S:") > 0) {
    int mIndex = command.indexOf("M:") + 2; // Start of number of steps
    int dIndex = command.indexOf("D:") + 2; // Start of direction
    int sIndex = command.indexOf("S:") + 2; // Start of speed
    
    // Extract and parse the number of steps:
    String stepsStr = command.substring(mIndex, command.indexOf("D:"));
    stepsStr.trim(); // Remove whitespace
    numSteps = stepsStr.toInt();
    
    // Extract and parse the direction:
    String directionStr = command.substring(dIndex, command.indexOf("S:"));
    directionStr.trim(); // Remove whitespace
    direction = directionStr;
    
    // Extract and parse the speed:
    String speedStr = command.substring(sIndex);
    speedStr.trim(); // Remove whitespace
    speed = speedStr.toInt();
    
    // Validate inputs:
    if (numSteps > 0 && (direction == "forward" || direction == "back") && speed > 0) {
      return true; // Valid command
    }
  }
  return false; // Invalid command
}
