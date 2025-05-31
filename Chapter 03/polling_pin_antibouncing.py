from machine import Pin
from time import sleep_ms

led = Pin('LED', Pin.OUT)
push_button = Pin(2, Pin.IN)

# Initialize variables for debounce
button_state = push_button.value()  # Initial state
debounce_delay = 50  # Adjust as needed (in milliseconds)

while True:
    # Read the current state of the push button
    current_state = push_button.value()

    # Check if the current state is different from the previous state
    if current_state != button_state:
        # Introduce a debounce delay
        sleep_ms(debounce_delay)

        # Read the button state again after the delay
        current_state = push_button.value()

        # If it remains the same, update the LED
        if current_state == button_state:
            if current_state == 1:
                led.value(0)  # Turn off the LED
            else:
                led.value(1)  # Turn on the LED

    # Update the previous state
    button_state = current_state
