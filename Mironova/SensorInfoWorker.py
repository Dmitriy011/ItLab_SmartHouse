class SensorInfoFileWorker:
    def ReadData():
        f=open('..\\Uglinskiy\\SmartHouse\\Total_sensors_data.txt','r')
        s=f.readlines()
        f.close()
        return s
