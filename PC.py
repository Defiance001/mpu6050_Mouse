import serial
import time 
from pynput.mouse import Button, Controller
import pyautogui


ArduinoSerial = serial.Serial('com5',baudrate = 9600, timeout=1)
MouseLocation = Controller()
print("loading sensor....")
print("communications established")


while 1:
	Rdata = ArduinoSerial.readline()
	data = str(Rdata.decode('ascii'))
	print(data)

	if data.startswith("x"):
		dataX = data.replace('x', ' ')

	elif data.startswith("Y"):
		dataY = data.replace('Y', ' ') 

		x = dataX
		y = dataY

		x1 = int(x) + 500
		y1 = int(y) - 900

		print("x", x1, "y", y1)

		MouseLocation.position = (-y1, x1)
	
	elif data.startswith("B"):
		pyautogui.click()


		

























