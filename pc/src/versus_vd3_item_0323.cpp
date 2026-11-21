// Work item 0323: AActor vtable slots 58 and 35, AMover slot 35.
// Field names are neutral (offsets) where UE2 evidence is not conclusive.

typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef float FLOAT;
typedef int INT;

struct FVector { FLOAT X, Y, Z; };

// Output record filled by the slot-35 functions (neutral name).
struct FActorStateRecord
{
    FVector V00;        // 0x00  <- Actor+0x80
    FVector V0C;        // 0x0c  <- Actor+0xa4
    FVector V18;        // 0x18  <- Mover+0x304
    FVector V24;        // 0x24  <- Actor+0xb0
    FVector V30;        // 0x30  <- Actor+0xe0
    FVector V3C;        // 0x3c  <- Actor+0xec
    DWORD   D48;        // 0x48
    DWORD   D4C;        // 0x4c
    DWORD   D50;        // 0x50
    DWORD   D54;        // 0x54
    DWORD   D58;        // 0x58
    BYTE    B5C;        // 0x5c
    BYTE    Pad5D[0x88 - 0x5d];
    DWORD   D88;        // 0x88
    DWORD   D8C;        // 0x8c
};

struct ULevel
{
    BYTE  Pad[0x3a48];
    void *Obj3A48;
};

class AActor;
void __stdcall FUN_10a19a20(void *Obj, AActor *Actor);



class AActor
{
public:
    BYTE    Pad000[0x80];
    FVector F080;       // 0x80
    BYTE    Pad08C[0xa4 - 0x8c];
    FVector F0A4;       // 0xa4
    FVector F0B0;       // 0xb0
    BYTE    Pad0BC[0xe0 - 0xbc];
    FVector F0E0;       // 0xe0
    FVector F0EC;       // 0xec
    BYTE    Pad0F8[0x100 - 0xf8];
    DWORD   F100;       // 0x100
    BYTE    Pad104[0x108 - 0x104];
    DWORD   F108;       // 0x108
    BYTE    Pad10C[0x1a4 - 0x10c];
    ULevel *XLevel;     // 0x1a4
    BYTE    Pad1A8[0x23c - 0x1a8];
    DWORD   F23C;       // 0x23c
    BYTE    Pad240[0x24c - 0x240];
    DWORD   F24C;       // 0x24c
    BYTE    Pad250[0x2a8 - 0x250];
    DWORD   F2A8;       // 0x2a8
    DWORD   F2AC;       // 0x2ac
    BYTE    Pad2B0[0x2d9 - 0x2b0];
    BYTE    F2D9;       // 0x2d9
    BYTE    Pad2DA[0x2e3 - 0x2da];
    BYTE    F2E3;       // 0x2e3
    BYTE    Pad2E4[0x2f0 - 0x2e4];
    DWORD   Flags2F0;   // 0x2f0

    FLOAT Slot58(FLOAT Value);
    void  Slot35(FActorStateRecord *Out);
};

class AMover : public AActor
{
public:
    BYTE    Pad2F4[0x304 - 0x2f4];
    FVector F304;       // 0x304

    void Slot35(FActorStateRecord *Out);
};

// RVA 0x8f010, AActor vtable slot 58
FLOAT AActor::Slot58(FLOAT Value)
{
    return (FLOAT)F2E3 * Value * (1.f / 255.f);
}

// RVA 0x8f030, AActor vtable slot 35
void AActor::Slot35(FActorStateRecord *Out)
{
    Out->V00 = F080;
    Out->V30 = F0E0;
    Out->V0C = F0A4;
    Out->V3C = F0EC;
    Out->D48 = F108;
    Out->D4C = (Flags2F0 >> 12) & 1;
    Out->D50 = F2A8;
    Out->D54 = F2AC;
    Out->D58 = F23C;
    Out->V24 = F0B0;
    Out->B5C = F2D9;
    Out->D88 = F24C;
    Out->D8C = F100;
    if (Flags2F0 & 0x1000)
        FUN_10a19a20(XLevel->Obj3A48, this);
}

// RVA 0x8f160, AMover vtable slot 35
void AMover::Slot35(FActorStateRecord *Out)
{
    Out->V18 = F304;
    AActor::Slot35(Out);
}
