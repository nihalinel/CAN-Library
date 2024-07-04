#############################################
#--------------------BMS--------------------#
#############################################



class BMSStatus1:
    def __init__(self):
        self.id = 0x6B0
        self.dlc = 8
        self.voltage = 0
        self.current = 0
        self.resistance = 0
        self.health = 0
        self.SOC = 0

    def updateVals(self, dataRaw):
        data = 0
        for i in range(0,self.dlc):
            data = data + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.voltage = ((data & 0xFFFF000000000000) >> 48) * 0.1        
        self.current = ((data & 0xFFFF00000000) >> 32) * 0.1
        self.resistance = ((data & 0xFF000000) >> 24) * 0.001 #conversion to ohms
        self.health = ((data & 0xFFFF00) >> 8) * 0.01
        self.SOC = (data & 0xFF)


class BMSStatus2:
    def __init__(self):
        self.id = 0x6B1
        self.dlc = 6
        self.temperature = 0
        self.plug = 0
        self.relay = 0
        self.pack = 0

    def updateVals(self,dataRaw):
        data = 0
        for i in range(0, self.dlc):
            data = data + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.temperature = (data & 0xFFFF0000000000) >> 32
        self.plug = (data & 0xFFFF0000) >> 16
        self.relay = (data & 0xFF00) >> 8
        self.pack = data & 0xFF

class BMSStatus3:
    def __init__(self):
        self.id = 0x6B2
        self.dlc = 4
        self.DTC1 = 0
        self.DTC2 = 0
        self.errors1 = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
        self.errors2 = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

    def updateVals(self,dataRaw):
        data = 0
        for i in range(0, self.dlc):
            data = data + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.DTC1 = (data & 0xFFFF0000) >> 16
        self.DTC2 = data & 0xFFFF
        for i in range(0,16):
            self.errors1[i] = self.DTC1 & i
            self.errors2[i] = self.DTC2 & i



#############################################       
#--------------------MC---------------------#
#############################################

class rightRear0:
    def __init__(self):
        self.id = 0x08850245
        self.dlc = 8
        self.angle = 0
        self.duty = 0
        self.RPM = 0
        self.temp = 0
        self.currentPeak = 0
        self.currentDir = 0
        self.current = 0
        self.voltage = 0

    def updateVals(self,dataRaw):
        data = 0
        for i in range(0, self.dlc):
            data = data + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.angle = ((data & 0xFE00000000000000) >> 57) * 0.5
        self.duty = ((data & 0x1F8000000000000) >> 47) * 0.005
        self.RPM = (data & 0x7FF800000000) >> 35
        self.temp = ((data & 0x7C0000000) >> 30) * 5
        self.currentPeak = (data & 0x3FF00000) >> 20
        self.currentDir = (data & 0x80000) >> 19
        self.current = (data & 0x7FC00) >> 10
        self.voltage = (data & 0x3FF) * 0.5

class leftRear0:
    def __init__(self):
        self.id = 0x08850225
        self.dlc = 8
        self.angle = 0
        self.duty = 0
        self.RPM = 0
        self.temp = 0
        self.currentPeak = 0
        self.currentDir = 0
        self.current = 0
        self.voltage = 0

    def updateVals(self,dataRaw):
        data = 0
        for i in range(0, self.dlc):
            data = data + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.angle = ((data & 0xFE00000000000000) >> 57) * 0.5
        self.duty = ((data & 0x1F8000000000000) >> 47) * 0.005
        self.RPM = (data & 0x7FF800000000) >> 35
        self.temp = ((data & 0x7C0000000) >> 30) * 5
        self.currentPeak = (data & 0x3FF00000) >> 20
        self.currentDir = (data & 0x80000) >> 19
        self.current = (data & 0x7FC00) >> 10
        self.voltage = (data & 0x3FF) * 0.5

