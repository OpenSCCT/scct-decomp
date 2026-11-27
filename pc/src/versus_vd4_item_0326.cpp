// Work item 0326: Versus AActor methods (LTCG object).
// Names: AActor field names follow UE2 (XLevel at 0x1a4, ObjectFlags at 0x1c,
// Class at 0x24, collision bits at 0x2f0); others are neutral offsets.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    void Remove(INT Index, INT Count, INT ElementSize);   // RVA 0x119c0
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayMax = 0;
        ArrayNum = 0;
    }
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT RemoveItem(const T &Item);
    ~TArray();
};

class UClass
{
public:
    BYTE Pad00[0x88];
    DWORD ClassFlags;               // 0x88
};

// Collision hash of a level (FCollisionHash-style; LTCG convention: hash on
// the stack).
struct FVector { FLOAT X, Y, Z; };
struct FRotator { INT Pitch, Yaw, Roll; };

class AActor;

// FMemStack / FMemMark (UE2).
struct FTaggedMemory
{
    FTaggedMemory *Next;
    INT DataSize;
    BYTE Data[1];
};
class FMemStack
{
public:
    BYTE *Top;
    BYTE *End;
    INT DefaultChunkSize;
    FTaggedMemory *TopChunk;
    static FTaggedMemory *UnusedChunks;     // retail 0x10c92574
    void FreeChunks(FTaggedMemory *NewTopChunk);    // RVA 0x57830
};
extern FMemStack GMem;                      // retail 0x10c78bb0
class FMemMark
{
public:
    FMemMark(FMemStack &InMem)
    {
        Mem = &InMem;
        Top = Mem->Top;
        SavedChunk = Mem->TopChunk;
    }
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

struct FCheckResult
{
    FCheckResult *Next;
    AActor *Actor;
    FVector Location;
    FVector Normal;
    FCheckResult *GetNext() const { return Next; }
};

enum { TRACE_AllColliding = 0x9f };

class FCollisionHash;
void __stdcall FCollisionHash_RemoveActor(FCollisionHash *Hash, AActor *Actor);  // RVA 0x119a20
class FCollisionHash
{
public:
    DWORD Field00;
    INT Field04;
    FCheckResult *Field08;
    FMemStack *Field0C;
    BYTE Pad10[0x58 - 0x10];
    DWORD Field58;
    DWORD Field5C;
    AActor *Field60;
    void AddActor(AActor *Actor);   // RVA 0x1198a0 (hash on the stack, actor in EBX)
    FCheckResult *ActorEncroachmentCheck(FMemStack &Mem, AActor *Actor, FVector Location,
                                         FRotator Rotation, DWORD TraceFlags, DWORD ExtraNodeFlags);  // RVA 0x11a230
};

class ULevel
{
public:
    BYTE Pad0000[0x3a48];
    FCollisionHash *Hash;           // 0x3a48
};

class UObjectBase
{
public:
    virtual void Slot0();
    virtual void Slot1();  virtual void Slot2();  virtual void Slot3();  virtual void Slot4();
    virtual void Slot5();  virtual void Slot6();  virtual void Slot7();  virtual void Slot8();
    virtual void Slot9();  virtual void Slot10(); virtual void Slot11(); virtual void Slot12();
    virtual void Slot13(); virtual void Slot14(); virtual void Slot15(); virtual void Slot16();
    virtual void Slot17(); virtual void Slot18(); virtual void Slot19(); virtual void Slot20();
    virtual void Slot21(); virtual void Slot22(); virtual void Slot23(); virtual void Slot24();
    virtual void Slot25();
    DWORD Field04[6];
    DWORD ObjectFlags;              // 0x1c
    DWORD Name;                     // 0x20
    UClass *Class;                  // 0x24
};

class UnnamedObject_238 : public UObjectBase
{
public:
    BYTE Pad28[0x50 - 0x28];
    UObjectBase *Field50;           // 0x50
};

class AActor : public UObjectBase
{
public:
    virtual UBOOL IsBlockedBy(const AActor *Other) const;   // slot 26
    BYTE Pad028[0x80 - 0x28];
    FVector Location;               // 0x80
    BYTE Pad08C[0xe0 - 0x8c];
    FRotator Rotation;              // 0xe0
    BYTE Pad0EC[0x108 - 0xec];
    AActor *Base;                   // 0x108 (presumed)
    BYTE Pad10C[0x134 - 0x10c];
    INT Field134;                   // 0x134
    BYTE Pad138[0x1a0 - 0x138];
    AActor *Level;                  // 0x1a0
    ULevel *XLevel;                 // 0x1a4
    BYTE Pad1A8[0x1dc - 0x1a8];
    TArray<AActor *> Touching;      // 0x1dc
    BYTE Pad1E8[0x200 - 0x1e8];
    INT JoinTag;                    // 0x200 (neutral)
    TArray<AActor *> Attached;      // 0x204 (presumed)
    BYTE Pad210[0x238 - 0x210];
    UnnamedObject_238 *Field238;    // 0x238
    FLOAT Field23C;                 // 0x23c (DrawScale, presumed)
    BYTE Pad240[0x250 - 0x240];
    DWORD Field250;                 // 0x250
    BYTE Pad254[0x268 - 0x254];
    FLOAT Field268;                 // 0x268
    FLOAT Field26C;                 // 0x26c
    BYTE Pad270[0x2ec - 0x270];
    DWORD Flags2EC;                 // 0x2ec (bit 2: bNetDirty)
    union
    {
        DWORD Flags2F0;             // 0x2f0
        struct
        {
            DWORD Bits2F0 : 12;
            DWORD bCollideActors : 1;
            DWORD Bit13 : 1;
            DWORD bBlockActors : 1;
            DWORD bBlockPlayers : 1;
        };
    };

