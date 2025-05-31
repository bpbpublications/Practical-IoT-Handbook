#Filename interruptpin.py
import RPi.GPIO as GPIO
import time
import argparse

def pin_state_change(channel):
    if GPIO.input(channel) == GPIO.HIGH:
        print(f"GPIO pin {channel} is HIGH")
    else:
        print(f"GPIO pin {channel} is LOW")

if __name__ == "__main__":
    # Create an argument parser to handle command-line arguments
    parser = argparse.ArgumentParser(description="Detect the state of a GPIO pin using interrupts.")
    
    # Add a required argument for the GPIO pin number
    parser.add_argument("pin", type=int, help="GPIO pin number to monitor")
    
    # Parse the command-line arguments
    args = parser.parse_args()
    
    # Set the GPIO mode to BCM
    GPIO.setmode(GPIO.BCM)
    
    # Set up the specified GPIO pin as an input
    GPIO.setup(args.pin, GPIO.IN)
    

    # Add event detection for the specified pin and configure the callback    function
    GPIO.add_event_detect(args.pin, GPIO.BOTH, callback=pin_state_change)
    
    try:
        print(f"Monitoring GPIO pin {args.pin}")
        while True:
            # Your main program can continue to run here
            time.sleep(1)
    
    except KeyboardInterrupt:
        pass
    
    # Clean up GPIO configuration
    GPIO.remove_event_detect(args.pin)
    GPIO.cleanup()
