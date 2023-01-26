from plotResults import Parser
import math

def runMultipleTimes():
    diffBandWidths = [1, 10, 100]
    errorRates = [0.1, 0.01, 0.001, 0.0]
    packetsDropped = [10, 100, 1000, math.inf]
    P = Parser()
    subplots1 = {}
    subplots2 = {}
    subplots3 = {1 : [], 10 : [], 100 : []}
    for i in range(len(errorRates)):    
        delays = []
        thPutsvsBW = []
        for bw in diffBandWidths:
            P.runCommand(errorRates[i], bw)
            OneWayDelay = P.calcAveDelay(packetsDropped[i])
            througPut = P.calcThroughput()
            delays.append([bw, round(OneWayDelay, 3)])
            thPutsvsBW.append([bw, round(througPut, 3)])
            subplots3[bw].append([errorRates[i], round(througPut, 3)]) 
        subplots1[errorRates[i]] = delays    
        subplots2[errorRates[i]] = thPutsvsBW
        
    P.plot(subplots1, "OneWayDelay vs BandWidth", 'errorRate: ', 'BandWidth (Mbps)', "Average one way delay (s)")
    P.plot(subplots2, "Throughput vs BandWidth", 'errorRate: ', 'BandWidth (Mbps)', "Throughput (Kb)")
    P.plot(subplots3, "Throughput vs ErrorRate", 'bandWidth: ', 'ErrorRate', 'Throughput (Kb)')

runMultipleTimes()