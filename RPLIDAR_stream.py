## if the serial commands don't work on your machine, you may need to install pyserial
## python -m pip install pyserial
## from the window command prompt


import serial
import struct
import binascii


start_scan = "\xA5\x20"                         ##hex A520
express_scan = "\xA5\x5A\x05\x00\x00\x40\x81"   ##hex A55A0500004081
get_info = "\xA5\x50"                           ##hex A550
force_scan = "\xA5\x21"                         ##hex A521

import serial.tools.list_ports as port_list
ports = list(port_list.comports())
for p in ports:
    print (p)

ser = serial.Serial()
ser.baudrate = 115200
ser.port = 'COM7'
ser.setDTR(False) ## this is neccessary to keep the motor running
ser.open()
ser.write(start_scan)


x= ser.read(7)              #this reads 7 characters
x = binascii.hexlify(x)     
print(x)


a=0
b=0
c=0
d=0
e=0
f=0
g=0
h=0
count =0
print ("0 deg\t45 deg\t90 deg\t135 deg\t180 deg\t225 deg\t270 deg\t315 deg")
while (1):
    quality = ord(ser.read(1))/4    # the ord function converts the character to an int
    angle_LSB = ord(ser.read(1))
    angle_MSB = ord(ser.read(1))
    angle = (angle_MSB *256 + angle_LSB) /128   #in degrees
    distance_LSB = ord(ser.read(1))
    distance_MSB = ord(ser.read(1)) 

    distance = (distance_MSB*256 + distance_LSB)/4 # in mm

    if quality ==15:
        if distance != 0:
            if angle <=1 or angle >=359:
                a = distance
            elif 44 <= angle and angle <=46:
                b = distance
            elif 89 <= angle  and angle <=91:
                c = distance
            elif 134 <= angle  and angle <= 136:
                d = distance
            elif 179 <= angle  and angle <=181:
                e = distance
            elif 224 <= angle and angle  <=226:
                f = distance
            elif 269 <= angle and angle  <=271:
                g = distance
            elif 314 <= angle and angle <=316:
                h = distance
    count = count +1
    if count ==500:
        print ("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d") % (a,b,c,d,e,f,g,h)
        count =0
        a=0
        b=0
        c=0
        d=0
        e=0
        f=0
        g=0
        h=0
