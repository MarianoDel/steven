from bottle import run, route

@route('/')
def index():
    return '<h1>  Hello STEVEN!</h1>'


if __name__ == '__main__':
    run()


