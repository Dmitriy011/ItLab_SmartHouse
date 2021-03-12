from ServerInfoWorker import ServerInfoFileWorker
from ServerInfoWorker import N_THINGS
NORMAL_ILLUMINATION=200 #в Лк
N_LAMPS=2

class SmartLamp:

    def __init__(self):  
        self.name = ""
        self.br = 0
        self.r = 0
        self.g = 0
        self.b = 0

    def update(self, name, br, r, g, b):  
        self.name = name  
        self.br = br
        self.r = r
        self.g = g
        self.b = b

    def get_str(self):
        s=self.name+":BR="+str(int(self.br))+",R="+str(self.r)+",G="+str(self.g)+",B="+str(self.b)+";"
        return s
        

class Jalousie:
    def __init__(self):
        self.name=""
        self.value=0

    def update(self, name,value):
        self.name=name
        self.value=value
        
    def get_str(self):
        s=self.name+":DEG="+str(int(self.value))+";"
        return s

class SmartLight(SmartLamp,Jalousie):
    def Update_lamplight(value,room):
        lamp=SmartLamp()
        s=ServerInfoFileWorker.ReadData()
        for i in range (N_LAMPS-1):
            t=s[i][0]
            if t[7:9]==room:
                lamp.update(s[i][0],s[i][1],s[i][2],s[i][3],s[i][4])
                if value<NORMAL_ILLUMINATION:
                    if int(lamp.br)==0:
                        print("Включить лампочку")
                        lamp.br=1
                    else:
                        if int(lamp.br)<11:
                            print("Увеличить яркость")
                            lamp.br=str(int(lamp.br)+1)
                if value>NORMAL_ILLUMINATION:
                    if int(lamp.br)>0:
                        print("Уменьшить яркость")
                        lamp.br=str(int(lamp.br)-1)
                st=SmartLamp.get_str(lamp)
                ServerInfoFileWorker.SaveData(st)       

    def Update_jalousie(value,room):
        jal=Jalousie()
        s=ServerInfoFileWorker.ReadData()
        for i in range (N_LAMPS,N_THINGS):
            t=s[i][0]
            if t[11:13]==room:
                jal.update(s[i][0],s[i][1])
                if value<NORMAL_ILLUMINATION:
                    if int(jal.value)<=170:
                        print("Открыть жалюзи")
                        jal.value=str(int(jal.value)+10)
                if value>NORMAL_ILLUMINATION:
                    if int(jal.value)>=10:
                        print("Закрыть жалюзи")
                        jal.value=str(int(jal.value)-10)
                st=Jalousie.get_str(jal)
                ServerInfoFileWorker.SaveData(st)

    def Update(value_,value,room):
        if value_>=500:
             SmartLight.Update_jalousie(value,room)
        else:
             SmartLight.Update_lamplight(value,room)





                
                    
                    
