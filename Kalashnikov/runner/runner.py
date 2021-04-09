import subprocess
import sys
import time
import os

C_DIR = r"..\..\Uglinskiy\Smart_House\x64\Debug"
PY_DIR = r"..\..\Mironova"


DELAY = 1

# subprocess.Popen([rf'{V_DIR}\ITLab.exe'])
# time.sleep(DELAY)

while True:
    time.sleep(DELAY)
    subprocess.Popen([rf"{C_DIR}\Smart_House.exe"], cwd=C_DIR)
    time.sleep(DELAY)
    subprocess.Popen([sys.executable, os.path.join(os.getcwd(), rf"{PY_DIR}\main.py")], cwd=PY_DIR, shell=True)
