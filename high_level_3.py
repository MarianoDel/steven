# -*- coding: utf-8 -*-
#usar python3
import usb.core
import usb.util
import pymongo
from pymongo import MongoClient
import RPi.GPIO as GPIO
import time
import gpios as gp
from keyboard_alike import reader
    


#DATOS DEL BARCODE READER
VENDOR_ID = 0x05fe
PRODUCT_ID = 0x1010
#device = usb.core.find(idVendor=self.vendor_id, idProduct=self.product_id)


def MainLoop():
    print("Inicio GPIOs")
    gp.GpiosInit()

    ########################################
    # Busco el lector de codigos de barras #
    ########################################
    barcode_find = False
    while barcode_find == False:
        print ("Buscando Lector de Codigo de Barras...")
        device = usb.core.find(idVendor=VENDOR_ID, idProduct=PRODUCT_ID)
        
        if (device != None):
            barcode_find = True
            print ("Encontrado")
        else:
            print ("No se encuentra, verificar cableado USB")
            time.sleep(10)

            
    ####################################
    # Busco conexion con Base de Datos #
    ####################################
    database_find = False
    while database_find == False:
        print ("Abriendo Base de Datos...")
        client = MongoClient()

        try:
            client.admin.command('ismaster')
            database_find = True
        except:
            print ("No se encontro la Base, verificar si el proceso esta corriendo")
            time.sleep(10)



    #######################################################
    # Todo levantado me quedo mostrando codigo en consola #
    #######################################################
    print ("Paso a un Loop de Lectura de Codigos de Barras")
    reader = BarCodeReader(0x05fe, 0x1010, 84, 6, should_reset=True, debug=True)
    reader.initialize()
    while True:
        print(reader.read().strip())
        
    reader.disconnect()

    #prueba Pin LedGreen
    gp.LedGreenOn()
    gp.LedRedOn()
    time.sleep(0.3)
    gp.LedGreenOff()
    gp.LedRedOff()
    time.sleep(0.7)

    print ("Cleaning Out")            
    gp.GpiosCleanUp()


class BarCodeReader(reader.Reader):
    """
    This class supports Lindy USB bar code scanner configured to work as a keyboard
    http://www.lindy.co.uk/accessories-c9/input-devices-c357/barcode-scanners-c360/barcode-scanner-ccd-usb-p1352
    """
    pass

if __name__ == "__main__":
    print ("Inicio Componentes")
    MainLoop()
