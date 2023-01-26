import re
import matplotlib.pyplot as plt
import numpy as np
import math
from subprocess import DEVNULL, STDOUT, check_call

class Parser:

    def __init__(self):
        self.tclFile = "wireless.tcl"
        self.trFile = "wireless.tr"
        self.th4 = "throughput4.tr"
        self.th5 = "throughput5.tr"
        self.th6 ="throughput6.tr"
        self.packetPattern = '^([srd]) -t ([0-9]*[.]?[0-9]*) .*-Hs (\d+) .*-Ii (\d+) .*'
        self.tcpPattern = '^[dsr].*-It tcp.*'
        self.packetCount = 0
        return


    def runCommand(self, errorRate, bw):
        print("Running for errorRate: " + str(errorRate) + "\tBW: " + str(bw))
        check_call(['ns', self.tclFile, str(errorRate), str(bw)], stdout=DEVNULL,
                    stderr=STDOUT)
            

    def plot(self, data, superTitle, subTitle, x_ax, y_ax):
        plt.figure(figsize = (15, 6))
        keys = list(data.keys())
        values = list(data.values())
        # print(keys)
        # print(values)
        for i in range(len(keys)):
            plt.subplot(1, 4, i + 1)
            plt.suptitle(superTitle)
            plt.title(subTitle + str(keys[i]))
            pointsX = [i[0] for i in values[i]]
            pointsY = [i[1] for i in values[i]]
            # print(pointsX)
            # print(pointsY)
            plt.xlim([float(0.9* min(pointsX)), float(1.1*max(pointsX))])
            plt.ylim([float(0.9*min(pointsY)), float(1.1*max(pointsY))])
            plt.plot(pointsX, pointsY, marker = 'o')
            plt.ylabel(y_ax)
            plt.xlabel(x_ax)
            
        plt.show()

    # # xLabel = list(range(1, 100))
    # yLabel = through4[:, 1]
    # xLabel = through4[:, 0]    

    def checkStatus(self, whichPacketErrored, 
    resultMatched, sentTimes, retransmittedPackets, arrivalTimes):
        status = resultMatched.group(1)
        time = resultMatched.group(2)
        hs = resultMatched.group(3)
        uid = resultMatched.group(4)

        if status == 's':
            if re.search('[3]', hs):  # sender should be 3
                if uid not in sentTimes:
                    sentTimes[uid] = time  # packet is sent now!
                    self.packetCount += 1
            if self.packetCount == whichPacketErrored: 
                retransmittedPackets.append(uid)
                self.packetCount = 0
                
        elif status == 'r':
            if uid in sentTimes:
                # print(status + " " + time + " " + hs + " " + uid)
                if re.search('[456]', hs): # receivers should be 4 5 6
                    propdelay = (float(time) - float(sentTimes[uid]))
                    if uid in retransmittedPackets:
                        arrivalTimes[uid] = 2*propdelay
                    else:
                        arrivalTimes[uid] = propdelay

        

    def calcAveDelay(self, whichPacketErrored):
        openTRFile = open(self.trFile, "r")
        data = []
        sentTimes = {}
        arrivalTimes = {}
        retransmittedPackets = []
        for row in openTRFile:
            data.append(str(row))
        for pattern in row:
            if re.search(self.tcpPattern, pattern):
                data.append(pattern)
        # print("Data Len: " , len(data))
        self.packetCount = 0
        for line in data:
            resultMatched = re.search(self.packetPattern, line)
            if not resultMatched: continue
            self.checkStatus(whichPacketErrored, resultMatched, 
            sentTimes, retransmittedPackets, arrivalTimes)
        return sum(arrivalTimes.values()) / len(arrivalTimes)


    def calcThroughput(self):
        through4 = np.genfromtxt(self.th4, dtype=np.int32)
        through5 = np.genfromtxt(self.th5, dtype=np.int32)
        through6 = np.genfromtxt(self.th6, dtype=np.int32)
        totalThrougput = np.sum(through4[:, 1], dtype=np. int32) + np.sum(through5[:, 1], dtype=np. int32) + np.sum(through6[:, 1], dtype=np. int32)
        totalThrougput = float(totalThrougput/3000) #Kb
        return totalThrougput