class rightRear1:
    def __init__(self):
        self.id = 0x08950245
        self.dlc = 5
        self.regen = 0
        self.drive = 0
        self.outputTarg = 0
        self.SWPos = 0
        self.VRPos = 0
        self.accPos = 0
        self.mode = 0
        self.pwrMode = 0

    def updateVals(self, dataRaw):
        data = 0
        for i in range(0, self.dlc):
            data = data + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.regen = (data & 0x4000000000) >> 38
        self.drive = (data & 0x3000000000) >> 36
        self.SWPos = (data & 0x3C00000) >> 22
        self.VRPos = ((data & 0x3FF000) >> 12) * 0.005
        self.accPos = ((data & 0xFFC) >> 2) * 0.005
        self.mode = (data & 0x2) >> 1
        self.pwrMode = data & 0x1
        if (self.pwrMode == 0):
            self.outputTarg = ((data & 0xFFC000000) >> 26) * 0.5
        else:
            self.outputTarg = ((data & 0xFFC000000) >> 26) * 0.005


class leftRear1:
    def __init__(self):
        self.id = 0x08950225
        self.dlc = 5
        self.regen = 0
        self.drive = 0
        self.outputTarg = 0
        self.SWPos = 0
        self.VRPos = 0
        self.accPos = 0
        self.mode = 0
        self.pwrMode = 0

    def updateVals(self, dataRaw):
        data = 0
        for i in range(0, self.dlc):
            data = data + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.regen = (data & 0x4000000000) >> 38
        self.drive = (data & 0x3000000000) >> 36
        self.SWPos = (data & 0x3C00000) >> 22
        self.VRPos = ((data & 0x3FF000) >> 12) * 0.005
        self.accPos = ((data & 0xFFC) >> 2) * 0.005
        self.mode = (data & 0x2) >> 1
        self.pwrMode = data & 0x1
        if (self.pwrMode == 0):
            self.outputTarg = ((data & 0xFFC000000) >> 26) * 0.5
        else:
            self.outputTarg = ((data & 0xFFC000000) >> 26) * 0.005

class rightRear2:
    def __init__(self):
        self.id = 0x08A50245
        self.dlc = 5
        self.overheat = 0
        self.hallOpen = 0
        self.hallShort = 0
        self.lock = 0
        self.systemError = 0
        self.overCurrentLimit = 0
        self.overVoltageError = 0
        self.overCurrentError = 0
        self.pwrError = 0
        self.voltSenseError = 0
        self.accPosError = 0
        self.motorCurrAdjError = 0
        self.battCurrAdjError = 0
        self.battCurrSenseError = 0
        self.battVoltSenseError = 0
        self.FETError = 0
        self.motorCurrWError = 0
        self.motorCurrUError = 0
        self.analogError = 0

    def updateVals(self, dataRaw):
        data = 0
        for i in range(0, self.dlc):
            data = data + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.overheat = (data & 0x300000000) >> 32
        self.hallOpen = (data & 0x8000000) >> 27
        self.hallShort = (data & 0x4000000) >> 26
        self.lock = (data & 0x2000000) >> 25
        self.systemError = (data & 0x1000000) >> 24
        self.overCurrentLimit = (data & 0x200000) >> 21
        self.overVoltageError = (data & 0x80000) >> 19
        self.overCurrentError = (data & 0x20000) >> 17
        self.pwrError = (data & 0x10000) >> 16
        self.voltSenseError = (data & 0x800) >> 11
        self.accPosError = (data & 0x200) >> 9
        self.motorCurrAdjError = (data & 0x100) >> 8
        self.battCurrAdjError = (data & 0x80) >> 7
        self.battCurrSenseError = (data & 0x40) >> 6
        self.battVoltSenseError = (data & 0x20) >> 5
        self.FETError = (data & 0x8) >> 3
        self.motorCurrWError = (data & 0x4) >> 2
        self.motorCurrUError = (data & 0x2) >> 1
        self.analogError = data & 0x1

