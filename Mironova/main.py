from SmartLight import SmartLight
from SmartLight import read_last_string
import time

while 1:

    #работа с файлом, хранящим показания датчиков
    f=open('sensors.txt','r')
    last_string=read_last_string(f)
    i=0
    while last_string[i]!='=':
        i+=1
    sensor_name=last_string[0:i]
    k=i+1
    while last_string[k]!=';':
        k+=1
    value=last_string[i+1:k]

    #обработка полученных данных
    if sensor_name=="p_of_li":
        SmartLight.Regulation_of_artificial_lighting(float(value))
    time.sleep(0.5)
    
f.close()

