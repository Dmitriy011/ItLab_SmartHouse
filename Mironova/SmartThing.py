  
from ServerInfoWorker import ServerInfoFileWorker
from ServerInfoWorker import N_THINGS
NORMAL_ILLUMINATION=200 #в Лк
N_LAMPS=12

class SmartLamp:

    def __init__(self):  
        self.name = ""
        self.br = 0
    
    def update(self, name, br):  
        self.name = name  
        self.br = br
      

    def get_str(self):
        s=self.name+":BR="+str(self.br)+";"
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
        f=0
        for i in range (N_LAMPS):
            t=s[i][0]
            if (t[7:9])==room or(t[8:10])==room:
                lamp.update(s[i][0],s[i][1])
                if value<NORMAL_ILLUMINATION:
                    if int(lamp.br)==0:
                        print("Включить лампочку")
                        lamp.br=1
                        f=1
                    else:
                        if int(lamp.br)<11:
                            print("Увеличить яркость")
                            lamp.br=str(int(lamp.br)+1)
                            f=1
                if value>NORMAL_ILLUMINATION:
                    if int(lamp.br)>0:
                        print("Уменьшить яркость")
                        lamp.br=str(int(lamp.br)-1)
                        f=1
                if f==1:
                    st=SmartLamp.get_str(lamp)
                    ServerInfoFileWorker.SaveData(st)
                    break

    def Update_jalousie(value,room):
        f=0
        jal=Jalousie()
        s=ServerInfoFileWorker.ReadData()
        for i in range (N_LAMPS,N_THINGS):
            t=s[i][0]
            if t[11:13]==room:
                jal.update(s[i][0],s[i][1])
                if value<NORMAL_ILLUMINATION:
                    if int(jal.value)<90:
                        print("Открыть жалюзи")
                        jal.value=str(int(jal.value)+90)
                        f=1
                if value>NORMAL_ILLUMINATION:
                    if int(jal.value)>0:
                        print("Закрыть жалюзи")
                        jal.value=str(int(jal.value)-90)
                        f=1
                if f==1:
                    st=Jalousie.get_str(jal)
                    ServerInfoFileWorker.SaveData(st)

    def Update(value_,value,room):
        if value_>=500:
             SmartLight.Update_jalousie(value,room)
        else:
             SmartLight.Update_lamplight(value,room)
