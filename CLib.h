#include <stdint.h>
#include <stdio.h>

/**********************************************
********************* BMS *********************
**********************************************/

// Struct Definitions
typedef struct 
{
    int id = 0x6B0;
    int dlc = 8;
    double voltage = 0;
    double current = 0;
    double resistance = 0;
    double health = 0;
    int SOC = 0;
} BMSStatus1;

typedef struct 
{
    int id = 0x6B1;
    int dlc = 6;
    int temperature = 0;
    int plug = 0;
    int relay = 0;
    int pack = 0;
} BMSStatus2;

typedef struct 
{
    int id = 0x6B2;
    int dlc = 4;
    int DTC1 = 0;
    int DTC2 = 0;
    int errors1[16];
    int errors2[16];
} BMSStatus3;

// Function Prototypes
void updateBMSStatus1(BMSStatus1* bms, int data);
void updateBMSStatus2(BMSStatus2* bms, int data);
void updateBMSStatus3(BMSStatus3* bms, int data);

// Function Implementations
void updateBMSStatus1(BMSStatus1* bms, int dataRaw[])
{
    int data = 0;
    for (int i = 0; i < bms->dlc; i++)
    {
        data += (int)dataRaw[i] << (8 * (bms->dlc - (i + 1)));
    }
    bms->voltage = ((data & 0xFFFF000000000000) >> 48) * 0.1;
    bms->current = ((data & 0xFFFF00000000) >> 32) * 0.1;
    bms->resistance = ((data & 0xFF000000) >> 24) * 0.001;
    bms->health = ((data & 0xFFFF00) >> 8) * 0.01;
    bms->SOC = (data & 0xFF);
}

void updateBMSStatus2(BMSStatus2* bms, int dataRaw[])
{
    int data = 0;
    for (int i = 0; i < bms->dlc; i++)
    {
        data += (int)dataRaw[i] << (8 * (bms->dlc - (i + 1)));
    }
    bms->temperature = (data & 0xFFFF0000000000) >> 32;
    bms->plug = (data & 0xFFFF0000) >> 16;
    bms->relay = (data & 0xFF00) >> 8;
    bms->pack = data & 0xFF;
}

void updateBMSStatus3(BMSStatus3* bms, int dataRaw[])
{
    int data = 0;
    for (int i = 0; i < bms->dlc; i++)
    {
        data += (int)dataRaw[i] << (8 * (bms->dlc - (i + 1)));
    }
    bms->DTC1 = (data & 0xFFFF0000) >> 16;
    bms->DTC2 = data & 0xFFFF;
    for (int i = 0; i < 16; i++) 
    {
        bms->errors1[i] = bms->DTC1 & i;
        bms->errors1[i] = bms->DTC2 & i;
    }
}

/**********************************************
********************** MC *********************
**********************************************/

typedef struct 
{
    int id = 0x08850245;
    int dlc = 8;
    double angle = 0;
    double duty = 0;
    int RPM = 0;
    int temp = 0;
    int currentPeak = 0;
    int currentDir = 0;
    int current = 0;
    double voltage = 0;
} RightRear0;

typedef struct 
{
    int id = 0x08850225;
    int dlc = 8;
    double angle = 0;
    double duty = 0;
    int RPM = 0;
    int temp = 0;
    int currentPeak = 0;
    int currentDir = 0;
    int current = 0;
    double voltage = 0;
} LeftRear0;

typedef struct 
{
    int id = 0x08950245;
    int dlc = 5;
    int regen = 0;
    int drive = 0;
    double outputTarg = 0;
    int SWPos = 0;
    double VRPos = 0;
    double accPos = 0;
    int mode = 0;
    int pwrMode = 0;
} RightRear1;

typedef struct 
{
    int id = 0x08950225;
    int dlc = 5;
    int regen = 0;
    int drive = 0;
    double outputTarg = 0;
    int SWPos = 0;
    double VRPos = 0;
    double accPos = 0;
    int mode = 0;
    int pwrMode = 0;
} LeftRear1;

