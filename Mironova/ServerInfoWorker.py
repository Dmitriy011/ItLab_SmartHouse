class ServerInfoFileWorker:
    def ReadData():
        f=open('D:\\ITLab\\ItLab_SmartHouse\\Uglinskiy\\SmartHouse\\smart_lamp.txt','r')
        s=f.readlines()
        last_string=s[len(s)-1]
        i=10
        while last_string[i]!=';':
            i+=1
        lamp_state=last_string[10:i]
        f.close()
        return int(lamp_state)
    
    def SaveData(value):
        f=open('D:\\ITLab\\ItLab_SmartHouse\\Uglinskiy\\SmartHouse\\smart_lamp.txt','r+')
        f.readlines()
        f.write("\nlamp_1_BR="+str(value)+";")
        f.close()
