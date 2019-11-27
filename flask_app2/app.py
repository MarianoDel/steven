from flask import Flask, render_template
app = Flask(__name__)

@app.route('/hello/<int:score>')
def hello_name(score):
   return render_template('hello.html', marks = score, t='Basura', h='Todo lo desechado')

@app.route('/')
def index():
    return "Hello!"

if __name__ == '__main__':
   app.run(host='0.0.0.0', debug = True)
