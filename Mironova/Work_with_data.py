from SmartThing import SmartLight
from SensorInfoWorker import ISensorInfoWorker
from SensorInfoWorker import TSensorInfoFileWorker
import time

class Work_with_data:
    def get_sensor_name(s):
        i=0
        while s[i]!='=':
            i+=1
        name=s[0:i]
        return name
    
    def get_sensor_value(s):
        i=0
        while s[i]!='=':
            i+=1
        j=i+1
        while s[j]!=';':
            j+=1
        value=s[i+1:j]
        return value

    def reading_and_processing_data():
         while 1:
            li_sensors=TSensorInfoFileWorker.ReadData()
            #для комнаты, которая есть сейчас
            s_value=Work_with_data.get_sensor_value(li_sensors[3])
            SmartLight.Update(float(s_value))
            time.sleep(0.1)  

    def reading_and_processing_data_without_cycle():
            li_sensors=TSensorInfoFileWorker.ReadData()
            #для комнаты, которая есть сейчас
            s_value=Work_with_data.get_sensor_value(li_sensors[3])
            SmartLight.Update(float(s_value))
 

         

         

    