    void Notify_16f70();            // RVA 0x16f70
    void Update_90de0();            // RVA 0x90de0
    void Slot8_90040();
    void Slot16_900f0();
    void SetCollisionSize(FLOAT NewRadius, FLOAT NewHeight);
    void SetDrawScale(FLOAT NewScale);
    void SetCollision(UBOOL NewCollideActors, UBOOL NewBlockActors, UBOOL NewBlockPlayers);
    UBOOL IsJoinedTo(const AActor *Other) const;                    // RVA 0x91680
    void BeginTouch(AActor *Other, const FVector &HitLocation, const FVector &HitNormal);  // RVA 0x909f0
    void EndTouch(AActor *Other, UBOOL NoNotifySelf);               // RVA 0x90a40
    void eventUnTouch(AActor *Other);                               // RVA 0x92a50
};

// RVA 0x90040, AActor vtable slot 8
void AActor::Slot8_90040()
{
    ObjectFlags |= 0x20000000;
    if (ObjectFlags & 0x100)
        Notify_16f70();
    if (Class->ClassFlags & 0x20)
        Notify_16f70();
    if (Field238)
        Field238->ObjectFlags |= 1;
    if (Field238 && Field238->Field50)
        Field238->Field50->ObjectFlags |= 1;
    for (INT i = 0; i < Attached.Num(); i++)
    {
        if (!Attached(i) || Attached(i)->Base != this)
            Attached.Remove(i--, 1, sizeof(AActor *));
    }
}

// RVA 0x900f0, AActor vtable slot 16
void AActor::Slot16_900f0()
{
    for (INT i = 0; i < Attached.Num(); i++)
    {
        if (!Attached(i))
            Attached.Remove(i--, 1, sizeof(AActor *));
    }
    Update_90de0();
}

// RVA 0x90130 (NOT matched). Logic follows retail; the LTCG link gives the
// helpers (EndTouch, BeginTouch, IsJoinedTo, ActorEncroachmentCheck,
// FreeChunks) conventions different from retail because their scaffolding
// bodies differ, and try_ltcg cannot bind GMem.TopChunk (GMem+0xc).
void AActor::SetCollision(UBOOL NewCollideActors, UBOOL NewBlockActors, UBOOL NewBlockPlayers)
{
    UBOOL OldCollideActors = bCollideActors;
    if (OldCollideActors && XLevel->Hash)
        FCollisionHash_RemoveActor(XLevel->Hash, this);
    if (bCollideActors && !NewCollideActors)
    {
        for (INT i = 0; i < Touching.Num(); )
        {
            if (Touching(i))
                Touching(i)->EndTouch(this, 0);
            else
                i++;
        }
    }
    bCollideActors = NewCollideActors;
    bBlockActors = NewBlockActors;
    bBlockPlayers = NewBlockPlayers;
    if (bCollideActors && XLevel->Hash)
        XLevel->Hash->AddActor(this);
    if (NewCollideActors && !OldCollideActors)
    {
        FMemMark Mark(GMem);
        FCheckResult *FirstHit = XLevel->Hash
            ? XLevel->Hash->ActorEncroachmentCheck(GMem, this, Location, Rotation, TRACE_AllColliding, 0)
            : 0;
        for (FCheckResult *Test = FirstHit; Test; Test = Test->GetNext())
        {
            if (Test->Actor != this && !Test->Actor->IsJoinedTo(this) && Test->Actor != Level
                && !IsBlockedBy(Test->Actor))
                BeginTouch(Test->Actor, Test->Location, Test->Normal);
        }
        Mark.Pop();
    }
    Flags2EC |= 4;
}

// RVA 0x90300
void AActor::SetCollisionSize(FLOAT NewRadius, FLOAT NewHeight)
{
    if ((Flags2F0 & 0x1000) && XLevel && XLevel->Hash)
        FCollisionHash_RemoveActor(XLevel->Hash, this);
    Field268 = NewRadius;
    Field26C = NewHeight;
    if ((Flags2F0 & 0x1000) && XLevel && XLevel->Hash)
        XLevel->Hash->AddActor(this);
    Flags2EC |= 4;
}

// RVA 0x90370
void AActor::SetDrawScale(FLOAT NewScale)
{
    if ((Flags2F0 & 0x1000) && XLevel->Hash)
        FCollisionHash_RemoveActor(XLevel->Hash, this);
    Field23C = NewScale;
    if ((Flags2F0 & 0x1000) && XLevel->Hash)
        XLevel->Hash->AddActor(this);
    Flags2EC |= 4;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
__declspec(noinline) void AActor::Notify_16f70()
{
    if (Class->ClassFlags & 0x20)
    {
        Escape(Class);
        Escape(this);
    }
}
__declspec(noinline) void AActor::Update_90de0()
{
    Field134++;
    if (Field250)
    {
        Escape(Class);
        Escape(this);
    }
}
__declspec(noinline) void FCollisionHash::AddActor(AActor *Actor)
{
    if (!Actor || (Actor->Flags2F0 & 0x40))
        return;
    if (Actor->Field134 > 0)
        FCollisionHash_RemoveActor(this, Actor);
    struct FBig { DWORD D[16]; };
    *(FBig *)&Actor->Pad028 = *(FBig *)Actor->Class;
    *(FBig *)&Actor->Pad1A8 = *(FBig *)Actor->XLevel;
    Escape(Actor->Class);
    Actor->Flags2EC &= 0x7fffffff;
    FCollisionHash_RemoveActor(this, Actor);
}
__declspec(noinline) FCheckResult *FCollisionHash::ActorEncroachmentCheck(FMemStack &Mem, AActor *Actor,
    FVector Location, FRotator Rotation, DWORD TraceFlags, DWORD ExtraNodeFlags)
{
    Field0C = &Mem;
    Field58 = TraceFlags;
    Field5C = ExtraNodeFlags;
    Field08 = 0;
    Field04++;
    Field60 = Actor;
    FVector SavedLocation = Actor->Location;
    FRotator SavedRotation = Actor->Rotation;
    Actor->Location = Location;
    Actor->Rotation = Rotation;
    Escape(Actor->Class);
    Escape(this);
    Actor->Location = SavedLocation;
    Actor->Rotation = SavedRotation;
    return Field08;
}
__declspec(noinline) UBOOL AActor::IsJoinedTo(const AActor *Other) const
{
    for (const AActor *Test = this; Test; Test = Test->Base)
    {
        if (Test == Other)
            return 1;
        if (Test && Other && Test->JoinTag == Other->JoinTag && Test->JoinTag)
            return 1;
    }
    return 0;
}
__declspec(noinline) void AActor::BeginTouch(AActor *Other, const FVector &HitLocation, const FVector &HitNormal)
{
    Escape(Other);
    Escape(this);
    FVector Flipped;
    Flipped.X = -HitNormal.X;
    Flipped.Y = -HitNormal.Y;
    Flipped.Z = -HitNormal.Z;
    Escape(&Flipped);
    Escape((void *)&HitLocation);
    Escape(Other);
}
__declspec(noinline) void AActor::EndTouch(AActor *Other, UBOOL NoNotifySelf)
{
    if (!NoNotifySelf)
    {
        for (INT i = 0; i < Touching.Num(); i++)
            if (Touching(i) == Other)
            {
                eventUnTouch(Other);
                break;
            }
    }
    Touching.RemoveItem(Other);
    for (INT j = 0; j < Other->Touching.Num(); j++)
        if (Other->Touching(j) == this)
        {
            Other->eventUnTouch(this);
            break;
        }
    Other->Touching.RemoveItem(this);
}
__declspec(noinline) void FMemStack::FreeChunks(FTaggedMemory *NewTopChunk)
{
    while (TopChunk != NewTopChunk)
    {
        FTaggedMemory *RemoveChunk = TopChunk;
        TopChunk = TopChunk->Next;
        RemoveChunk->Next = UnusedChunks;
        UnusedChunks = RemoveChunk;
    }
    if (TopChunk)
    {
        Top = TopChunk->Data;
        End = Top + TopChunk->DataSize;
    }
}
void Driver_90130(AActor *A, UBOOL C, UBOOL B, UBOOL P) { Escape(&GMem); A->SetCollision(C, B, P); }
// Other retail callers of the helpers, so the linker neither folds their
// constant arguments nor inlines them.
#pragma inline_depth(0)
void Driver_Helpers(AActor *A, AActor *B, FMemStack *M, DWORD F, DWORD X, FVector *V, FTaggedMemory *T)
{
    Escape(A->XLevel->Hash->ActorEncroachmentCheck(*M, A, *V, A->Rotation, F, X));
    A->EndTouch(B, F);
    A->BeginTouch(B, *V, V[1]);
    Escape((void *)A->IsJoinedTo(B));
    M->FreeChunks(T);
}
#pragma inline_depth()
void Driver_90300(AActor *A, FLOAT R, FLOAT H) { A->SetCollisionSize(R, H); }
// Keep the setter out of line in its driver.
#pragma inline_depth(0)
void Driver_90370(AActor *A, FLOAT S) { A->SetDrawScale(S); }
#pragma inline_depth()
// Retail reaches these through the vtable; a member pointer keeps thiscall.
typedef void (AActor::*AActorMethod)();
void Driver_90040(AActor *A) { AActorMethod M = &AActor::Slot8_90040; Escape(&M); (A->*M)(); }
void Driver_900f0(AActor *A) { AActorMethod M = &AActor::Slot16_900f0; Escape(&M); (A->*M)(); }
template<class T> __declspec(noinline) TArray<T>::~TArray()
{
    Remove(0, ArrayNum, sizeof(T));
}
