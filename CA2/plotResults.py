import re
import matplotlib.pyplot as plt
import numpy as np
from subprocess import DEVNULL, STDOUT, check_call

def plot(xLabel, yLabel):
    plt.figure()

    # # xLabel = list(range(1, 100))
    # through4 = np.genfromtxt("throughput4.tr", dtype=np.int32)
    # through5 = np.genfromtxt("throughput5.tr", dtype=np.int32)
    # through6 = np.genfromtxt("throughput6.tr", dtype=np.int32)
    
    # yLabel = through4[:, 1]
    # xLabel = through4[:, 0]
    plt.plot(xLabel, yLabel)
    # plt.plot(xLabel, through5[:, 1])
    # plt.plot(xLabel, through6[:, 1])
    
    plt.show()


def extractData():
    openTRFile = open("wireless.tr", "r")
    data = []
    packetDict = {}
    delayDict = {}
    for row in openTRFile:
        data.append(str(row))
    for pattern in row:
        if re.search('^[dsr].*-It tcp.*', pattern):
            data.append(pattern)
    print("Data Len: " , len(data))
    for line in data:
        resultMatched = re.search('^([srd]) -t ([0-9]*[.]?[0-9]*) .*-Hs (\d+) .*-Ii (\d+) .*', line)
        if not resultMatched: continue

        status = resultMatched.group(1)
        time = resultMatched.group(2)
        hs = resultMatched.group(3)
        uid = resultMatched.group(4)
        
        if status == 's':
            if re.search('[012]', hs):  # sender should be 0 1 2
                if uid not in packetDict:
                    packetDict[uid] = time  # packet is sent now!
            
        elif status == 'r':
            if uid in packetDict:
                print(status + " " + time + " " + hs + " " + uid)
                if re.search('[456]', hs):
                    delayDict[uid] = (float(time) - float(packetDict[uid]))

        elif status == 'd': # if packet is delayed
            if uid in packetDict:
                packetDict.pop(uid)                
                if uid in delayDict:
                    delayDict.pop(uid) 
    return sum(delayDict.values()) / len(delayDict)


def runMultipleTimes():
    diffBandWidths = [1, 10, 100]
    errorRates = [0.001, 0.0001, 0.00001]
    points = []
    for bw in diffBandWidths:
        for errorRate in errorRates:
            check_call(['ns', "wireless.tcl", str(errorRate), str(bw)], stdout=DEVNULL,
                       stderr=STDOUT)
            OneWayDelay = extractData()
            points.append([errorRate, OneWayDelay])
    plot(points[:, 0], points[:, 1])
# AverageDelay =  extractData()

runMultipleTimes()