typedef struct 
{
    int id = 0x08A50245;
    int dlc = 5;
    int overheat = 0;
    int hallOpen = 0;
    int hallShort = 0;
    int lock = 0;
    int systemError = 0;
    int overCurrentLimit = 0;
    int overVoltageError = 0;
    int overCurrentError = 0;
    int pwrError = 0;
    int voltSenseError = 0;
    int accPosError = 0;
    int motorCurrAdjError = 0;
    int battCurrAdjError = 0;
    int battCurrSenseError = 0;
    int battVoltSenseError = 0;
    int FETError = 0;
    int motorCurrWError = 0;
    int motorCurrUError = 0;
    int analogError = 0;
} RightRear2;

typedef struct
{
    int id = 0x08A50225;
    int dlc = 5;
    int overheat = 0;
    int hallOpen = 0;
    int hallShort = 0;
    int lock = 0;
    int systemError = 0;
    int overCurrentLimit = 0;
    int overVoltageError = 0;
    int overCurrentError = 0;
    int pwrError = 0;
    int voltSenseError = 0;
    int accPosError = 0;
    int motorCurrAdjError = 0;
    int battCurrAdjError = 0;
    int battCurrSenseError = 0;
    int battVoltSenseError = 0;
    int FETError = 0;
    int motorCurrWError = 0;
    int motorCurrUError = 0;
    int analogError = 0;
} LeftRear2;

typedef struct
{
    int id = 0x08F89540;
    int dlc = 1;
    int frame0 = 0;
    int frame1 = 0;
    int frame2 = 0;
    int data[1];
} MCRequestLeft;

typedef struct
{
    int id = 0x08F91540;
    int dlc = 1;
    int frame0 = 0;
    int frame1 = 0;
    int frame2 = 0;
    int data[1];
} MCRequestRight;

// Function Prototypes
void updateRightRear0(RightRear0* rr, int data);
void updateLeftRear0(LeftRear0* lr, int data);
void updateRightRear1(RightRear1* rr, int data);
void updateLeftRear1(LeftRear1* lr, int data);
void updateRightRear2(RightRear2* rr, int data);
void updateLeftRear2(LeftRear2* lr, int data);
void updateMCRequestLeft(MCRequestLeft* mc, int fr0, int fr1, int fr2);
void updateMCRequestRight(MCRequestRight* mc, int fr0, int fr1, int fr2);

// Function Implementations
void updateRightRear0(RightRear0* rr, int dataRaw[])
{
    int data = 0;
    for (int i = 0; i < rr->dlc; i++)
    {
        data += (int)dataRaw[i] << (8 * (rr->dlc - (i + 1)));
    }
    rr->angle = ((data & 0xFE00000000000000) >> 57) * 0.5;
    rr->duty = ((data & 0x1F8000000000000) >> 47) * 0.005;
    rr->RPM = (data & 0x7FF800000000) >> 35;
    rr->temp = ((data & 0x7C0000000) >> 30) * 5;
    rr->currentPeak = (data & 0x3FF00000) >> 20;
    rr->currentDir = (data & 0x80000) >> 19;
    rr->current = (data & 0x7FC00) >> 10;
    rr->voltage = (data & 0x3FF) * 0.5;
}

void updateLeftRear0(LeftRear0* lr, int dataRaw[])
{
    int data = 0;
    for (int i = 0; i < lr->dlc; i++)
    {
        data += (int)dataRaw[i] << (8 * (lr->dlc - (i + 1)));
    }
    lr->angle = ((data & 0xFE00000000000000) >> 57) * 0.5;
    lr->duty = ((data & 0x1F8000000000000) >> 47) * 0.005;
    lr->RPM = (data & 0x7FF800000000) >> 35;
    lr->temp = ((data & 0x7C0000000) >> 30) * 5;
    lr->currentPeak = (data & 0x3FF00000) >> 20;
    lr->currentDir = (data & 0x80000) >> 19;
    lr->current = (data & 0x7FC00) >> 10;
    lr->voltage = (data & 0x3FF) * 0.5;
}

void updateRightRear1(RightRear1* rr, int dataRaw[])
{
    int data = 0;
    for (int i = 0; i < rr->dlc; i++)
    {
        data += (int)dataRaw[i] << (8 * (rr->dlc - (i + 1)));
    }
    rr->regen = (data & 0x4000000000) >> 38;
    rr->drive = (data & 0x3000000000) >> 36;
    rr->SWPos = (data & 0x3C00000) >> 22;
    rr->VRPos = ((data & 0x3FF000) >> 12) * 0.005;
    rr->accPos = ((data & 0xFFC) >> 2) * 0.005;
    rr->mode = (data & 0x2) >> 1;
    rr->pwrMode = data & 0x1;
    if (rr->pwrMode == 0)
    {
        rr->outputTarg = ((data & 0xFFC000000) >> 26) * 0.5;
    }
    else
    {
        rr->outputTarg = ((data & 0xFFC000000) >> 26) * 0.005;
    }
}

