import time

#функция, считывающая последнюю строку из файла
def read_last_string(f):
    s=f.readlines()
    last_string=s[len(s)-1]
    return last_string

while 1:
    #работа с файлом
    f=open('test_file.txt','r')
    last_string=read_last_string(f)
    state=last_string[0] 
    brightness=last_string[2:5]

    #обработка данных, полученных из файла
    normal_illumination=200 #в Лк
    S=10 #площадь освещаемого помещения
    illumination=float(brightness)*2500/S
    command=''
    if illumination<normal_illumination:
        if int(state)!=1:
            command="Включить лампочку"
        else:
            if float(brightness)<1:
                command="Увеличить яркость"
    if illumination>normal_illumination:
        command="Уменьшить яркость"
    print(command)
    time.sleep(20)

f.close()
