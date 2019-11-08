# -*- coding: utf-8 -*-
#usar python3
import RPi.GPIO as GPIO
from _thread import start_new_thread
import time

###########################################
# Seteo Inicial de todos los GPIOs a usar #
###########################################
#LED_G = 24
#LED_R = 23
#BUZZER = 25
#SCANNER = 18
#TRASH_UP = 15
#TRASH_DWN = 14

LED_G = 15
LED_R = 18
BUZZER = 14
SCANNER = 25
TRASH_UP = 24
TRASH_DWN = 23

def GpiosInit():
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(LED_G, GPIO.OUT)
    GPIO.setup(LED_R, GPIO.OUT)
    GPIO.setup(BUZZER, GPIO.OUT)
    GPIO.setup(SCANNER, GPIO.OUT)
    GPIO.setup(TRASH_UP, GPIO.OUT)
    GPIO.setup(TRASH_DWN, GPIO.OUT)        


def GpiosCleanUp():
    GPIO.cleanup()

    
#############
# LED Green #
#############
def LedGreenOn():
    GPIO.output(LED_G, GPIO.HIGH)


def LedGreenOff():
    GPIO.output(LED_G, GPIO.LOW)


def LedGreenToggle():
    if GPIO.input(LED_G) == 0:
        GPIO.output(LED_G, GPIO.HIGH)
    else:
        GPIO.output(LED_G, GPIO.LOW)


###########
# LED Red #
###########
def LedRedOn():
    GPIO.output(LED_R, GPIO.HIGH)


def LedRedOff():
    GPIO.output(LED_R, GPIO.LOW)


def LedRedToggle():
    if GPIO.input(LED_R) == 0:
        GPIO.output(LED_R, GPIO.HIGH)
    else:
        GPIO.output(LED_R, GPIO.LOW)


def LedRedToggleContinous():
    start_new_thread(LedRedToggle_Thread, ())


def LedRedToggle_Thread():
    while True:
        LedRedOn()
        time.sleep(1.3)
        LedRedOff()
        time.sleep(0.7)


##########
# Buzzer #
##########
def BuzzerOn():
    GPIO.output(BUZZER, GPIO.HIGH)


def BuzzerOff():
    GPIO.output(BUZZER, GPIO.LOW)


def BuzzerPulse(timer):
    start_new_thread(BuzzerPulse_Thread, (timer,))


def BuzzerPulse_Thread(timer):
    BuzzerOn()
    time.sleep(timer)
    BuzzerOff()

    
###########
# Scanner #
###########
def ScannerOn():
    GPIO.output(SCANNER, GPIO.HIGH)


def ScannerOff():
    GPIO.output(SCANNER, GPIO.LOW)


def ScannerPulse(timer):
    start_new_thread(ScannerPulse_Thread, (timer,))


def ScannerPulse_Thread(timer):
    ScannerOn()
    time.sleep(timer)
    ScannerOff()
    
############
# Trash Up #
############
def TrashUpOn():
    GPIO.output(TRASH_UP, GPIO.HIGH)


def TrashUpOff():
    GPIO.output(TRASH_UP, GPIO.LOW)


def TrashUpPulse():
    start_new_thread(TrashUpPulse_Thread, ())


def TrashUpPulse_Thread():
    TrashUpOn()
    time.sleep(0.2)
    TrashUpOff()

    
##############
# Trash Down #
##############
def TrashDwnOn():
    GPIO.output(TRASH_DWN, GPIO.HIGH)


def TrashDwnOff():
    GPIO.output(TRASH_DWN, GPIO.LOW)


def TrashDwnPulse():
    start_new_thread(TrashDwnPulse_Thread, ())


def TrashDwnPulse_Thread():
    TrashDwnOn()
    time.sleep(0.2)
    TrashDwnOff()





    
