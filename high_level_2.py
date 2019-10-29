# -*- coding: utf-8 -*-
#usar python3
import usb.core
import usb.util
import pymongo
from pymongo import MongoClient
import RPi.GPIO as GPIO
import time


#DATOS DEL BARCODE READER
VENDOR_ID = 0x05fe
PRODUCT_ID = 0x1010
#device = usb.core.find(idVendor=self.vendor_id, idProduct=self.product_id)

def InitGpios():
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(18, GPIO.OUT)


def MainLoop():
    print("Inicio GPIOs")
    InitGpios()
    break_loop = False
    loop_cnt = 0
    
    while break_loop != True:        
        GPIO.output(18, GPIO.HIGH)
        time.sleep(3)
        GPIO.output(18, GPIO.LOW)
        time.sleep(3)
        loop_cnt += 1
        if loop_cnt > 100:
            break_loop = True

    print ("Cleaning Out")            
    GPIO.cleanup()

    
if __name__ == "__main__":
    print ("Inicio Componentes")
    MainLoop()
