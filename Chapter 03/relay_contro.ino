// Define the GPIO pin connected to the relay module
const int relayPin = 15;  // Use the appropriate GPIO pin

void setup() {
  // Set the relayPin as an OUTPUT
  pinMode(relayPin, OUTPUT);
  
  // Initialize the relay in the OFF state
  digitalWrite(relayPin, LOW);
}

void loop() {
  // Turn the relay ON (close the switch) for 2 seconds
  digitalWrite(relayPin, HIGH);
  delay(2000);

  // Turn the relay OFF (open the switch) for 2 seconds
  digitalWrite(relayPin, LOW);
  delay(2000);
}
