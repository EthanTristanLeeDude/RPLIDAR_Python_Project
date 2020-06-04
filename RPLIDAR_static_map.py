## if the serial commands don't work on your machine, you may need to install pyserial
## python -m pip install pyserial
## from the window command prompt


import serial
import struct
import binascii

from struct import pack
from PIL import Image       #pip install Pillow

import math

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

n=0
attempt =0
array=[0]*72
print ("0 deg\t45 deg\t90 deg\t135 deg\t180 deg\t225 deg\t270 deg\t315 deg")
while (n<72):
    quality = ord(ser.read(1))/4    # the ord function converts the character to an int
    angle_LSB = ord(ser.read(1))
    angle_MSB = ord(ser.read(1))
    angle = (angle_MSB *256 + angle_LSB) /128   #in degrees
    distance_LSB = ord(ser.read(1))
    distance_MSB = ord(ser.read(1)) 
    
    def distance_cm(distance_MSB, distance_LSB):
        distance = (distance_MSB*256 + distance_LSB)/40 # in cm 40 for cm, i increase to 400 to test out of range error
        return distance

    

    attemt = attempt +1
    if attemt ==2:
        n=n+1
        attempt =0
    if (n*5-2) <= angle <= (n*5+2):
        if quality ==15: 
            array[n] = distance_cm(distance_MSB, distance_LSB)
            #print (array[n])
            #a = distance_cm(distance_MSB, distance_LSB)
            #print (a)
            n = n+1
        
print("done")
for n in range(0,71):
    print(array[n])

ser.setDTR(True)



class Bitmap():
  def __init__(s, width, height):
    s._bfType = 19778 # Bitmap signature
    s._bfReserved1 = 0
    s._bfReserved2 = 0
    s._bcPlanes = 1
    s._bcSize = 12
    s._bcBitCount = 24
    s._bfOffBits = 26
    s._bcWidth = width
    s._bcHeight = height
    s._bfSize = 26+s._bcWidth*3*s._bcHeight
    s.clear()


  def clear(s):
    s._graphics = [(255,255,255)]*s._bcWidth*s._bcHeight    ##all 255 here will creat a white background
                                                            ##all zeros will create a black background


  def setPixel(s, x, y, color):
    if isinstance(color, tuple):
      if x<0 or y<0 or x>s._bcWidth-1 or y>s._bcHeight-1:
        raise ValueError('Coords out of range')
      if len(color) != 3:
        raise ValueError('Color must be a tuple of 3 elems')
      s._graphics[y*s._bcWidth+x] = (color[2], color[1], color[0])
    else:
      raise ValueError('Color must be a tuple of 3 elems')


  def write(s, file):
    with open(file, 'wb') as f:
      f.write(pack('<HLHHL', 
                   s._bfType, 
                   s._bfSize, 
                   s._bfReserved1, 
                   s._bfReserved2, 
                   s._bfOffBits)) # Writing BITMAPFILEHEADER
      f.write(pack('<LHHHH', 
                   s._bcSize, 
                   s._bcWidth, 
                   s._bcHeight, 
                   s._bcPlanes, 
                   s._bcBitCount)) # Writing BITMAPINFO
      for px in s._graphics:
        f.write(pack('<BBB', *px))
      for i in range((4 - ((s._bcWidth*3) % 4)) % 4):
        f.write(pack('B', 0))



def main():
  side = 2400
  b = Bitmap(side, side)
  for n in range(0, 72):
    for p in range(0,array[n]):
        b.setPixel(int(round(p*math.sin(n*5*3.14/180))+1200), int(round(p*math.cos(n*5*3.14/180))+1200), (255, 0, 0))
##        x = int(round(p*math.sin(n*5*3.14/180)))
##        y = int(round(p*math.cos(n*5*3.14/180)))
##        print(x)
##        print(x)
    
  b.write('file2.bmp')
  img = Image.open("file2.bmp")             # i added this and the next line to show the image
  img.show()                                # i added this to show the image, required: from PIL import Image       #pip install Pillow

if __name__ == '__main__':
  main()


