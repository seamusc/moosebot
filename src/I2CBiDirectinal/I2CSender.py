import time

import pigpio

pi = pigpio.pi("RaspberryPi")

# Address
ARDUINO_ADDR = 25

# i2c bus
bus = 1

# Commands
LEFT = "<"
RIGHT = ">"
FORWARD = "|"
BALL_DETECTED = 1
BALL_NOT_DETECTED = 0

def I2CListener(id, tick):
    global pi
    s, b, d = pi.bsc_i2c(ARDUINO_ADDR)

    if b:
        print(d[:-1])

pi = pigpio.pi()

def sendData(dataArray):
    for data in dataArray:
        pi.i2c_write_byte(bus, data)


handle = pi.i2c_open(bus, ARDUINO_ADDR)  # open i2c bus

# Register event handler
e = pi.event_callback(pigpio.EVENT_BSC, I2CListener)
pi.bsc_i2c(ARDUINO_ADDR) # Configure BSC as I2C slave
# time.sleep(600)
# e.cancel()
# pi.bsc_i2c(0) # Disable BSC peripheral
# pi.stop()

while True:
    time.sleep(600)
    sendData([0, '<'])

pi.i2c_close(handle)
