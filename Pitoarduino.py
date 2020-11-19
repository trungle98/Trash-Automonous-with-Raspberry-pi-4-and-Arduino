import syslog
import time
import serial
from serial import Serial
	

#The following line is for serial over GPIO
port = '/dev/ttyUSB0'


ard = serial.Serial(port,9600,timeout=5)

i = 0

while (True):
    # Serial write section

    setTempCar1 = 20
    setTempCar2 = 37
    ard.flush()
    setTemp1 = str(setTempCar1)
    setTemp2 = str(setTempCar2)
    print ("Python value sent: ")
    print (setTemp1)
    ard.write(setTemp1.encode("utf-8"))
    time.sleep(4)
    #setTempCar1+=1;
    # Serial read section
    msg = ard.readline()
    print ("Message from arduino: ")
    print (msg.decode("utf-8"))
    i = i + 1
else:
    print("Exiting")
exit()
