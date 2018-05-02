import os
import numpy as np
import time

# Create the NumbersNew folder before the Run

if __name__ == '__main__':
    folder = "...........\\Numbers"
    os.chdir(folder)
    myList = os.listdir()
    for i in range(len(myList) - 1):
        name = myList[i]
        num = int(name.split('.')[0])
        newname = "NumbersNew/" + str(num + 1) + ".txt"
        print(name, " to ", newname)
        os.rename(name, newname)

