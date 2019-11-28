from flask import Flask, render_template
from pymongo import MongoClient
import time

   
app = Flask(__name__)    #toma el nombre del archivo que corre

# para conexiones con mongo
myclient = MongoClient("mongodb://localhost:27017/")
mydb = myclient["mydatabase"]
mycol_prod = mydb["productos"]
mycol_des = mydb["desechos"]
mycol_worker = mydb["worker"]


@app.route('/garbage')
def garbage():
    desechos = mycol_des.find()
    return render_template('garbage.html', t='Basura', h='Todo lo desechado', des=desechos)

@app.route('/carrito')
def carrito():
    desechos = mycol_des.find()
    # productos = mycol_prod.find()
    # db.mycol_worker.drop()
    mycol_worker.drop()

    mydict = { }

    for d in desechos:
        barcode = d["barcode"]

        qtty = mydict.get(barcode)
        if qtty != None:
            qtty = str(int(qtty) + 1)
            mydict[barcode] = qtty
        else:
            #creo la entrada
            mydict.update({barcode : 1})

    
    print (mydict)
    for m in mydict:
        new_dict = { }
        print(m)
        new_dict = { 'barcode':m }
        new_dict.update({'qtty':mydict[m]})
        producto = mycol_prod.find_one({'barcode':m})

        if producto != None:
            new_dict.update({'producto':producto['producto']})
            new_dict.update({'descripcion':producto['descripcion']})
            
        mycol_worker.insert_one(new_dict)

    mycol = mycol_worker.find()
    return render_template('carrito.html', t='Carrito', h='A Reponer', des=mycol)

@app.route('/clean_garbage')
def clean_garbage():
    desechos = mycol_des.find()

    return render_template('garbage.html', t='Basura', h='Todo lo desechado', des=desechos)

@app.route('/')
def index():
    return render_template('index.html')    #ubicar en carpeta template

if __name__ == "__main__":
    app.run(host='0.0.0.0', debug=True)    #lo corro en modo debug para conocer errores


