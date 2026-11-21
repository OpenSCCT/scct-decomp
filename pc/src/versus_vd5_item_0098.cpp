// Work item 0098: AEmitter virtuals at RVA 0xae550-0xae8a4 (vtable AEmitter@308e80,
// slots 78, 79, 42 and 80). The unit was built with VC7.0 /GL and linked /LTCG:
// slots 78 and 79 call FRangeVector::GetRand, the collision-hash overlap query and
// FMemStack::FreeChunks with link-time register conventions, so they are checked
// with try_ltcg.py. Names marked "neutral" are not confirmed by symbols.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

extern "C" __declspec(dllimport) int __cdecl rand(void);
inline FLOAT appFrand() { return rand() * (1.0f / 32767.0f); }

struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT S) const { return FVector(X * S, Y * S, Z * S); }
};
struct FBox { FVector Min, Max; };

// Random range; this build stores the upper bound first.
struct FRange {
    FLOAT Max, Min;
    FLOAT GetRand() const { return Min + (Max - Min) * appFrand(); }
};
struct FRangeVector {
    FRange X, Y, Z;
    FVector GetRand() const;
};
// 0xaf050 (work item 0100); defined here so the LTCG link gives its callers the
// retail register convention (this in ESI, return slot in EDI).
FVector FRangeVector::GetRand() const
{
    return FVector(X.GetRand(), Y.GetRand(), Z.GetRand());
}

// Memory stack (UnMem.h).
struct FTaggedMemory { FTaggedMemory *Next; INT DataSize; BYTE Data[1]; };
extern FTaggedMemory *FMemStack_UnusedChunks;   // static member FMemStack::UnusedChunks
class FMemStack {
public:
    BYTE *Top;
    BYTE *End;
    INT ChunkSize;
    FTaggedMemory *TopChunk;
    __declspec(noinline) void FreeChunks(FTaggedMemory *NewTopChunk);
};
// 0x57830; defined here for its LTCG convention (this in EAX, argument in EDX).
void FMemStack::FreeChunks(FTaggedMemory *NewTopChunk)
{
    while (TopChunk != NewTopChunk) {
        FTaggedMemory *RemoveChunk = TopChunk;
        TopChunk = TopChunk->Next;
        RemoveChunk->Next = FMemStack_UnusedChunks;
        FMemStack_UnusedChunks = RemoveChunk;
    }
    if (TopChunk) {
        Top = TopChunk->Data;
        End = Top + TopChunk->DataSize;
    } else {
        Top = 0;
        End = 0;
    }
}
extern FMemStack GMem;
class FMemMark {
public:
    FMemMark(FMemStack &InMem) { Mem = &InMem; Top = Mem->Top; SavedChunk = Mem->TopChunk; }
    void Pop()
    {
        if (SavedChunk != Mem->TopChunk)
            Mem->FreeChunks(SavedChunk);
        Mem->Top = Top;
    }
private:
    FMemStack *Mem;
    BYTE *Top;
    FTaggedMemory *SavedChunk;
};

class UClass;
class UObject {
public:
    virtual void VSlot00();
    virtual void VSlot01();
    virtual void VSlot02();
    virtual void Destroy(INT Flags);   // slot 3 (+0x0c), deleting-destructor style
    char PadObj[0x24 - 4];
    UClass *Class;                     // 0x24
    UBOOL IsA(UClass *SomeBase) const;
};
class UStruct : public UObject {
public:
    UStruct *SuperField;               // 0x28 (UField::SuperField)
};
class UClass : public UStruct {};
inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

enum EName { NAME_None = 0 };
struct FName { INT Index; FName(EName N) : Index(N) {} };
class FOutputDevice;
extern FOutputDevice *GError;
extern UObject *GOuter_10c925b4;      // neutral: outer passed when the helper is created
extern UClass HelperClass_10cc1bf8;   // neutral: class of the emitter helper object
// 0x1d380: this build's object constructor (eight arguments, cdecl).
UObject *ConstructHelper_1d380(UClass *Class, UObject *Outer, FName Name, DWORD SetFlags, UObject *Template, FOutputDevice *Error, UObject *Root, INT Extra);
template<class T> inline T *ConstructObject(UClass *Class, UObject *Outer = GOuter_10c925b4, FName Name = NAME_None, DWORD SetFlags = 0, UObject *Template = 0, FOutputDevice *Error = GError, UObject *Root = 0, INT Extra = 0)
{
    return (T *)ConstructHelper_1d380(Class, Outer, Name, SetFlags, Template, Error, Root, Extra);
}
extern void (*GHelperInit_10cc1cfc)(UObject *);   // neutral: imported init hook
extern FVector *GVecA_10ccacc4;                     // neutral: imported vectors
extern FVector *GVecB_10ccacc0;

