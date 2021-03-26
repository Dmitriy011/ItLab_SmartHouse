from SmartThing import SmartLight
import time
from SensorInfoWorker import SensorInfoFileWorker
class Work_with_data:
    
    def get_li_sensors():
        s=SensorInfoFileWorker.ReadData();
        li_sensors = [0]*6
        for n in range (len(s)):
            if s[n][0:9]=="li_sensor":
                i,j=0,0
                for k in range(6):
                    while (s[n][i]!='=')and(s[n][i]!=':'):
                        i+=1
                    if s[n][i]=='=':
                        j=i+1
                        while (s[n][i]!=',')and(s[n][i]!=';'):
                            i+=1
                    li_sensors[k]=s[n][j:i]
                    j=i+1
                    i+=1
        return li_sensors

    def reading_and_processing_data():
        while 1:
            #для комнаты, которая есть сейчас
            rooms=["BT","KN","LR","SR"]
            li_sensors=Work_with_data.get_li_sensors()
            SmartLight.Update(int(li_sensors[4]),int(li_sensors[3]),rooms[3])
            time.sleep(0.1)  

    def reading_and_processing_data_without_cycle():
            rooms=["BT","SR","KN","LR"]
            li_sensors=Work_with_data.get_li_sensors()
            SmartLight.Update(int(li_sensors[4]),int(li_sensors[3]),rooms[3])

         

    
