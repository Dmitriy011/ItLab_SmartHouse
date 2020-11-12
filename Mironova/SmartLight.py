NORMAL_ILLUMINATION=200 #в Лк

class SmartLight:
        
    @staticmethod
    def Regulation_of_artificial_lighting(lamp_state,brightness,value):
        if value<NORMAL_ILLUMINATION:
            if int(lamp_state)!=1:
                print("Включить лампочку")
            else:
                if float(brightness)<1:
                    print("Увеличить яркость")
        if value>NORMAL_ILLUMINATION:
            print("Уменьшить яркость")

  
         