class AActor;
struct FCheckResult {
    FCheckResult *Next;
    AActor *Actor;
};
FBox MakeBox_81ad0(const FVector &A, const FVector &B);
extern INT HashConst_10c73c9c;
class FCollisionHashRoot;
void HashQuery_19360(FCollisionHashRoot *Root, void *Query, INT *Const);
// Collision hash whose overlap query is retail 0x11a0a0 (neutral name). Its body is
// an approximation, present only so the LTCG link gives the call the retail
// convention (this in EBX, Mem in EAX, vectors in ECX/EDX, three stack arguments).
class FCollisionHash_11a0a0 {
public:
    FCollisionHashRoot *Root;   // 0x00
    INT Tag;                    // 0x04
    FCheckResult *Result;       // 0x08
    FMemStack *Mem;             // 0x0c
    INT Pad10[3];
    FVector Location;           // 0x1c
    INT Pad28[9];
    FVector Extent;             // 0x4c
    DWORD TraceFlags;           // 0x58
    DWORD ExtraNodeFlags;       // 0x5c
    INT Pad60[2];
    FBox Box;                   // 0x68
    FCheckResult *ActorOverlapCheck(FMemStack &InMem, const FVector &InLocation, const FVector &InExtent, DWORD InTraceFlags, DWORD InExtraNodeFlags, UBOOL bFlag);
};
FCheckResult *FCollisionHash_11a0a0::ActorOverlapCheck(FMemStack &InMem, const FVector &InLocation, const FVector &InExtent, DWORD InTraceFlags, DWORD InExtraNodeFlags, UBOOL bFlag)
{
    Tag++;
    Mem = &InMem;
    Result = 0;
    Location = InLocation;
    Extent = InExtent;
    ExtraNodeFlags = InExtraNodeFlags;
    TraceFlags = InTraceFlags;
    if (bFlag)
        TraceFlags |= 0x200;
    Box = MakeBox_81ad0(Location - Extent, Location - Extent);
    HashQuery_19360(Root, this, &HashConst_10c73c9c);
    return Result;
}

struct ULevel_Like { char Pad[0x3a48]; FCollisionHash_11a0a0 *Hash; };
struct ALevelInfo_Like { char Pad[0x1a4]; ULevel_Like *XLevel; };

class AActor : public UObject {
public:
    // Slots 4..81 (unrecovered here).
    virtual void VSlot04(); virtual void VSlot05(); virtual void VSlot06(); virtual void VSlot07();
    virtual void VSlot08(); virtual void VSlot09(); virtual void VSlot10(); virtual void VSlot11();
    virtual void VSlot12(); virtual void VSlot13(); virtual void VSlot14(); virtual void VSlot15();
    virtual void VSlot16(); virtual void VSlot17(); virtual void VSlot18(); virtual void VSlot19();
    virtual void VSlot20(); virtual void VSlot21(); virtual void VSlot22(); virtual void VSlot23();
    virtual void VSlot24(); virtual void VSlot25(); virtual void VSlot26(); virtual void VSlot27();
    virtual void VSlot28(); virtual void VSlot29(); virtual void VSlot30(); virtual void VSlot31();
    virtual void VSlot32(); virtual void VSlot33(); virtual void VSlot34(); virtual void VSlot35();
    virtual void VSlot36(); virtual void VSlot37(); virtual void VSlot38(); virtual void VSlot39();
    virtual void VSlot40(); virtual void VSlot41(); virtual void VSlot42(); virtual void VSlot43();
    virtual void VSlot44(); virtual void VSlot45(); virtual void VSlot46(); virtual void VSlot47();
    virtual void VSlot48(); virtual void VSlot49(); virtual void VSlot50(); virtual void VSlot51();
    virtual void VSlot52(); virtual void VSlot53(); virtual void VSlot54(); virtual void VSlot55();
    virtual void VSlot56(); virtual void VSlot57(); virtual void VSlot58(); virtual void VSlot59();
    virtual void VSlot60(); virtual void VSlot61(); virtual void VSlot62(); virtual void VSlot63();
    virtual void VSlot64(); virtual void VSlot65(); virtual void VSlot66(); virtual void VSlot67();
    virtual void VSlot68(); virtual void VSlot69(); virtual void VSlot70(); virtual void VSlot71();
    virtual void VSlot72(); virtual void VSlot73(); virtual void VSlot74(); virtual void VSlot75();
    virtual void VSlot76(); virtual void VSlot77(); virtual void VSlot78(); virtual void VSlot79();
    virtual void VSlot80(); virtual void VSlot81();
    virtual void AttachEmitterHelper(UObject *Helper, INT Index);   // slot 82 (+0x148), neutral
    char PadAct[0x80 - 0x28];
    FVector Location;            // 0x80
    char Pad8c[0x1a0 - 0x8c];
    ALevelInfo_Like *Level;      // 0x1a0
    char Pad1a4[0x1e0 - 0x1a4];
    DWORD Pad1e0Bits : 8;
    DWORD bFlagA : 1;            // 0x1e1 bit 0 (neutral)
    DWORD bFlagB : 1;            // 0x1e1 bit 1 (neutral)
    DWORD bFlagC : 1;            // 0x1e1 bit 2 (neutral)
    char Pad1e4[0x2bc - 0x1e4];
    AActor *Owner2bc;            // 0x2bc
};

