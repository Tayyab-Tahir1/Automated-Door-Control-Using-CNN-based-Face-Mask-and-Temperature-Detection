import serial
import time
arduino = serial.Serial(port='COM25', baudrate=115200, timeout=0.1)

def write_read(x):
	arduino.write(bytes(x, 'utf-8'))
	time.sleep(0.05)
	data = arduino.readline()
	return data
while True:
	num = input("Enter a number: ")
	value = write_read(num)

	print(int(value))

