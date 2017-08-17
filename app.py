
from bottle import run, route
import os


@route('/')
def index():
    usercall = str(os.geteuid())
    return '<h1>  Hello STEVEN! runnig script as: ' + usercall + ' </h1>'


if __name__ == '__main__':
    if os.geteuid() == 0:
        run(host='192.168.0.4', port=80)
    else:
        run(host='192.168.0.4', port=8080)


