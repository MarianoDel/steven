# -*- coding: utf-8 -*-
# usar python3
import usb.core
import usb.util
import pymongo
from pymongo import MongoClient
# import serial
import RPi.GPIO as GPIO
import time
import gpios as gp

#DATOS DEL BARCODE READER
VENDOR_ID = 0x05fe
PRODUCT_ID = 0x1010
#device = usb.core.find(idVendor=self.vendor_id, idProduct=self.product_id)

#DATOS DEL PUERTO SERIE
#SERIAL_PORT = COM20				#para windows
SERIAL_PORT = '/dev/ttyAMA0'		#para linux
SERIAL_BAUD = 9600

def InitGpios ():
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(18, GPIO.OUT)
        while True:
                GPIO.output(18, GPIO.HIGH)
                time.sleep(3)
                GPIO.output(18, GPIO.LOW)
                time.sleep(3)
                
def MainLoop ():
        print ("Python3 inicio GPIO")
        InitGpios()
        
	print ("Buscando Lector de Codigo de Barras...")
	device = usb.core.find(idVendor=VENDOR_ID, idProduct=PRODUCT_ID)
        
	if (device != None):
		print ("Encontrado")
	else:
		print ("No se encontro, verificar cableado USB")

	print ("Abriendo Base de Datos...")
	client = MongoClient()
	try:
		client.admin.command('ismaster')
	except:		   
		print ("No se encontro la Base, verificar si el proceso esta corriendo")

	print ("Abriendo Puerto Serie...")
	serial_port = serial.Serial(SERIAL_PORT, SERIAL_BAUD, timeout=None)
	if (serial_port != None):
		print ("Puerto Abierto")
	else:
		print ("No se encontro el puerto o su controlador")






if __name__ == "__main__":
	print ("Inicializando Componentes por primer vez...")
	MainLoop()