class leftRear2:
    def __init__(self):
        self.id = 0x08A50225
        self.dlc = 5
        self.overheat = 0
        self.hallOpen = 0
        self.hallShort = 0
        self.lock = 0
        self.systemError = 0
        self.overCurrentLimit = 0
        self.overVoltageError = 0
        self.overCurrentError = 0
        self.pwrError = 0
        self.voltSenseError = 0
        self.accPosError = 0
        self.motorCurrAdjError = 0
        self.battCurrAdjError = 0
        self.battCurrSenseError = 0
        self.battVoltSenseError = 0
        self.FETError = 0
        self.motorCurrWError = 0
        self.motorCurrUError = 0
        self.analogError = 0

    def updateVals(self, dataRaw):
        data = 0
        for i in range(0, self.dlc):
            data = data + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.overheat = (data & 0x300000000) >> 32
        self.hallOpen = (data & 0x8000000) >> 27
        self.hallShort = (data & 0x4000000) >> 26
        self.lock = (data & 0x2000000) >> 25
        self.systemError = (data & 0x1000000) >> 24
        self.overCurrentLimit = (data & 0x200000) >> 21
        self.overVoltageError = (data & 0x80000) >> 19
        self.overCurrentError = (data & 0x20000) >> 17
        self.pwrError = (data & 0x10000) >> 16
        self.voltSenseError = (data & 0x800) >> 11
        self.accPosError = (data & 0x200) >> 9
        self.motorCurrAdjError = (data & 0x100) >> 8
        self.battCurrAdjError = (data & 0x80) >> 7
        self.battCurrSenseError = (data & 0x40) >> 6
        self.battVoltSenseError = (data & 0x20) >> 5
        self.FETError = (data & 0x8) >> 3
        self.motorCurrWError = (data & 0x4) >> 2
        self.motorCurrUError = (data & 0x2) >> 1
        self.analogError = data & 0x1
        

class MCRequestLeft:
    def __init__(self):
        self.id = 0x08F89540
        self.dlc = 1
        self.frame0 = 0
        self.frame1 = 0
        self.frame2 = 0
        self.data = 0
    
    def updateVals(self,fr0, fr1, fr2):
        self.frame0 = fr0
        self.frame1 = fr1
        self.frame2 = fr2
        dataTemp = (fr2 << 2) + (fr1 << 1) + fr0
        for i in range(0,self.dlc):
            self.data[i] = (dataTemp >> (8 * (self.dlc - (i + 1)))) & 0xFF


class MCRequestRight:
    def __init__(self):
        self.id = 0x08F91540
        self.dlc = 1
        self.frame0 = 0
        self.frame1 = 0
        self.frame2 = 0
        self.data = [0]

    def updateVals(self, fr0, fr1, fr2):
        self.frame0 = fr0
        self.frame1 = fr1
        self.frame2 = fr2
        dataTemp = (fr2 << 2) + (fr1 << 1) + fr0
        for i in range(0,self.dlc):
            self.data[i] = (dataTemp >> (8 * (self.dlc - (i + 1)))) & 0xFF

#############################################       
#-----------------CHARGER-------------------#
#############################################

class chargerSend:
    def __init__(self):
        self.id = 0x18FF50E5
        self.dlc = 5
        self.outputVoltage = 0
        self.outputCurrent = 0
        self.status = 0

    def updateVals(self, dataRaw):
        data = 0
        for i in range(0, self.dlc):
            data = data + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.outputVoltage = ((data & 0xFFFF000000) >> 24) * 0.1
        self.outputCurrent = ((data & 0xFFFF00) >> 8) * 0.1
        self.status = data & 0xFF 