void updateLeftRear1(LeftRear1* lr, int dataRaw[])
{
    int data = 0;
    for (int i = 0; i < lr->dlc; i++)
    {
        data += (int)dataRaw[i] << (8 * (lr->dlc - (i + 1)));
    }
    lr->regen = (data & 0x4000000000) >> 38;
    lr->drive = (data & 0x3000000000) >> 36;
    lr->outputTarg = ((data & 0xFFF00000000000) >> 44) * 0.1;
    lr->SWPos = (data & 0x3C00000) >> 22;
    lr->VRPos = ((data & 0x3FF000) >> 12) * 0.005;
    lr->accPos = ((data & 0xFFC) >> 2) * 0.005;
    lr->mode = (data & 0x2) >> 1;
    lr->pwrMode = data & 0x1;
    if (lr->pwrMode == 0)
    {
        lr->outputTarg = ((data & 0xFFC000000) >> 26) * 0.5;
    }
    else
    {
        lr->outputTarg = ((data & 0xFFC000000) >> 26) * 0.005;
    }
}

void updateRightRear2(RightRear2* rr, int dataRaw[])
{
    int data = 0;
    for (int i = 0; i < rr->dlc; i++)
    {
        data += (int)dataRaw[i] << (8 * (rr->dlc - (i + 1)));
    }
    rr->overheat = (data & 0x300000000) >> 32;
    rr->hallOpen = (data & 0x8000000) >> 27;
    rr->hallShort = (data & 0x4000000) >> 26;
    rr->lock = (data & 0x2000000) >> 25;
    rr->systemError = (data & 0x1000000) >> 24;
    rr->overCurrentLimit = (data & 0x200000) >> 21;
    rr->overVoltageError = (data & 0x80000) >> 19;
    rr->overCurrentError = (data & 0x20000) >> 17;
    rr->pwrError = (data & 0x10000) >> 16;
    rr->voltSenseError = (data & 0x800) >> 11;
    rr->accPosError = (data & 0x200) >> 9;
    rr->motorCurrAdjError = (data & 0x100) >> 8;
    rr->battCurrAdjError = (data & 0x80) >> 7;
    rr->battCurrSenseError = (data & 0x40) >> 6;
    rr->battVoltSenseError = (data & 0x20) >> 5;
    rr->FETError = (data & 0x8) >> 3;
    rr->motorCurrWError = (data & 0x4) >> 2;
    rr->motorCurrUError = (data & 0x2) >> 1;
    rr->analogError = data & 0x1;
}

void updateLeftRear2(LeftRear2* lr, int dataRaw[])
{
    int data = 0;
    for (int i = 0; i < lr->dlc; i++)
    {
        data += (int)dataRaw[i] << (8 * (lr->dlc - (i + 1)));
    }
    lr->overheat = (data & 0x300000000) >> 32;
    lr->hallOpen = (data & 0x8000000) >> 27;
    lr->hallShort = (data & 0x4000000) >> 26;
    lr->lock = (data & 0x2000000) >> 25;
    lr->systemError = (data & 0x1000000) >> 24;
    lr->overCurrentLimit = (data & 0x200000) >> 21;
    lr->overVoltageError = (data & 0x80000) >> 19;
    lr->overCurrentError = (data & 0x20000) >> 17;
    lr->pwrError = (data & 0x10000) >> 16;
    lr->voltSenseError = (data & 0x800) >> 11;
    lr->accPosError = (data & 0x200) >> 9;
    lr->motorCurrAdjError = (data & 0x100) >> 8;
    lr->battCurrAdjError = (data & 0x80) >> 7;
    lr->battCurrSenseError = (data & 0x40) >> 6;
    lr->battVoltSenseError = (data & 0x20) >> 5;
    lr->FETError = (data & 0x8) >> 3;
    lr->motorCurrWError = (data & 0x4) >> 2;
    lr->motorCurrUError = (data & 0x2) >> 1;
    lr->analogError = data & 0x1;
}

