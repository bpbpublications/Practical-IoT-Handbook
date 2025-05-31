import machine
import time

# Initialize the ADC (Analog-to-Digital Converter)
adc = machine.ADC(machine.Pin(26))  # Use the appropriate GPIO pin number

# Main loop for reading and printing the analog value
while True:
    # Read the analog value (0-4095 for 12-bit ADC)
    analog_value = adc.read()
    
    # Calculate the voltage measured using the formula
    voltage_measured = (3.3 * analog_value) / 4096
    
    # Print the analog value and the calculated voltage
    print("Analog Value:", analog_value)
    print("Voltage Measured (V):", voltage_measured)    
    
    # Add a delay to control the reading frequency
    time.sleep(1)  # You can adjust the delay as needed
