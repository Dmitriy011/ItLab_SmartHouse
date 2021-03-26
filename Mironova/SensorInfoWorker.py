class SensorInfoFileWorker:
    def ReadData():
        f=open('..\\Uglinskiy\\Smart_House\\Smart_House\\Total_sensors_data.txt','r')
        s=f.readlines()
        f.close()
        return s
    
    def SaveData():
        pass