void updateMCRequestLeft(MCRequestLeft* mc, int fr0, int fr1, int fr2)
{
    mc->frame0 = fr0;
    mc->frame1 = fr1;
    mc->frame2 = fr2;
    int dataTemp = (fr2 << 2) + (fr1 << 1) + fr0;
    for (int i = 0; i < mc->dlc; i++)
    {
        mc->data[i] = (dataTemp >> (8 * (mc->dlc - (i + 1)))) & 0xFF;
    }
}

void updateMCRequestRight(MCRequestRight* mc, int fr0, int fr1, int fr2)
{
    mc->frame0 = fr0;
    mc->frame1 = fr1;
    mc->frame2 = fr2;
    int dataTemp = (fr2 << 2) + (fr1 << 1) + fr0;
    for (int i = 0; i < mc->dlc; i++)
    {
        mc->data[i] = (dataTemp >> (8 * (mc->dlc - (i + 1)))) & 0xFF;
    }
}

/**********************************************
******************* CHARGER *******************
**********************************************/

typedef struct
{
    int id = 0x18FF50E5;
    int dlc = 5;
    double outputVoltage = 0;
    double outputCurrent = 0;
    int status = 0;
} ChargerSend;

typedef struct
{
    int id = 0x1806E5F4;
    int dlc = 6;
    double maxVoltage = 0;
    double maxCurrent = 0;
    int control1 = 0;
    int control2 = 0;
    double data[6];
} ChargerReceive;

// Function Prototypes
void updateChargerSend(ChargerSend* cs, int data);
void updateChargerReceive(ChargerReceive* cr, double volt, double curr, int cont1, int cont2);
void updateChargerReceiveFromData(ChargerReceive* cr, int data);

// Function Implementations
void updateChargerSend(ChargerSend* cs, int dataRaw[])
{
    int data = 0;
    for (int i = 0; i < cs->dlc; i++)
    {
        data += dataRaw[i] << (8 * (cs->dlc - (i + 1)));
    }
    cs->outputVoltage = ((data & 0xFFFF000000) >> 24) * 0.1;
    cs->outputCurrent = ((data & 0xFFFF00) >> 8) * 0.1;
    cs->status = data & 0xFF;
}

void updateChargerReceive(ChargerReceive* cr, double volt, double curr, int cont1, int cont2)
{
    cr->maxVoltage = volt;
    cr->maxCurrent = curr;
    cr->control1 = cont1;
    cr->control2 = cont2;
    int dataTemp = (((int)(cr->maxVoltage / 0.1) << 32) & 0xFFFF00000000ULL) |
               (((int)(cr->maxCurrent / 0.1) << 16) & 0xFFFF0000ULL) |
               ((int)(cr->control1 << 8) & 0xFF00ULL) |
               ((int)cr->control2 & 0xFFULL);

    for (int i = 0; i < cr->dlc; i++)
    {
        cr->data[i] = (dataTemp >> (8 * (cr->dlc - (i + 1)))) & 0xFF;
    }
}

void updateChargerReceiveFromData(ChargerReceive* cr, int dataRaw[])
{
    int dataIn = 0;
    for (int i = 0; i < cr->dlc; i++)
    {
        dataIn += (dataRaw[i] << (8 * (cr->dlc - (i+1)))) & 0xFF;
    }
    cr->maxVoltage = ((0xFFFF00000000 & dataIn) >> 32) * 0.1;
    cr->maxCurrent = ((dataIn & 0xFFFF0000) >> 16) * 0.1;
    cr->control1 = (dataIn & 0xFF00) >> 8;
    cr->control2 = dataIn & 0xFF;
}


/**********************************************
********************* PMS *********************
**********************************************/

typedef struct
{
    int id = 0x19000001;
    int dlc = 8;
    int auxCurr = 0;
    double auxCurrDec = 0;
    int startup = 0;
    int auxStatus = 0;
    int auxTemp = 0;
    int auxVolt = 0;
    double auxVoltDec = 0;
    int ESTOP = 0;
    int data[8];
} PMSStatus;

// Function Prototypes
void updatePMSStatusSend(PMSStatus* pms, double current, double voltage, int temp, int start, int status, int estop);
void updatePMSStatusReceive(PMSStatus* pms, int data);

