import client

class ServerInfoBaseWorker:
    def ReadLamp(name):
        s=client.lamp_select(name)
        return(s)

    def ReadJal(name):
        s=client.jalousie_select(name)
        return(s)

    def ReadHumidifier(name):
        s=client.humidifier_select(name)
        return(s)

    def ReadBattery(name):
        s=client.heater_select(name)
        return(s)
        
    def SaveLamp(name,pw,f):
        client.lamp_upsert(name,pw,f)

    def SaveJal(name,rt,f):
        client.jalousie_upsert(name,rt,f)

    def SaveHumidifier(name,pw,f):
        client.humidifier_upsert(name, pw,f)
        
    def SaveBattery(name,warmth,f):
        client.heater_upsert(name, warmth,f)

   

