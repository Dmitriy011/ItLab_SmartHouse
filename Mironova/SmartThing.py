from ServerInfoWorker import ServerInfoFileWorker
NORMAL_ILLUMINATION=200 #в Лк

class SmartThing:
    def Update():
        raise NotImplementedError()

class SmartLight(SmartThing):
    def Update(value):
        lamp_state=ServerInfoFileWorker.ReadData()
        if value<NORMAL_ILLUMINATION:
            if lamp_state==0:
                print("Включить лампочку")
                ServerInfoFileWorker.SaveData(1)
            else:
                if lamp_state<11:
                    print("Увеличить яркость")
                    ServerInfoFileWorker.SaveData(lamp_state+1)
        if value>NORMAL_ILLUMINATION:
            if lamp_state>0:
                print("Уменьшить яркость")
                ServerInfoFileWorker.SaveData(lamp_state-1)       
