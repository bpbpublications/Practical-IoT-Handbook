import machine
import time

led_pin = machine.Pin('LED', machine.Pin.OUT)
while True:
    led_pin.value(1)
    print("Turning ON...")
    time.sleep(1)
    led_pin.value(0)
    print("Turning OFF...")
    time.sleep(1)