// Actor class the emitter looks for (neutral name; class object at 0x10cc03e8).
class ATargetActor : public AActor {
public:
    char Pad2c0[0x470 - 0x2c0];
    AActor *Field470;            // 0x470
    INT Pad474;
    DWORD Flags478;              // 0x478
};
extern UClass TargetClass_10cc03e8;

// Actor type held in the emitter's element array (neutral name).
class AEmitterElement : public AActor {
public:
    char Pad2c0[0x2d8 - 0x2c0];
    INT Field2d8;                // 0x2d8
    INT Field2dc;                // 0x2dc
    char Pad2e0[0x3dc - 0x2e0];
    INT Field3dc;                // 0x3dc
};

struct FHelperObject : public UObject { char Pad[0x78 - 0x28]; INT Count; };

class AEmitter : public AActor {
public:
    char Pad2c0[0x2f8 - 0x2c0];
    AEmitterElement **Elements;  // 0x2f8 (TArray data)
    INT ElementNum;              // 0x2fc
    INT ElementMax;              // 0x300
    DWORD bActive : 1;           // 0x304 bit 0
    DWORD bPending : 1;          // 0x304 bit 1
    FRangeVector Range308;       // 0x308
    FRange Range320;             // 0x320
    INT bInitialized;            // 0x328
    FBox Box32c;                 // 0x32c
    FVector Vec344;              // 0x344
    INT Pad350[2];
    FLOAT Float358;              // 0x358
    FHelperObject *Helper;       // 0x35c
    DWORD Flags360;              // 0x360

    virtual void Slot42();       // retail vtable slot 42 (neutral name)
    virtual void Slot78();       // retail vtable slot 78 (neutral name)
    virtual INT Slot79();        // retail vtable slot 79 (neutral name)
    virtual void Slot80();       // retail vtable slot 80 (neutral name)
};

// 0xae550, vtable slot 78: create the helper once, then refresh the bounds.
void AEmitter::Slot78()
{
    if (!bInitialized) {
        UObject *O = ConstructObject<UObject>(&HelperClass_10cc1bf8);
        if (O)
            GHelperInit_10cc1cfc(O);
        Helper = (FHelperObject *)O;
        Vec344 = Range308.GetRand();
        Float358 = Range320.GetRand();
        bInitialized = 1;
    }
    FBox &B = Box32c;
    B.Min = *GVecA_10ccacc4;
    B.Max = *GVecB_10ccacc0;
}

// 0xae640, vtable slot 79: hand the helper to up to four overlapping target actors.
INT AEmitter::Slot79()
{
    INT Count = 0;
    FCollisionHash_11a0a0 *Hash = Level->XLevel->Hash;
    if (Hash) {
        FMemMark Mark(GMem);
        for (FCheckResult *Hit = Hash->ActorOverlapCheck(GMem, Location, (Box32c.Max - Box32c.Min) * 0.5f, 0x4000, 0, 0); Hit; Hit = Hit->Next) {
            ATargetActor *A = (ATargetActor *)Hit->Actor;
            if (A && A->IsA(&TargetClass_10cc03e8) && (A->Flags478 & 8) && (!A->Field470 || Owner2bc == A->Field470)) {
                A->AttachEmitterHelper(Helper, Count);
                Count++;
            }
        }
        Mark.Pop();
    }
    Helper->Count = Count < 0 ? 0 : Count < 4 ? Count : 4;
    return Helper->Count;
}

// 0xae7a0, vtable slot 42: destroy the elements and the helper.
void AEmitter::Slot42()
{
    if (Flags360 & 4) {
        for (INT i = 0; i < ElementNum; i++) {
            if (Elements[i])
                Elements[i]->Destroy(1);
            Elements[i] = 0;
        }
        if (Helper)
            Helper->Destroy(1);
        Helper = 0;
    }
}

// 0xae810, vtable slot 80: reset every element.
void AEmitter::Slot80()
{
    for (INT i = 0; i < ElementNum; i++) {
        if (Elements[i]) {
            Elements[i]->bFlagA = 0;
            Elements[i]->Field2dc = 0;
            Elements[i]->Field2d8 = 0;
            Elements[i]->bFlagC = 0;
            Elements[i]->bFlagB = 0;
            Elements[i]->Field3dc = 1;
        }
    }
    bPending = 0;
    bActive = 1;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_ae550(AEmitter *E, FRangeVector *R) { Escape(&GVecA_10ccacc4); Escape(&GVecB_10ccacc0); E->Slot78(); FVector V = R->GetRand(); Escape(&V); }
void Driver_ae640(AEmitter *E) { Escape(&GMem); Escape(&FMemStack_UnusedChunks); Escape((void *)E->Slot79()); }
