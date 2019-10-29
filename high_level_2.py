# -*- coding: utf-8 -*-
#usar python3
import usb.core
import usb.util
import pymongo
from pymongo import MongoClient
import time
import gpios as gp


#DATOS DEL BARCODE READER
VENDOR_ID = 0x05fe
PRODUCT_ID = 0x1010
#device = usb.core.find(idVendor=self.vendor_id, idProduct=self.product_id)


def MainLoop():
    print("Inicio GPIOs")
    gp.GpiosInit()
    break_loop = False
    loop_cnt = 0
    
    while break_loop != True:        
        LedGreenOn()
        time.sleep(3)
        LedGreenOff()
        time.sleep(3)
        loop_cnt += 1
        if loop_cnt > 100:
            break_loop = True

    print ("Cleaning Out")            
    gp.GpiosCleanUp()

    
if __name__ == "__main__":
    print ("Inicio Componentes")
    MainLoop()
