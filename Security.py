import os
import numpy as np

if __name__ == '__main__':
    f = open("file", "r")
    count = 0
    limit = 1000000
    name = "Numbers/temp.txt"
    writeF = open(name, "w")
    primeA = "2"
    line = ""
    for line in f:
        writeF.write(line)
        count += 1
        if count == limit:
            print(line)
            primeB = line[:-2]
            print("Processed {} %".format(np.around(int(primeB) / (10 ** 8), 2)))
            newname = "Numbers/" + primeA + "-" + primeB + ".txt"
            primeA = primeB
            writeF.close()
            os.rename("Numbers/temp.txt", newname)
            writeF = open("Numbers/temp.txt", "w")
            count = 0
    if count != 0:
        primeB = line[:-2]
        newname = primeA + "-" + primeB + ".txt"
        writeF.close()
        os.rename("Numbers/temp.txt", newname)

