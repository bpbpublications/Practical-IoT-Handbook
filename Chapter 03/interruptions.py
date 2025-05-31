from machine import Pin
import time

led = Pin('LED', Pin.OUT)
push_button = Pin(2, Pin.IN, Pin.PULL_UP)  # Configure pull-up resistor

# Initialize a variable to track button press events
button_pressed = False

# Define an interrupt callback function
def button_callback(pin):
    global button_pressed
    button_pressed = True

# Attach the callback to the button's falling edge (button press)
push_button.irq(trigger=Pin.IRQ_FALLING, handler=button_callback)

while True:
    if button_pressed:
        # Turn on the LED
        led.value(1)
        button_pressed = False  # Reset the flag
        time.sleep(1)  # Add a delay to avoid rapid LED flicker
    else:
        # Turn off the LED
        led.value(0)
