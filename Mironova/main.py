from SmartLight import SmartLight
import time

#функция, считывающая последнюю строку из файла
def read_last_string(f):
    s=f.readlines()
    last_string=s[len(s)-1]
    return last_string

while 1:
    #работа с файлом, хранящим данные лампочки
    f1=open('smart_lamp.txt','r')
    last_string=read_last_string(f1)
    lamp_state=last_string[0] 
    brightness=last_string[2:5]
    
    #работа с файлом, хранящим показания датчиков
    f2=open('sensors.txt','r')
    last_string=read_last_string(f2)
    i=0
    while last_string[i]!=';':
        i+=1
    sensor_name=last_string[0:i]
    k=i+1
    while last_string[k]!=';':
        k+=1
    value=last_string[i+1:k]

    #обработка полученных данных
    if sensor_name=="Light sensor":
        SmartLight.Regulation_of_artificial_lighting(int(lamp_state),float(brightness),float(value))
    time.sleep(20)
    
f.close()

