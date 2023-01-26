import re
import matplotlib.pyplot as plt
import numpy as np
from subprocess import DEVNULL, STDOUT, check_call
import math

def plot(data, superTitle, y_ax):
    plt.figure(figsize = (15, 6))
    keys = list(data.keys())
    values = list(data.values())
    # print(keys)
    # print(values)
    for i in range(len(keys)):
        plt.subplot(1, 4, i + 1)
        plt.suptitle(superTitle)
        plt.title('ErrorRate: ' + str(keys[i]))
        pointsX = [i[0] for i in values[i]]
        pointsY = [i[1] for i in values[i]]
        # print(pointsX)
        # print(pointsY)
        plt.xlim([float(0.9* min(pointsX)), float(1.1*max(pointsX))])
        plt.ylim([float(0.9*min(pointsY)), float(1.1*max(pointsY))])
        plt.plot(pointsX, pointsY, marker = 'o')
        plt.ylabel(y_ax)
        plt.xlabel('BandWidth (Mbps)')
        
    plt.show()

    # # xLabel = list(range(1, 100))
    # yLabel = through4[:, 1]
    # xLabel = through4[:, 0]    

def extractData(whichDrops):
    openTRFile = open("wireless.tr", "r")
    data = []
    sentTimes = {}
    arrivalTimes = {}
    retransmittedPackets = []
    packetCount = 0
    for row in openTRFile:
        data.append(str(row))
    for pattern in row:
        if re.search('^[dsr].*-It tcp.*', pattern):
            data.append(pattern)
    # print("Data Len: " , len(data))
    for line in data:
        resultMatched = re.search('^([srd]) -t ([0-9]*[.]?[0-9]*) .*-Hs (\d+) .*-Ii (\d+) .*', line)
        if not resultMatched: continue

        status = resultMatched.group(1)
        time = resultMatched.group(2)
        hs = resultMatched.group(3)
        uid = resultMatched.group(4)

        if status == 's':
            if re.search('[3]', hs):  # sender should be 3
                if uid not in sentTimes:
                    sentTimes[uid] = time  # packet is sent now!
                    packetCount += 1
            if packetCount == whichDrops: 
                retransmittedPackets.append(uid)
                packetCount = 0
                
        elif status == 'r':
            if uid in sentTimes:
                # print(status + " " + time + " " + hs + " " + uid)
                if re.search('[456]', hs): # receivers should be 4 5 6
                    propdelay = (float(time) - float(sentTimes[uid]))
                    if uid in retransmittedPackets:
                        arrivalTimes[uid] = 2*propdelay
                    else:
                        arrivalTimes[uid] = propdelay

    return sum(arrivalTimes.values()) / len(arrivalTimes)


def runMultipleTimes():
    diffBandWidths = [1, 10, 100]
    errorRates = [0.1, 0.01, 0.001, 0.0]
    packetsDropped = [10, 100, 1000, math.inf]
    subplot = {}
    for i in range(len(errorRates)):
        delays = []
        for bw in diffBandWidths:
            print("Running for errorRate: " + str(errorRates[i]) + " BW: " + str(bw))
            check_call(['ns', "wireless.tcl", str(errorRates[i]), str(bw)], stdout=DEVNULL,
                       stderr=STDOUT)
            OneWayDelay = extractData(packetsDropped[i])
            delays.append([bw, round(OneWayDelay, 3)])
        subplot[errorRates[i]] = delays    
    plot(subplot, "OneWayDelay vs BandWidth", "Average one way delay (s)")
        
runMultipleTimes()