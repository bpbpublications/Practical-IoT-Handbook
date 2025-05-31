// Motor A connections
const int enableA = 14;  // Enable pin for motor A
const int in1 = 12;      // Input 1 for motor A
const int in2 = 13;      // Input 2 for motor A

void setup() {
  // Define the motor control pins as OUTPUT
  pinMode(enableA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Initialize the motor control pins
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
  // Enable the motor by applying a PWM signal to the enable pin
  analogWrite(enableA, 255);  // 255 is full speed; you can adjust it
}

void loop() {
  // Move the motor forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(2000);  // Run for 2 seconds
  
  // Stop the motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(1000);  // Pause for 1 second
  
  // Move the motor backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(2000);  // Run for 2 seconds
  
  // Stop the motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(1000);  // Pause for 1 second
} 
