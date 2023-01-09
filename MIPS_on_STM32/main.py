from uart import *
import time

FILE = open("test.hex", "r")


while not isCompleted() and portName != "None":
    instruction = FILE.readline()
    instruction = instruction.replace("\n", "")
    if instruction != "":
        #print(instruction)
        writeSerial(instruction)
        time.sleep(0.1)
    readSerial()
FILE.close()




