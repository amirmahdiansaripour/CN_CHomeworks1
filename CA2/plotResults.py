import re
import matplotlib.pyplot as plt
import numpy as np
from subprocess import DEVNULL, STDOUT, check_call

def plot(Xs, Ys, title_, x_label, y_label):
    plt.figure()

    # # xLabel = list(range(1, 100))
    
    # yLabel = through4[:, 1]
    # xLabel = through4[:, 0]
    plt.plot(Xs, Ys, marker='o')
    plt.title(title_)
    plt.ylabel(y_label)
    plt.xlabel(x_label)
    
    plt.show()


def extractData():
    openTRFile = open("wireless.tr", "r")
    data = []
    sentTimes = {}
    arrivalTimes = {}
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

        elif status == 'r':
            if uid in sentTimes:
                # print(status + " " + time + " " + hs + " " + uid)
                if re.search('[456]', hs): # receivers should be 4 5 6
                    arrivalTimes[uid] = (float(time) - float(sentTimes[uid]))

        elif status == 'd': # if should be retransmitted (TIMEOUT)
            if uid in sentTimes:
                sentTimes.pop(uid)                
                if uid in arrivalTimes:
                    arrivalTimes.pop(uid) 
    return sum(arrivalTimes.values()) / len(arrivalTimes)


def runMultipleTimes():
    diffBandWidths = [1, 10, 100]
    errorRates = [0.001, 0.0001, 0.00001]
    Xs = []
    Ys = []
    for bw in diffBandWidths:
        for errorRate in errorRates:
            print("Running for BW: " + str(bw) + "Mbps and ErrorRate: " + str(errorRate))
            check_call(['ns', "wireless.tcl", str(errorRate), str(bw)], stdout=DEVNULL,
                       stderr=STDOUT)
            OneWayDelay = extractData()
            Xs.append(bw)
            Ys.append(OneWayDelay)
    plot(Xs, Ys, "OneWatyDelay vs Bandwidth", "BandWidth (Mbps)", "OneWayDelay (s)")
# AverageDelay =  extractData()

runMultipleTimes()


