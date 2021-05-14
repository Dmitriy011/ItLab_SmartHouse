from SmartThing import SmartThing
import time
from SensorInfoBaseWorker import SensorInfoBaseWorker
import client

class Work_with_data:

    def reading_and_processing_data():
        while 1:
            #для комнаты, которая есть сейчас
            rooms=["bath","kitchen","living","bed"]
            #SmartThing.Update_light(OUT_BR,(SensorInfoBaseWorker.ReadData("living/brightness"))["value"],rooms[2])
            SmartThing.Update_battery((SensorInfoBaseWorker.ReadData("living/temperature"))["value"],rooms[2])
            time.sleep(0.5)  

    def reading_and_processing_data_without_cycle():
            rooms=["bath","kitchen","living","bed"]
            SmartThing.Update_light((SensorInfoBaseWorker.ReadData("out/brightness"))["value"],(SensorInfoBaseWorker.ReadData("bed/brightness"))["value"],rooms[3])
            SmartThing.Update_humidity((SensorInfoBaseWorker.ReadData("bed/humidity"))["value"],rooms[3])
            SmartThing.Update_battery((SensorInfoBaseWorker.ReadData("bed/temperature"))["value"],rooms[3])


client.sensor_insert("out/brightness",300)    