class chargerReceive:
    def __init__(self):
        self.id = 0x1806E5F4
        self.dlc = 6
        self.maxVoltage = 0
        self.maxCurrent = 0
        self.control1 = 0
        self.control2 = 0
        self.data = [0,0,0,0,0,0]
    
    def updateSend(self,volt, curr, cont1, cont2):
        self.voltage = volt
        self.current = curr
        self.control1 = cont1
        self.control2 = cont2
        dataTemp = (((self.voltage / 0.1) << 32) & 0xFFFF00000000) + (((self.current / 0.1) << 16) & 0xFFFF0000) + ((self.control1 << 8) & 0xFF00) + (self.control2 & 0xFF)
        for i in range(0,self.dlc):
            self.data[i] = (dataTemp >> (8 * (self.dlc - (i + 1)))) & 0xFF

    def updateReceive(self, dataRaw):
        dataIn = 0
        for i in range(0, self.dlc):
            dataIn = dataIn + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.voltage = ((0xFFFF00000000 & dataIn) >> 32) * 0.1
        self.current = ((dataIn & 0xFFFF0000) >> 16) * 0.1
        self.control1 = (dataIn & 0xFF00) >> 8
        self.control2 = dataIn & 0xFF

#############################################       
#--------------------PMS--------------------#
#############################################

class PMSStatus:
    def __init__(self):
        self.id = 0x19000001
        self.dlc = 8
        self.auxCurr = 0
        self.auxCurrDec = 0
        self.startup = 0
        self.auxStatus = 0
        self.auxTemp = 0
        self.auxVolt = 0
        self.auxVoltDec = 0
        self.ESTOP = 0
        self.data = [0,0,0,0,0,0,0,0]

    def updateSend(self,current, voltage, temp, start, status, estop):
        self.auxCurr = current // 1
        self.auxCurrDec = (current - self.auxCurr) * 100
        self.auxVolt = voltage // 1
        self.auxVoltDec = (voltage - self.auxVolt) * 10
        self.auxStatus = status
        self.startup = start
        self.auxTemp = temp
        self.ESTOP = estop
        dataTemp = ((self.auxCurr << 56) & 0xFF00000000000000) + ((self.auxCurrDec << 48) & 0xFF000000000000) + ((self.startup << 40) & 0xFF0000000000) + ((self.auxStatus << 32) & 0xFF00000000) + ((self.auxTemp << 24) & 0xFF000000) + ((self.auxVolt << 16) & 0xFF0000) + ((self.auxVoltDec << 8) & 0xFF00) + (self.ESTOP & 0xFF)
        for i in range(0,self.dlc):
            self.data[i] = (dataTemp >> (8 * (self.dlc - (i + 1)))) & 0xFF

    def updateReceive(self, dataRaw):
        dataIn = 0
        for i in range(0, self.dlc):
            dataIn = dataIn + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.auxCurr = (dataIn & 0xFF00000000000000) >> 56
        self.auxCurrDec = ((dataIn & 0xFF000000000000) >> 48) * 0.01
        self.auxVolt = (dataIn & 0xFF0000) >> 16
        self.auxVoltDec = ((dataIn & 0xFF00) >> 8) * 0.1
        self.startup = (dataIn & 0xFF0000000000) >> 40
        self.auxStatus = (dataIn & 0xFF00000000) >> 32
        self.auxTemp = (dataIn & 0xFF000000) >> 24
        self.ESTOP = dataIn & 0xFF


#############################################       
#--------------------FAN--------------------#
#############################################

class FANSTAT1:
    def __init__(self):
        self.id = 0x1B100001
        self.dlc = 8
        self.fans = [0,0,0,0,0,0,0,0]

    def updateVals(self,dataRaw):
        data = 0
        for i in range(0, self.dlc):
            data = data + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.fans[0] = (data & 0xFF00000000000000) >> 56
        self.fans[1] = (data & 0xFF000000000000) >> 48
        self.fans[2] = (data & 0xFF0000000000) >> 40
        self.fans[3] = (data & 0xFF00000000) >> 32
        self.fans[4] = (data & 0xFF0000000) >> 24
        self.fans[5] = (data & 0xFF0000) >> 16
        self.fans[6] = (data & 0xFF00) >> 8
        self.fans[7] = data & 0xFF

