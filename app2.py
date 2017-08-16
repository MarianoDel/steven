from bottle import run, route

@route('/login')
def login():
    return '<h1>On the login page!</h1>'

@route('/register')
def register():
    return '<h1>On the register page!</h1>'

@route('/article/<id>')
def article(id):
    return '<h1>you are viewing article ' + id + '!</h1>'

@route('/posted', method='GET')
def posted():
    return '<h1>POSTED!</h1>'




if __name__ == '__main__':
    run(host='192.168.0.4', port=8080,
        debug=True, reloader=True)


