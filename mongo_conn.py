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

    return mycol



def InsertOne (collection, index):
    mydict = { "name": f"John{index}", "address": "Highway 37" }
    x = collection.insert_one(mydict)


def ShowCol (collection):
    mydoc = collection.find().sort("name")

    for x in mydoc:
        print(x)

if __name__ == "__main__":
    print ("Intento conectar con Mongo")
    mycol = ConnMongo()

    print ("Agrego datos a collection")
    for i in range(10):
        InsertOne(mycol, i)

    print ("Collection data")
    ShowCol(mycol)

    
