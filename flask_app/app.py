from flask import Flask, render_template
from pymongo import MongoClient

   
app = Flask(__name__)    #toma el nombre del archivo que corre

# para conexiones con mongo
myclient = MongoClient("mongodb://localhost:27017/")
mydb = myclient["mydatabase"]
mycol_prod = mydb["productos"]
mycol_des = mydb["desechos"]


@app.route('/garbage')
def garbage():
    med = {'name':"maxi", 'desc':"agua", 'date':"hoy mismo", 'pr':"pr", 'done':"no"}
    # return render_template('garbage.html', marks=3)    #ubicar en carpeta template
    desechos = mycol_des.find()
    return render_template('garbage.html', t='Basura', h='Todo lo desechado', des=desechos)    #ubicar en carpeta template

@app.route('/')
def index():
    return render_template('index.html')    #ubicar en carpeta template

if __name__ == "__main__":
    app.run(host='0.0.0.0', debug=True)    #lo corro en modo debug para conocer errores