class FANSTAT2:
    def __init__(self):
        self.id = 0x1B200001
        self.dlc = 8
        self.fans = [0,0,0,0,0,0,0,0]

    def updateVals(self,dataRaw):
        data = 0
        for i in range(0, self.dlc):
            data = data + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.fans[0] = (data & 0xFF00000000000000) >> 56
        self.fans[1] = (data & 0xFF000000000000) >> 48
        self.fans[2] = (data & 0xFF0000000000) >> 40
        self.fans[3] = (data & 0xFF00000000) >> 32
        self.fans[4] = (data & 0xFF0000000) >> 24
        self.fans[5] = (data & 0xFF0000) >> 16
        self.fans[6] = (data & 0xFF00) >> 8
        self.fans[7] = data & 0xFF

class FANRequest:
    def __init__(self):
        self.id = 0x1B300001
        self.dlc =2
        self.rq1 = 0
        self.rq2 = 0
        self.data = [0,0]
    
    def updateVals(self,req1,req2):
        self.rq1 = req1
        self.rq2 = req2
        dataTemp = (0xFF00 & (self.rq1 << 8)) + (0xFF & self.rq2)
        for i in range(0,self.dlc):
            self.data[i] = (dataTemp >> (8 * (self.dlc - (i + 1)))) & 0xFF

#############################################       
#--------------------PCB--------------------#
#############################################

class PCBMessage:
    def __init__(self):
        self.id = 0x1C100001
        self.dlc = 4
        self.motorError = 0
        self.regen = 0
        self.brake = 0
        self.neutral = 0
        self.data = [0,0,0,0]

    def updateSend(self,motor, reg, brk, neut):
        self.motorError = motor
        self.regen = reg
        self.brake = brk
        self.neutral = neut
        dataTemp = ((self.motorError << 24) & 0xFF000000) + ((self.regen << 16) & 0xFF0000) + ((self.brake << 8) & 0xFF00) + (self.neutral & 0xFF)
        for i in range(0,self.dlc):
            self.data[i] = (dataTemp >> (8 * (self.dlc - (i + 1)))) & 0xFF

    def updateReceive(self, dataRaw):
        dataI = 0
        for i in range(0, self.dlc):
            dataIn = dataIn + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.motorError = (dataIn & 0xFF000000) >> 24
        self.regen = (dataIn & 0xFF0000) >> 16
        self.brake = (dataIn & 0xFF00) >> 8
        self.neutral = dataIn & 0xFF 

#############################################       
#-------------------MPPT--------------------#
#############################################

class MPPTSend:
    def __init__(self):
        self.id = 0x1D100001
        self.dlc = 4
        self.volt = 0
        self.voltDec = 0
        self.curr = 0
        self.currDec = 0
        self.data = [0,0,0,0]

    def updateSend(self,voltage,current):
        self.curr = current // 1
        self.currDec = (current - self.curr) * 10
        self.volt = voltage // 1
        self.voltDec = (voltage - self.volt) * 10 
        dataTemp = ((self.voltDec << 24) & 0xFF000000) + ((self.volt << 16) & 0xFF0000) + ((self.currDec << 8) & 0xFF00) + (self.curr & 0xFF)
        for i in range(0,self.dlc):
            self.data[i] = (dataTemp >> (8 * (self.dlc - (i + 1)))) & 0xFF

    def updateReceive(self,dataRaw):
        dataIn = 0
        for i in range(0, self.dlc):
            dataIn = dataIn + (dataRaw[i] << (8 * (self.dlc - (i + 1))))
        self.curr = dataIn & 0xFF
        self.currDec = ((dataIn & 0xFF00) >> 8) * 0.1
        self.volt = (dataIn & 0xFF0000) >> 16
        self.voltDec = ((dataIn & 0xFF000000) >> 24)