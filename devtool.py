import os
import sys
import subprocess

if __name__ == "__main__":
    #call premake
    subprocess.run(("./bin/premake5-win.exe","vs2022"))