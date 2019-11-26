# -*- coding: utf-8 -*-
#usar python3
import usb.core
import usb.util
import pymongo
from pymongo import MongoClient
import time

def ConnMongo ():
    myclient = MongoClient("mongodb://localhost:27017/")
    mydb = myclient["mydatabase"]
    mycol_prod = mydb["productos"]
    mycol_des = mydb["desechos"]

    return mycol_prod, mycol_des


def InsertMultiple (collection, index):
    mydict = { "name": f"John{index}", "address": "Highway 37" }
    x = collection.insert_one(mydict)


def InsertOne (collection, data_dict):
    x = collection.insert_one(data_dict)


def ShowCol (collection):
    # mydoc = collection.find().sort("name")
    mydoc = collection.find({},{ "_id": 0, "producto": 1, "descripcion": 1 })

    for x in mydoc:
        print(x)

def ShowCol (collection):
    # mydoc = collection.find().sort("name")
    mydoc = collection.find({},{ "_id": 0, "producto": 1, "descripcion": 1 })

    for x in mydoc:
        print(x)

def ShowGarbage (collection):
    # mydoc = collection.find().sort("name")
    mydoc = collection.find({},{ "_id": 0, "barcode": 1, "date": 1 })

    for x in mydoc:
        print(x)


def DeleteOne (collection):
    myquery = { "address": "Mountain 21" }
    collection.delete_one(myquery)

    
if __name__ == "__main__":
    print ("Intento conectar con Mongo")
    myprod, mygarb = ConnMongo()

    # print ("Agrego datos a collection")
    # for i in range(10):
    #     InsertOne(mycol, i)

    # print ("Agrego datos a collection Productos")
    # mydict = { "producto": "agua", "descripcion": "eco de los andes con gas", "barcode": "77927799000035" }
    # InsertOne(myprod, mydict)

    # mydict = { "producto": "sopa", "descripcion": "quick de pollo", "barcode": "7794000598584" }
    # InsertOne(myprod, mydict)

    # mydict = { "producto": "arvejas", "descripcion": "marolio tetra 340g", "barcode": "7797470007426" }
    # InsertOne(myprod, mydict)
    
    print ("Collection data for Productos")
    ShowCol(myprod)

    print ("Collection data for Desechos")
    ShowGarbage(mygarb)
    
    

    
