from ServerInfoBaseWorker import ServerInfoBaseWorker
NORMAL_ILLUMINATION={'living':150,'kitchen':150,'bed':150,'bath':50}
NORMAL_HUMIDITY={'living':50,'kitchen':60,'bed':60}
NORMAL_T={'living':20,'kitchen':19,'bed':18,'bath':22}
N_LAMPS_KN=3
N_LAMPS_BT=3
N_LAMPS_BED=3
N_LAMPS_LR=3
N_JAL_BT=1
N_JAL_KN=1
N_JAL_BED=1
N_JAL_LR=1
N_BATTERY_BT=1
N_BATTERY_KN=1
N_BATTERY_BED=1
N_BATTERY_LR=1
N_HIM_LR=1
N_HIM_KN=1
N_HIM_BED=1

def get_n_lamps(room):
    switcher = {"bath": N_LAMPS_BT,"kitchen": N_LAMPS_KN,"living": N_LAMPS_LR,"bed": N_LAMPS_BED}
    return switcher.get(room, None)

def get_n_jal(room):
    switcher = {"bath": N_JAL_BT,"kitchen": N_JAL_KN,"living": N_JAL_LR,"bed": N_JAL_BED}
    return switcher.get(room, None)

def get_n_bat(room):
    switcher = {"bath": N_BATTERY_BT,"kitchen": N_BATTERY_KN,"living": N_BATTERY_LR,"bed": N_BATTERY_BED}
    return switcher.get(room, None)

def get_n_him(room):
    switcher = {"kitchen": N_HIM_KN,"living": N_HIM_LR,"bed": N_HIM_BED}
    return switcher.get(room, None)

class SmartLamp:

    def __init__(self):  
        self.name = ""
        self.br = 0
        self.web=False
    
    def update(self, name, br,web):  
        self.name = name  
        self.br = br
        self.web=web
    


class Jalousie:
    def __init__(self):
        self.name=""
        self.rt=0
        self.web=False

    def update(self, name,rt,web):
        self.name=name
        self.rt=rt
        self.web=web

class Humidifier:

    def __init__(self):  
        self.name = ""
        self.pw = 0
        self.web=False
    
    def update(self, name, pw,web):  
        self.name = name  
        self.pw = pw
        self.web=web
        

class Battery:

    def __init__(self):  
        self.name = ""
        self.pw = 0
        self.web=False
    
    def update(self, name, pw,web):  
        self.name = name  
        self.pw = pw
        self.web=web
 
class SmartThing(SmartLamp,Jalousie,Humidifier,Battery):

    def Update_lamplight(value,room):
        f=0
        n=get_n_lamps(room)
        for i in range (n):
            lamp=SmartLamp()
            s=room+"/lamp"+str(i+1)
            s=ServerInfoBaseWorker.ReadLamp(s)
            lamp.update(s["name"],s["power"],s["web"])
            if value<NORMAL_ILLUMINATION[room]:
                if lamp.web!=True:
                    if int(lamp.br)==0:
                        print("Включить лампочку")
                        lamp.br=5
                        f=1
                    else:
                        if int(lamp.br)<11:
                            print("Увеличить яркость")
                            lamp.br=str(int(lamp.br)+1)
                            f=1
            if value>NORMAL_ILLUMINATION[room]:
                if lamp.web!=True:
                    if int(lamp.br)>0:
                        print("Уменьшить яркость")
                        lamp.br=str(int(lamp.br)-1)
                        f=1
            if f==1:
                ServerInfoBaseWorker.SaveLamp(lamp.name,lamp.br,False)  

    def Update_jalousie(value,room):
        f=0
        n=get_n_jal(room)
        for i in range (n):
            jal=Jalousie()
            s=room+"/jalousie"
            s=ServerInfoBaseWorker.ReadJal(s)
            jal.update(s["name"],s["rotation"],s["web"])
            if value<NORMAL_ILLUMINATION[room]:
                if jal.web!=True:
                    if int(jal.rt)<60:
                        print("Открыть жалюзи")
                        jal.rt=str(int(jal.rt)+60)
                        f=1
                    elif int(jal.rt)<90:
                        print("Открыть жалюзи")
                        jal.rt=str(int(jal.rt)+30)
                        f=1
            if value>NORMAL_ILLUMINATION[room]:
                if jal.web!=True:
                    if int(jal.rt)>60:
                        print("Закрыть жалюзи")
                        jal.rt=str(int(jal.rt)-30)
                        f=1
                    elif int(jal.rt)>0:
                        print("Закрыть жалюзи")
                        jal.rt=str(int(jal.rt)-60)
                        f=1
            if f==1:
                ServerInfoBaseWorker.SaveJal(jal.name,jal.rt,False)

    def Update_light(value_,value,room):
        if value_>=1000:
             SmartThing.Update_jalousie(value,room)
        else:
             SmartThing.Update_lamplight(value,room)


    def Update_humidity(value,room):
        f=0
        n=get_n_him(room)
        for i in range (n):
            h=Humidifier()
            s=ServerInfoBaseWorker.ReadHumidifier(room+"/humidifier")
            h.update(s["name"],s["power"],s["web"])
            if value<NORMAL_HUMIDITY[room]:
                if h.web!=True:
                    if int(h.pw)==0:
                        print("Включить увлажнитель")
                        h.pw=50
                    else:
                        if int(h.pw)<=90:
                            print("Увлажнитель работает сильнее")
                            h.pw=str(int(h.pw)+10)
                            f=1
            if value>NORMAL_HUMIDITY[room]:
                if h.web!=True:
                    if int(h.pw)>0:
                        print("Увлажнитель выключается")
                        h.pw=0
                        f=1
            if f==1:
                ServerInfoBaseWorker.SaveHumidifier(h.name,h.pw,False) 

    def Update_battery(value,room):
        f=0
        n=get_n_bat(room)
        for i in range (n):
            b=Battery()
            s=ServerInfoBaseWorker.ReadBattery(room+"/heater")
            b.update(s["name"],s["warmth"],s["web"])
            if value<NORMAL_T[room]:
                if b.web!=True:
                    if int(b.pw)==0:
                        print("Включить батареи")
                        b.pw=800
                        f=1
                    else:
                        if int(b.pw)<=1000:
                            print("Батарея работает сильнее")
                            b.pw=str(int(b.pw)+200)
                            f=1
            if value>NORMAL_T[room]:
                if b.web!=True:
                    if int(b.pw)>=200:
                        print("Батарея работает слабее")
                        b.pw=str(b.pw-200)
                        f=1
            if f==1:
                ServerInfoBaseWorker.SaveBattery(b.name,b.pw,False)



