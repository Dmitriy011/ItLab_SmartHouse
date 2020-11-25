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
        i=16
        while last_string[i]!=';':
            i+=1
        lamp_state=last_string[16:i]
    
        if value<NORMAL_ILLUMINATION:
            if int(lamp_state)==0:
                print("Включить лампочку")
                f.write("\nlamp_brightness=1;")
            else:
                if int(lamp_state)<12:
                    print("Увеличить яркость")
                    new_brightness=int(lamp_state)+1
                    f.write("\nlamp_brightness="+str(new_brightness)+";")
        if value>NORMAL_ILLUMINATION:
            if int(lamp_state)>0:
                print("Уменьшить яркость")
                new_brightness=int(lamp_state)-1
                f.write("\nlamp_brightness="+str(new_brightness)+";")       
