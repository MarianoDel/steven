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

    # print ("Salto la base de datos")

    #######################################################
    # Todo levantado me quedo mostrando codigo en consola #
    #######################################################
    print ("Paso a un Loop de Lectura de Codigos de Barras")
    reader = BarCodeReader(0x05fe, 0x1010, 84, 6, should_reset=True, debug=False)
    reader.initialize()

    gp.LedRedToggleContinous()
    while True:
        raw_data = reader.read()
        # print(raw_data)
        processed_data = get_data_code(raw_data)
        print(f'processed: {processed_data} size: {len(processed_data)}')

        gp.LedGreenOn()
        gp.TrashUpPulse()
        time.sleep(5)
        gp.TrashDwnPulse()
        gp.LedGreenOff()
        
        
        
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


def get_data_code (new_raw_data):
    readed = ""
    for i in range(len(new_raw_data)):
        a = new_raw_data[i]
        if a >= 30 and a < 40:
            if a == 39:
                code = 0
            else:
                code = a - 30 + 1

            readed += str(code)

    return readed


if __name__ == "__main__":
    print ("Inicio Componentes")
    MainLoop()