// Function Implementations
void updatePMSStatusSend(PMSStatus* pms, double current, double voltage, int temp, int start, int status, int estop)
{
    pms->auxCurr = current / 1;
    pms->auxCurrDec = (current - pms->auxCurr) * 100;
    pms->auxVolt = voltage / 1;
    pms->auxVoltDec = (voltage - pms->auxVolt) * 10;
    pms->auxStatus = status;
    pms->startup = start;
    pms->auxTemp = temp;
    pms->ESTOP = estop;
    int dataTemp = ((int)pms->auxCurr << 56) & 0xFF00000000000000ULL |
                ((int)pms->auxCurrDec << 48) & 0xFF000000000000ULL |
                ((int)pms->startup << 40) & 0xFF0000000000ULL |
                ((int)pms->auxStatus << 32) & 0xFF00000000ULL |
                ((int)pms->auxTemp << 24) & 0xFF000000ULL |
                ((int)pms->auxVolt << 16) & 0xFF0000ULL |
                ((int)pms->auxVoltDec << 8) & 0xFF00ULL |
                (int)pms->ESTOP & 0xFFULL;

    for (int i = 0; i < pms->dlc; i++)
    {
        pms->data[i] = (dataTemp >> (8 * (pms->dlc - (i + 1)))) & 0xFF;
    }
}

void updatePMSStatusReceive(PMSStatus* pms, int dataRaw[])
{
    int dataIn = 0;
    for (int i = 0; i < pms->dlc; i++)
    {
        dataIn += (dataRaw[i] << (8 * (pms->dlc - (i + 1))));
    }
    pms->auxCurr = (dataIn & 0xFF00000000000000) >> 56;
    pms->auxCurrDec = ((dataIn & 0xFF000000000000) >> 48) * 0.01;
    pms->auxVolt = (dataIn & 0xFF0000) >> 16;
    pms->auxVoltDec = ((dataIn & 0xFF00) >> 8) * 0.1;
    pms->startup = (dataIn & 0xFF0000000000) >> 40;
    pms->auxStatus = (dataIn & 0xFF00000000) >> 32;
    pms->auxTemp = (dataIn & 0xFF000000) >> 24;
    pms->ESTOP = dataIn & 0xFF;
}

/**********************************************
********************* FAN *********************
**********************************************/

typedef struct
{
    int id = 0x1B100001;
    int dlc = 8;
    int fans[8];
} FANSTAT1;

typedef struct
{
    int id = 0x1B200001;
    int dlc = 8;
    int fans[8];
} FANSTAT2;

typedef struct
{
    int id = 0x1B300001;
    int dlc = 2;
    int rq1 = 0;
    int rq2 = 0;
    int data[2];
} FANRequest;

// Function Prototypes
void updateFANSTAT1(FANSTAT1* fan, int data);
void updateFANSTAT2(FANSTAT2* fan, int data);
void updateFANRequest(FANRequest* fan, int req1, int req2);

// Function Implementations
void updateFANSTAT1(FANSTAT1* fan, int dataRaw[])
{
    int data = 0;
    for (int i = 0; i < fan->dlc; i++)
    {
        data += dataRaw[i] << (8 * (fan->dlc - (i + 1)));
    }
    fan->fans[0] = (data & 0xFF00000000000000) >> 56;
    fan->fans[1] = (data & 0xFF000000000000) >> 48;
    fan->fans[2] = (data & 0xFF0000000000) >> 40;
    fan->fans[3] = (data & 0xFF00000000) >> 32;
    fan->fans[4] = (data & 0xFF0000000) >> 24;
    fan->fans[5] = (data & 0xFF0000) >> 16;
    fan->fans[6] = (data & 0xFF00) >> 8;
    fan->fans[7] = data & 0xFF;
}

void updateFANSTAT2(FANSTAT2* fan, int dataRaw[])
{
    int data = 0;
    for (int i = 0; i < fan->dlc; i++)
    {
        data += dataRaw[i] << (8 * (fan->dlc - (i + 1)));
    }
    fan->fans[0] = (data & 0xFF00000000000000) >> 56;
    fan->fans[1] = (data & 0xFF000000000000) >> 48;
    fan->fans[2] = (data & 0xFF0000000000) >> 40;
    fan->fans[3] = (data & 0xFF00000000) >> 32;
    fan->fans[4] = (data & 0xFF0000000) >> 24;
    fan->fans[5] = (data & 0xFF0000) >> 16;
    fan->fans[6] = (data & 0xFF00) >> 8;
    fan->fans[7] = data & 0xFF;
}

