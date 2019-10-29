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
        #prueba Pin LedGreen
        # gp.LedGreenOn()
        # time.sleep(0.3)
        # gp.LedGreenOff()
        # time.sleep(1)

        #prueba Pin LedRed
        # gp.LedRedOn()
        # time.sleep(0.3)
        # gp.LedRedOff()
        # time.sleep(1)

        #prueba Pin Buzzer
        gp.BuzzerPulse(0.3)
        time.sleep(1)

        #prueba Pin Scanner
        # gp.ScannerPulse(0.3)
        # time.sleep(1)

        #prueba Pin Trash_Up
        # gp.TrashUpPulse()
        # time.sleep(1)

        #prueba Pin Trash_Dwn
        # gp.TrashDwnPulse()
        # time.sleep(1)

        loop_cnt += 1
        if loop_cnt > 4:
            break_loop = True

    print ("Cleaning Out")            
    gp.GpiosCleanUp()

    
if __name__ == "__main__":
    print ("Inicio Componentes")
    MainLoop()
