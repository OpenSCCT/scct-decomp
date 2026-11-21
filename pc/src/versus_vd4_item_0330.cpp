// Work item 0330: Versus RVA 0x91300, AActor::SetOwner (LTCG: this in ESI, NewOwner in EBX).
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;

enum EName {
    NAME_None = 0,
    NAME_PROBEMIN = 300,
    NAME_GainedChild = 302,  // probe 2 in this build
    NAME_LostChild = 303,    // probe 3 in this build
};

class FName {
public:
    INT Index;
    FName(EName N) : Index(N) {}
    INT GetIndex() const { return Index; }
};

class UFunction;

#pragma pack(push, 4)
struct FStateFrame {
    BYTE Pad[0x1c];
    QWORD ProbeMask;         // 0x1c
};
#pragma pack(pop)

class UObject {
public:
    virtual void VSlot0();
    virtual void VSlot1();
    virtual void VSlot2();
    virtual void VSlot3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    UFunction *FindFunctionChecked(FName Name, INT Global = 0);

    INT Index;               // 0x04
    UObject *HashNext;       // 0x08
    FStateFrame *StateFrame; // 0x0c

    INT IsProbing(FName ProbeName)
    {
        return !StateFrame
            || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
    }
};

class AActor : public UObject {
public:
    BYTE Pad10[0x104 - 0x10];
    AActor *Owner;           // 0x104
    BYTE Pad108[0x2ec - 0x108];
    DWORD Flags2ec;          // 0x2ec, bit 2 = bNetDirty

    void eventLostChild(AActor *Other)
    {
        if (IsProbing(NAME_LostChild)) {
            struct { AActor *Other; } Parms;
            Parms.Other = Other;
            ProcessEvent(FindFunctionChecked(NAME_LostChild), &Parms);
        }
    }
    void eventGainedChild(AActor *Other)
    {
        if (IsProbing(NAME_GainedChild)) {
            struct { AActor *Other; } Parms;
            Parms.Other = Other;
            ProcessEvent(FindFunctionChecked(NAME_GainedChild), &Parms);
        }
    }
    void SetOwner(AActor *NewOwner);
};

void AActor::SetOwner(AActor *NewOwner)
{
    if (Owner != 0)
        Owner->eventLostChild(this);
    Owner = NewOwner;
    if (Owner != 0)
        Owner->eventGainedChild(this);
    Flags2ec |= 4; // bNetDirty
}

// Scaffolding for the link, not part of the unit.
void Driver_91300(AActor *A, AActor *B) { A->SetOwner(B); }