void updateFANRequest(FANRequest* fan, int req1, int req2)
{
    fan->rq1 = req1;
    fan->rq2 = req2;
    int dataTemp = (0xFF00 & (fan->rq1 << 8)) + (0xFF & fan->rq2);
    for (int i = 0; i < fan->dlc; i++)
    {
        fan->data[i] = (dataTemp >> (8 * (fan->dlc - (i + 1)))) & 0xFF;
    }
}

/**********************************************
********************* PCB *********************
**********************************************/

typedef struct
{
    int id = 0x1C100001;
    int dlc = 4;
    int motorError = 0;
    int regen = 0;
    int brake = 0;
    int neutral = 0;
    int data[4];
} PCBMessage;

// Function Prototypes
void updatePCBMessageSend(PCBMessage* pcb, int motor, int reg, int brk, int neut);
void updatePCBMessageReceive(PCBMessage* pcb, int data);

// Function Implementations
void updatePCBMessageSend(PCBMessage* pcb, int motor, int reg, int brk, int neut)
{
    pcb->motorError = motor;
    pcb->regen = reg;
    pcb->brake = brk;
    pcb->neutral = neut;
    int dataTemp = ((pcb->motorError << 24) & 0xFF000000)
                + ((pcb->regen << 16) & 0xFF0000)
                + ((pcb->brake << 8) & 0xFF00)
                + (pcb->neutral & 0xFF);

    for (int i = 0; i < pcb->dlc; i++)
    {
        pcb->data[i] = (dataTemp >> (8 * (pcb->dlc - (i + 1)))) & 0xFF;
    }
}

void updatePCBMessageReceive(PCBMessage* pcb, int dataRaw[])
{
    int dataIn = 0;
    for (int i = 0; i < pcb->dlc; i++)
    {
        dataIn += dataRaw[i] << (8 * (pcb->dlc - (i + 1)));
    }
    pcb->motorError = (dataIn & 0xFF000000) >> 24;
    pcb->regen = (dataIn & 0xFF0000) >> 16;
    pcb->brake = (dataIn & 0xFF00) >> 8;
    pcb->neutral = dataIn & 0xFF;
}

/**********************************************
********************* MPPT ********************
**********************************************/

typedef struct
{
    int id = 0x1D100001;
    int dlc = 4;
    int volt = 0;
    double voltDec = 0;
    int curr = 0;
    double currDec = 0;
    int data[4];
} MPPTSend;

// Function Prototypes
void updateMPPTSend(MPPTSend* mppt, double voltage, double current);
void updateMPPTReceive(MPPTSend* mppt, int data);

// Function Implementations
void updateMPPTSend(MPPTSend* mppt, double voltage, double current)
{
    mppt->curr = current / 1;
    mppt->currDec = (current - mppt->curr) * 10;
    mppt->volt = voltage / 1;
    mppt->voltDec = (voltage - mppt->volt) * 10; 
    int dataTemp = (((int)mppt->voltDec << 24) & 0xFF000000)
                + (((int)mppt->volt << 16) & 0xFF0000)
                + (((int)mppt->currDec << 8) & 0xFF00)
                + (mppt->curr & 0xFF);

    for (int i = 0; i < mppt->dlc; i++)
    {
        mppt->data[i] = (dataTemp >> (8 * (mppt->dlc - (i + 1)))) & 0xFF;
    }
}

void updateMPPTReceive(MPPTSend* mppt, int dataRaw[])
{
    int dataIn = 0;
    for (int i = 0; i < mppt->dlc; i++)
    {
        dataIn += dataRaw[i] << (8 * (mppt->dlc - (i + 1)));
    }
    mppt->curr = dataIn & 0xFF;
    mppt->currDec = ((dataIn & 0xFF00) >> 8) * 0.1;
    mppt->volt = (dataIn & 0xFF0000) >> 16;
    mppt->voltDec = ((dataIn & 0xFF000000) >> 24);
}
