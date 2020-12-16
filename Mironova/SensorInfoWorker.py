class ISensorInfoWorker:
    def ReadData():
        raise NotImplementedError()
    def SaveData():
        raise NotImplementedError()

class TSensorInfoFileWorker(ISensorInfoWorker):
    def ReadData():
        f=open('D:\\ITLab\\ItLab_SmartHouse\\Uglinskiy\\SmartHouse\\Total_sensors_data.txt','r')
        s=f.readlines()
        li_sensors = [0]*4
        for n in range (len(s)):
            if s[n][0:9]=="li_sensor":
                i,j=0,0
                for k in range(4):
                    while s[n][i]!=';':
                        i+=1
                    li_sensors[k]=s[n][j:i+1]
                    j=i+1
                    i+=1
        f.close()
        return li_sensors
    
    def SaveData():
        pass

