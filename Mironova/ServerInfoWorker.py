import numpy as np
N_THINGS=16 #кол-во умных вещей

class ServerInfoFileWorker:
    def ReadData():
        f=open('..\\Uglinskiy\\Smart_House\\Smart_House\\smart_lamp.txt','r')
        s=f.readlines()
        s_things = [[0] * 2 for i in range(N_THINGS)]
        kol=0
        for i in range(len(s)):
            if s[i][0:4]=="lamp":
                j=0
                while s[i][j]!=':':
                    j+=1
                if j%2==1:
                    n=int(s[i][5:6])
                else:
                    n=int(s[i][5:7])
                s_things[n-1][0]=s[i][0:j]
                k=j
                while s[i][k]!=';':
                    k+=1
                s_things[n-1][1]=s[i][j+4:k]
                kol+=1
            if s[i][0:8]=="jalousie":
                j=0
                while s[i][j]!=':':
                    j+=1
                s_things[kol+int(s[i][9:10])-1][0]=s[i][0:j]
                k=j
                while s[i][k]!=';':
                    k+=1
                s_things[kol+int(s[i][9:10])-1][1]=s[i][j+5:k]
        f.close()
        return s_things
    
    def SaveData(s):
        f=open('..\\Uglinskiy\\Smart_House\\Smart_House\\smart_lamp.txt','r+')
        f.readlines()
        f.write("\n")
        f.write(s)
        print(s)
        f.close()
