from SmartLight import SmartLight
import time

class Work_with_data:
    
    @staticmethod
    def read_string_to_array(s):
        array = [0]*4
        i,j=0,0
        for k in range(4):
            while s[i]!=';':
                i+=1
            array[k]=s[j:i+1]
            j=i+1
            i+=1
        return array

    @staticmethod
    def get_sensor_name(s):
        i=0
        while s[i]!='=':
            i+=1
        name=s[0:i]
        return name
    
    @staticmethod
    def get_sensor_value(s):
        i=0
        while s[i]!='=':
            i+=1
        j=i+1
        while s[j]!=';':
            j+=1
        value=s[i+1:j]
        return value

    @staticmethod
    def reading_and_processing_data():
         while 1:
            #работа с файлом, хранящим показания датчиков
            f=open('sensors.txt','r')
            f.readline()
            s=f.readline()
            li_sensors=Work_with_data.read_string_to_array(s)

            #для комнаты, которая есть сейчас
            s_value=Work_with_data.get_sensor_value(li_sensors[3])
            SmartLight.Regulation_of_artificial_lighting(int(s_value))
            time.sleep(0.1)  
         f.close()

    
