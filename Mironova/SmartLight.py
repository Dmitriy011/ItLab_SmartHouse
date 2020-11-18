#функция, считывающая последнюю строку из файла
def read_last_string(f):
    s=f.readlines()
    last_string=s[len(s)-1]
    return last_string

NORMAL_ILLUMINATION=200 #в Лк

class SmartLight:
        
    @staticmethod
    def Regulation_of_artificial_lighting(value):
        #работа с файлом, хранящим данные лампочки
        f=open('smart_lamp.txt','r+')
        last_string=read_last_string(f)
        lamp_state=last_string[0] 
        brightness=last_string[2:5]
    
        if value<NORMAL_ILLUMINATION:
            if int(lamp_state)!=1:
                print("Включить лампочку")
                f.write("\n1;0.5;")
            else:
                if float(brightness)<1:
                    print("Увеличить яркость")
                    new_brightness=round(float(brightness)+0.1,1)
                    f.write("\n1;"+str(new_brightness)+";")
        if value>NORMAL_ILLUMINATION:
            print("Уменьшить яркость")
            new_brightness=round(float(brightness)-0.1,1)
            f.write("\n1;"+str(new_brightness)+";")
         
