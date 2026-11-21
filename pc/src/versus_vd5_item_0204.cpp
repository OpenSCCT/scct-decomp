// Work item 0204: UPCSaveGameDevice operation-queue helpers (RVA 0xe60b0-0xe620d).
// Layout recovered from the code only; field names are descriptive guesses.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString &operator=(const FString &Other);
    ~FString();
};

class UPCSaveGameDevice
{
public:
    virtual void Vf00(); virtual void Vf04(); virtual void Vf08(); virtual void Vf0c();
    virtual void Vf10(); virtual void Vf14(); virtual void Vf18(); virtual void Vf1c();
    virtual void Vf20(); virtual void Vf24(); virtual void Vf28(); virtual void Vf2c();
    virtual void Vf30(); virtual void Vf34(); virtual void Vf38(); virtual void Vf3c();
    virtual void Vf40(); virtual void Vf44(); virtual void Vf48(); virtual void Vf4c();
    virtual void Vf50(); virtual void Vf54(); virtual void Vf58(); virtual void Vf5c();
    virtual void Vf60(); virtual void Vf64(); virtual void Vf68(); virtual void Vf6c();
    virtual void StartNextOperation();              // vtable +0x70

    INT Pad04[15];          // 0x04
    INT OpDone[3];          // 0x40, 0x44, 0x48 (indexed by op type - 3)
    INT Pad4c;              // 0x4c
    INT Progress;           // 0x50
    INT Pad54[11];          // 0x54
    FString PendingName;    // 0x80
    INT Pad8c[6];           // 0x8c
    INT Status[3];          // 0xa4, 0xa8, 0xac
    INT Padb0;              // 0xb0
    INT OpType[16];         // 0xb4
    INT OpParam[16];        // 0xf4
    INT OpCount;            // 0x134

    UBOOL QueueOp(INT Type)
    {
        OpType[OpCount] = Type;
        OpParam[OpCount] = 0;
        OpCount++;
        OpDone[Type - 3] = 0;
        if (OpCount == 1) {
            Progress = 0;
            Status[Type - 3] = 0;
            StartNextOperation();
        }
        return 1;
    }
    UBOOL QueueOp3(FString Name);
    UBOOL QueueOp4();
    UBOOL QueueOp5();
    UBOOL IsIdle();
};

// RVA 0xe60b0 (LTCG: this in ESI)
UBOOL UPCSaveGameDevice::QueueOp3(FString Name)
{
    PendingName = Name;
    return QueueOp(3);
}

// RVA 0xe6150
UBOOL UPCSaveGameDevice::QueueOp4()
{
    return QueueOp(4);
}

// RVA 0xe61a0
UBOOL UPCSaveGameDevice::QueueOp5()
{
    return QueueOp(5);
}

// RVA 0xe61f0 (vtable slot 25)
UBOOL UPCSaveGameDevice::IsIdle()
{
    if (OpCount && OpType[0])
        return 0;
    return 1;
}

// Scaffolding for the LTCG link, not part of the unit.
void Driver_e60b0(UPCSaveGameDevice *D, FString *S) { D->QueueOp3(*S); }
void Driver_e6150(UPCSaveGameDevice *D) { D->QueueOp4(); }
void Driver_e61a0(UPCSaveGameDevice *D) { D->QueueOp5(); }
