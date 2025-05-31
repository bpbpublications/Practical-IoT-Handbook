import time
from machine import Pin
from onewire import OneWire
from ds18x20 import DS18X20

# Define the 1-Wire bus pin (replace with your actual GPIO pin)
ow_pin = Pin(12)  # Example: Pin 12 is used as the 1-Wire data pin

# Create a OneWire bus object
ow = OneWire(ow_pin)

# Create a DS18X20 temperature sensor object
ds = DS18X20(ow)

# Scan for available DS18B20 sensors on the bus
roms = ds.scan()

if not roms:
    print("No DS18B20 sensors found")
else:
    print(f"Found {len(roms)} DS18B20 sensor(s)")

# Main loop to read and display temperature
while True:
    for rom in roms:
        ds.convert_temp()
        time.sleep_ms(750)
        temp_c = ds.read_temp(rom)
        temp_f = (temp_c * 9.0 / 5.0) + 32.0 #Convert to Farenheit
        print(f"Sensor {rom} - Temperature: {temp_c:.2f}°C | {temp_f:.2f}°F")
    time.sleep(5)  # Adjust the delay as needed
