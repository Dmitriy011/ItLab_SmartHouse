import client

class SensorInfoBaseWorker:
    def ReadData(name):
        s=client.sensor_select(name)
        return(s)
