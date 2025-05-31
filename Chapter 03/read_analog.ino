// Define the analog pin for reading
const int analogPin = 26;

void setup() {
  // Initialize the serial communication for output
  Serial.begin(9600);

  // Set the ADC resolution to 12 bits (0-4095)
  analogReadResolution(12);
}

void loop() {
  // Read the analog value (0-4095)
  int analogValue = analogRead(analogPin);

  // Calculate the voltage measured using the formula
  float voltageMeasured = (5.0 * analogValue) / 4096;

  // Print the analog value and the calculated voltage
  Serial.print("Analog Value: ");
  Serial.println(analogValue);
  Serial.print("Voltage Measured (V): ");
  Serial.println(voltageMeasured, 3);  // Print with 3 decimal places

  // Add a delay to control the reading frequency
  delay(1000);  // You can adjust the delay as needed
}
