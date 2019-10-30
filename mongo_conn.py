# -*- coding: utf-8 -*-
#usar python3
import usb.core
import usb.util
import pymongo
from pymongo import MongoClient
import time

def ConnMongo ():
    myclient = pymongo.MongoClient("mongodb://localhost:27017/")
    mydb = myclient["mydatabase"]
    mycol = mydb["customers"]

    mydoc = mycol.find().sort("name")

    for x in mydoc:
        print(x)
    
if __name__ == "__main__":
    print ("Intento conectar con Mongo")
    ConnMongo()
