#filename pollpin.py
import RPi.GPIO as GPIO
import time
import argparse

def poll_gpio(pin_number):
    # Set the GPIO mode to BCM
    GPIO.setmode(GPIO.BCM)
    
    # Set up the specified GPIO pin as an input
    GPIO.setup(pin_number, GPIO.IN)
    
    # Initialize the previous state of the GPIO pin
    previous_state = GPIO.input(pin_number)

    try:
        print(f"Polling GPIO pin {pin_number}")
        while True:
            # Read the current state of the GPIO pin
            current_state = GPIO.input(pin_number)

            # Check if the state has changed
            if current_state != previous_state:
                if current_state == GPIO.HIGH:
                    print(f"GPIO pin {pin_number} is HIGH")
                else:
                    print(f"GPIO pin {pin_number} is LOW")
                
                # Update the previous state
                previous_state = current_state
            
            # Delay to avoid continuous polling
            time.sleep(0.1)
    
    except KeyboardInterrupt:
        pass
    finally:
        # Clean up the GPIO configuration before exiting
        GPIO.cleanup()

if __name__ == "__main__":
    # Create an argument parser to handle command-line arguments
    parser = argparse.ArgumentParser(description="Poll the state of a GPIO pin.")
    
    # Add a required argument for the GPIO pin number
    parser.add_argument("pin", type=int, help="GPIO pin number to poll")
    
    # Parse the command-line arguments
    args = parser.parse_args()
    
    # Call the poll_gpio function with the specified GPIO pin number
    poll_gpio(args.pin)
