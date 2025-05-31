# Import necessary modules
from machine import Pin  # For hardware pin control
from time import sleep   # For introducing delays

# Initialize the LED pin as an output
led = Pin('LED', Pin.OUT)

# Initialize the push button pin as an input (connected to GPIO pin 2)
push_button = Pin(2, Pin.IN)

# Enter an infinite loop for continuous monitoring
while True:
    # Read the current state of the push button
    logic_state = push_button.value()

    # Check if the push button is pressed (logic_state is True)
    if logic_state == True:
        # Turn the LED on (set LED pin to 1)
        led.value(1)
    else:
        # If the push button is not pressed, turn the LED off (set LED pin to 0)
        led.value(0)

