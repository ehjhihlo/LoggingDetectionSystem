import serial
import socketio
import RPi.GPIO as gpio
import time

sio = socketio.Client()

cut = '0'

@sio.event
def connect():
    print("Connected to the server")

@sio.event
def disconnect():
    print("Disconnected from the server")
    
@sio.event
def get_cut(data):
    global cut
    cut = data
    print('cut: ', cut)
    

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser.flush()

#server_address = "http://192.168.11.12:5000"
server_address = "http://172.20.10.13:5000" #phone
#server_address = "http://192.168.0.107:5000" #home
sio.connect(server_address)

gpio.setmode(gpio.BCM)
gpio.setup(17, gpio.OUT)

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
        sio.emit('send',line)
        if line == '1':
            gpio.output(17, gpio.HIGH)
            time.sleep(0.5)
            gpio.output(17, gpio.LOW)
            time.sleep(0.5)
