// Work item 0388: Versus RVA 0x11da40-0x11db21, 3 functions.
//
// Script event wrappers called from AActor::SetZone (RVA 0x11d700):
//   0x11da40  AZoneInfo::eventActorEntered(AActor *Other)   (NAME_ActorEntered = 0x141, probe bit 21)
//   0x11da90  AActor::eventZoneChange(AZoneInfo *NewZone)   (NAME_ZoneChange   = 0x143, probe bit 23)
//   0x11dae0  AZoneInfo::eventActorLeaving(AActor *Other)   (NAME_ActorLeaving = 0x142, probe bit 22)

// Unreal Engine 2 builds with 4-byte structure packing (/Zp4).
#pragma pack(push, 4)

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned __int64 QWORD;

enum EName {
    NAME_None         = 0,
    NAME_PROBEMIN     = 300,
    NAME_ActorEntered = 321,    // 0x141
    NAME_ActorLeaving = 322,    // 0x142
    NAME_ZoneChange   = 323,    // 0x143
    NAME_PROBEMAX     = 364
};

class FName {
public:
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
    INT GetIndex() const { return Index; }
};

struct FStateFrame {
    BYTE  unk_0[0x1c];
    QWORD ProbeMask;
};

class UFunction;
struct FGuid;

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);

    INT          Index;
    UObject     *HashNext;
    FStateFrame *StateFrame;

    UBOOL IsProbing(FName ProbeName)
    {
        return ProbeName.GetIndex() < NAME_PROBEMIN
            || ProbeName.GetIndex() >= NAME_PROBEMAX
            || !StateFrame
            || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
    }

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);
};

class AZoneInfo;

struct AActor_eventZoneChange_Parms {
    AZoneInfo *NewZone;
};

class AActor : public UObject {
public:
    void eventZoneChange(AZoneInfo *NewZone);
};

struct AZoneInfo_eventActorEntered_Parms {
    AActor *Other;
};

struct AZoneInfo_eventActorLeaving_Parms {
    AActor *Other;
};

class AZoneInfo : public AActor {
public:
    void eventActorEntered(AActor *Other);
    void eventActorLeaving(AActor *Other);
};

#pragma pack(pop)

// RVA 0x11da40: AZoneInfo::eventActorEntered
void AZoneInfo::eventActorEntered(AActor *Other)
{
    AZoneInfo_eventActorEntered_Parms Parms;
    if (IsProbing(NAME_ActorEntered)) {
        Parms.Other = Other;
        ProcessEvent(FindFunctionChecked(NAME_ActorEntered), &Parms);
    }
}

// RVA 0x11da90: AActor::eventZoneChange
void AActor::eventZoneChange(AZoneInfo *NewZone)
{
    AActor_eventZoneChange_Parms Parms;
    if (IsProbing(NAME_ZoneChange)) {
        Parms.NewZone = NewZone;
        ProcessEvent(FindFunctionChecked(NAME_ZoneChange), &Parms);
    }
}

// RVA 0x11dae0: AZoneInfo::eventActorLeaving
void AZoneInfo::eventActorLeaving(AActor *Other)
{
    AZoneInfo_eventActorLeaving_Parms Parms;
    if (IsProbing(NAME_ActorLeaving)) {
        Parms.Other = Other;
        ProcessEvent(FindFunctionChecked(NAME_ActorLeaving), &Parms);
    }
}

// Scaffolding for the LTCG link, not part of the unit.
void ExternalBarrier(void *);

void Driver_11da40(AZoneInfo *Zone, AZoneInfo *Zone2, AActor *A, AActor *B, INT Mode)
{
    switch (Mode) {
    case 0: Zone->eventActorEntered(A); ExternalBarrier(Zone); break;
    case 1: Zone->eventActorEntered(B); ExternalBarrier(A); break;
    case 2: Zone2->eventActorEntered(A); ExternalBarrier(Zone2); break;
    case 3: Zone2->eventActorEntered(B); ExternalBarrier(B); break;
    case 4: Zone->eventActorEntered(Zone2); ExternalBarrier(Zone); Zone2->eventActorEntered(A); break;
    case 5: Zone2->eventActorEntered(Zone); ExternalBarrier(Zone2); Zone->eventActorEntered(B); break;
    case 6: Zone->eventActorEntered(A); Zone->eventActorEntered(B); Zone2->eventActorEntered(A); break;
    case 7: Zone2->eventActorEntered(B); Zone->eventActorEntered(Zone); Zone2->eventActorEntered(Zone2); break;
    }
}

void Driver_11da90(AActor *Actor, AActor *Actor2, AZoneInfo *Z1, AZoneInfo *Z2, INT Mode)
{
    switch (Mode) {
    case 0: Actor->eventZoneChange(Z1); ExternalBarrier(Actor); break;
    case 1: Actor->eventZoneChange(Z2); ExternalBarrier(Z1); break;
    case 2: Actor2->eventZoneChange(Z1); ExternalBarrier(Actor2); break;
    case 3: Actor2->eventZoneChange(Z2); ExternalBarrier(Z2); break;
    case 4: Actor->eventZoneChange(Z2); ExternalBarrier(Actor); Actor2->eventZoneChange(Z1); break;
    case 5: Actor2->eventZoneChange(Z2); ExternalBarrier(Actor2); Actor->eventZoneChange(Z1); break;
    case 6: Actor->eventZoneChange(Z1); Actor->eventZoneChange(Z2); Actor2->eventZoneChange(Z1); break;
    case 7: Actor2->eventZoneChange(Z2); Z1->eventZoneChange(Z2); Z2->eventZoneChange(Z1); break;
    }
}

void Driver_11dae0(AZoneInfo *Zone, AZoneInfo *Zone2, AActor *A, AActor *B, INT Mode)
{
    switch (Mode) {
    case 0: Zone->eventActorLeaving(A); ExternalBarrier(Zone); break;
    case 1: Zone->eventActorLeaving(B); ExternalBarrier(A); break;
    case 2: Zone2->eventActorLeaving(A); ExternalBarrier(Zone2); break;
    case 3: Zone2->eventActorLeaving(B); ExternalBarrier(B); break;
    case 4: Zone->eventActorLeaving(Zone2); ExternalBarrier(Zone); Zone2->eventActorLeaving(A); break;
    case 5: Zone2->eventActorLeaving(Zone); ExternalBarrier(Zone2); Zone->eventActorLeaving(B); break;
    case 6: Zone->eventActorLeaving(A); Zone->eventActorLeaving(B); Zone2->eventActorLeaving(A); break;
    case 7: Zone2->eventActorLeaving(B); Zone->eventActorLeaving(Zone); Zone2->eventActorLeaving(Zone2); break;
    }
}
