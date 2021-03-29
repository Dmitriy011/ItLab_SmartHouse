import subprocess
import sys
import time 
import os

C_DIR = r"..\old_itlab\ItLab_SmartHouse\Uglinskiy\SmartHouse"
PY_DIR = r"..\old_itlab\ItLab_SmartHouse\Mironova"
V_DIR = r"..\old_itlab\ItLab_SmartHouse\Rozanov\x64\Debug"

DELAY = 1

def reset():
    f = open(rf'{C_DIR}\smart_lamp.txt', 'w')
    f.write("lamp_1_BR=0;")
    f.close()

subprocess.Popen([rf'{V_DIR}\ITLab.exe'])
time.sleep(DELAY)

# while True:
#   time.sleep(DELAY)
#   subprocess.Popen([rf'{C_DIR}\SmartHouse.exe'], cwd=C_DIR)
#   time.sleep(DELAY)
#   subprocess.Popen([sys.executable, os.path.join(os.getcwd(), rf'{PY_DIR}\main.py')], cwd = PY_DIR, shell=True)

  