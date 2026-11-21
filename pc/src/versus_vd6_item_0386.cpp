// Work item 0386: ULevel collision queries at Versus RVA 0x11cf80-0x11d3f8.
// Functions:
//   0x11cf80: ULevel::SinglePointCheck
//   0x11d090: ULevel::EncroachingWorldGeometry
//   0x11d120: ULevel::MultiPointCheck
//   0x11d200: ULevel::SingleLineCheck
// Built with VC7.0 /GL and linked /LTCG.

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef double DOUBLE;
typedef unsigned short TCHAR;

struct FVector
{
    FLOAT X, Y, Z;

    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    FVector SafeNormal() const;
};

struct FBox
{
    FVector Min;
    FVector Max;
    BYTE IsValid;
};

struct FName
{
    INT Index;
    FName() {}
    FName(INT InIndex) : Index(InIndex) {}
};

// Memory allocator / stack (UnMem.h).
class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
extern const TCHAR MemChunk_Tag[];

inline void *appMalloc(INT Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

struct FTaggedMemory
{
    FTaggedMemory *Next;
    INT DataSize;
    BYTE Data[1];
};
extern FTaggedMemory *FMemStack_UnusedChunks;

class FMemStack
{
public:
    BYTE *Top;
    BYTE *End;
    INT DefaultChunkSize;
    FTaggedMemory *TopChunk;

    BYTE *AllocateNewChunk(INT MinSize);
    void FreeChunks(FTaggedMemory *NewTopChunk);

    BYTE *PushBytes(INT AllocSize, INT Align)
    {
        BYTE *Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
        Top = Result + AllocSize;
        if (Top > End)
        {
            AllocateNewChunk(AllocSize + Align);
            Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
            Top = Result + AllocSize;
        }
        return Result;
    }
};

extern FMemStack GMem;

inline void *operator new(unsigned int Size, FMemStack &Mem)
{
    return Mem.PushBytes(Size, 8);
}

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

class AActor;
class ALevelInfo;
class UPrimitive;
class UMaterial;
class UFunction;
class ULevel;

struct FCheckResult
{
    FCheckResult *Next;         // 0x00
    AActor *Actor;              // 0x04
    FVector Location;           // 0x08
    FVector Normal;             // 0x14
    UPrimitive *Primitive;      // 0x20
    FLOAT Time;                 // 0x24
    INT Item;                   // 0x28
    UMaterial *Material;        // 0x2c
    INT Field30;                // 0x30
    UBOOL bNonBlocking;         // 0x34 (neutral: triggers Event_11db70 instead of stopping trace)

    FCheckResult() {}
    FCheckResult(FLOAT InTime, FCheckResult *InNext = 0);
    FCheckResult(const FCheckResult &Other);
    FCheckResult *GetNext() const { return Next; }
};

class UObject
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *UnusedResult = 0); // +0x10
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Slot08();
    virtual void Slot09();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);
};

class UPrimitive : public UObject
{
public:
    virtual UBOOL PointCheck(FCheckResult &Result, AActor *Owner, const FVector &Location,
                             const FVector &Extent, DWORD ExtraNodeFlags); // slot 22 (+0x58)
};

struct FBspNode
{
    BYTE unk_00[0x2c];
    INT iSurf;                  // 0x2c
    BYTE unk_30[0x5c - 0x30];
};

struct FBspSurf
{
    BYTE unk_00[0x14];
    DWORD PolyFlags;            // 0x14
    BYTE unk_18[0x2c - 0x18];
};

template <class T> struct TArray
{
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    T &operator()(INT i) { return Data[i]; }
};

class UModel : public UPrimitive
{
public:
    BYTE unk_04[0x54 - 0x04];
    TArray<FBspNode> Nodes;     // 0x54
    BYTE unk_60[0x94 - 0x60];
    TArray<FBspSurf> Surfs;     // 0x94
};

class AActor : public UObject
{
public:
    BYTE unk_04[0x1a4 - 0x04];
    ULevel *XLevel;             // 0x1a4

    void Event_11db70(AActor *SourceActor, FVector HitLocation, FVector HitNormal, FVector Dir);
};

class ALevelInfo : public AActor
{
};

extern DWORD HashConst_10c73c9c;
FBox MakeBox_81ad0(const FVector &A, const FVector &B);
void HashQuery_19360(void *Root, void *Hash, void *ConstPtr);

class FCollisionHash
{
public:
    void *Root;                 // 0x00
    INT Tag;                    // 0x04
    FCheckResult *Result;       // 0x08
    FMemStack *Mem;             // 0x0c
    BYTE unk_10[0x18];
    FVector Location;           // 0x28
    FVector Extent;             // 0x34
    FBox Box;                   // 0x40
    DWORD TraceFlags;           // 0x58
    DWORD ExtraNodeFlags;       // 0x5c

    FCheckResult *ActorOverlapCheck(FMemStack &InMem, const FVector &InLocation,
                                    const FVector &InExtent, DWORD InTraceFlags,
                                    DWORD InExtraNodeFlags, UBOOL bSingleResult);
};

class ULevel
{
public:
    BYTE unk_00[0x2c];
    TArray<AActor *> Actors;    // 0x2c
    BYTE unk_38[0x13c - 0x38];
    UModel *Model;              // 0x13c
    BYTE unk_140[0x3a48 - 0x140];
    FCollisionHash *Hash;       // 0x3a48

    ALevelInfo *GetLevelInfo() { return (ALevelInfo *)Actors(0); }

    UBOOL SinglePointCheck(FCheckResult &Hit, const FVector &Location, const FVector &Extent,
                           DWORD ExtraNodeFlags, ALevelInfo *Level, UBOOL bActors);
    UBOOL EncroachingWorldGeometry(FCheckResult &Hit, const FVector &Location,
                                   const FVector &Extent, DWORD ExtraNodeFlags, ALevelInfo *Level);
    FCheckResult *MultiPointCheck(FMemStack &Mem, const FVector &Location, const FVector &Extent,
                                  DWORD ExtraNodeFlags, ALevelInfo *Level, UBOOL bActors,
                                  UBOOL bOnlyWorld, UBOOL bSingleResult);
    UBOOL SingleLineCheck(FCheckResult &Hit, AActor *SourceActor, const FVector &End,
                          const FVector &Start, DWORD TraceFlags, const FVector &Extent);
    FCheckResult *MultiLineCheck(FMemStack &Mem, FVector End, const FVector &Start,
                                 const FVector &Extent, DWORD TraceFlags, AActor *SourceActor,
                                 ALevelInfo *LevelInfo);
};

// --- Target functions ---

// RVA 0x11cf80: ULevel::SinglePointCheck
UBOOL ULevel::SinglePointCheck(FCheckResult &Hit, const FVector &Location, const FVector &Extent,
                               DWORD ExtraNodeFlags, ALevelInfo *Level, UBOOL bActors)
{
    FMemMark Mark(GMem);
    FCheckResult *Hits = MultiPointCheck(GMem, Location, Extent, ExtraNodeFlags, Level, bActors, 0, 0);
    if (!Hits)
    {
        Mark.Pop();
        return 1;
    }
    Hit = *Hits;
    for (Hits = Hits->GetNext(); Hits != 0; Hits = Hits->GetNext())
    {
        if ((Hits->Location - Location).SizeSquared() < (Hit.Location - Location).SizeSquared())
            Hit = *Hits;
    }
    Mark.Pop();
    return 0;
}

// RVA 0x11d090: ULevel::EncroachingWorldGeometry
UBOOL ULevel::EncroachingWorldGeometry(FCheckResult &Hit, const FVector &Location,
                                       const FVector &Extent, DWORD ExtraNodeFlags,
                                       ALevelInfo *Level)
{
    FMemMark Mark(GMem);
    FCheckResult *Hits = MultiPointCheck(GMem, Location, Extent, ExtraNodeFlags, Level, 1, 1, 1);
    if (!Hits)
    {
        Mark.Pop();
        return 0;
    }
    Hit = *Hits;
    Mark.Pop();
    return 1;
}

// RVA 0x11d120: ULevel::MultiPointCheck
FCheckResult *ULevel::MultiPointCheck(FMemStack &Mem, const FVector &Location,
                                      const FVector &Extent, DWORD ExtraNodeFlags,
                                      ALevelInfo *Level, UBOOL bActors, UBOOL bOnlyWorld,
                                      UBOOL bSingleResult)
{
    FCheckResult *Result = 0;
    if (Level != 0)
    {
        FCheckResult Hit(1.0f);
        if (Level->XLevel->Model->PointCheck(Hit, 0, Location, Extent, 0) == 0)
        {
            Hit.Next = Result;
            Result = new(Mem) FCheckResult(Hit);
            Result->Actor = Level;
            if (bSingleResult)
                return Result;
        }
    }
    if (bActors && Hash)
    {
        Result = Hash->ActorOverlapCheck(Mem, Location, Extent, bOnlyWorld ? 0x86 : 0x9f,
                                         ExtraNodeFlags, bSingleResult);
    }
    return Result;
}

// RVA 0x11d200: ULevel::SingleLineCheck
UBOOL ULevel::SingleLineCheck(FCheckResult &Hit, AActor *SourceActor, const FVector &End,
                              const FVector &Start, DWORD TraceFlags, const FVector &Extent)
{
    FMemMark Mark(GMem);
    if (!(TraceFlags & 0x20000))
        TraceFlags |= 0x400;
    FCheckResult *FirstHit = MultiLineCheck(GMem, End, Start, Extent, TraceFlags, SourceActor,
                                            (TraceFlags & 0x4) ? GetLevelInfo() : 0);
    FVector Dir = (End - Start).SafeNormal();
    DWORD IgnorePolyFlags = ((TraceFlags & 0x100) | 0x8000) >> 8;
    FCheckResult *Test;
    for (Test = FirstHit; Test; Test = Test->Next)
    {
        if (((TraceFlags & 0x100) || (TraceFlags & 0x80000)) && Test->Actor == GetLevelInfo())
        {
            DWORD PolyFlags = Model->Surfs(Model->Nodes(Test->Item).iSurf).PolyFlags;
            if (PolyFlags & IgnorePolyFlags)
                continue;
        }
        if (!Test->bNonBlocking)
            break;
        Test->Actor->Event_11db70(SourceActor, Test->Location, Test->Normal, Dir);
    }
    if (Test)
    {
        Hit = *Test;
    }
    else
    {
        Hit.Time = 1.0f;
        Hit.Actor = 0;
    }
    Mark.Pop();
    return Test == 0;
}

// --- Scaffolding for the LTCG link, not part of the unit ---

void Escape(void *);
extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
extern FVector *GZeroVector_10ccacc0;

__declspec(noinline) BYTE *FMemStack::AllocateNewChunk(INT MinSize)
{
    FTaggedMemory *Chunk = 0;
    for (FTaggedMemory **Link = &FMemStack_UnusedChunks; *Link; Link = &(*Link)->Next)
    {
        if ((*Link)->DataSize >= MinSize)
        {
            Chunk = *Link;
            *Link = (*Link)->Next;
            break;
        }
    }
    if (!Chunk)
    {
        INT DataSize = Max(MinSize, DefaultChunkSize - (INT)sizeof(FTaggedMemory));
        Chunk = (FTaggedMemory *)appMalloc(DataSize + sizeof(FTaggedMemory), MemChunk_Tag);
        Chunk->DataSize = DataSize;
    }
    Chunk->Next = TopChunk;
    TopChunk = Chunk;
    Top = Chunk->Data;
    End = Top + Chunk->DataSize;
    return Top;
}

void FMemStack::FreeChunks(FTaggedMemory *NewTopChunk)
{
    while (TopChunk != NewTopChunk)
    {
        FTaggedMemory *RemoveChunk = TopChunk;
        TopChunk = TopChunk->Next;
        RemoveChunk->Next = FMemStack_UnusedChunks;
        FMemStack_UnusedChunks = RemoveChunk;
    }
    if (TopChunk)
    {
        Top = TopChunk->Data;
        End = Top + TopChunk->DataSize;
    }
    else
    {
        Top = 0;
        End = 0;
    }
}

__declspec(noinline) FCheckResult::FCheckResult(const FCheckResult &Other)
{
    Next = Other.Next;
    Actor = Other.Actor;
    Location = Other.Location;
    Normal = Other.Normal;
    Primitive = Other.Primitive;
    Time = Other.Time;
    Item = Other.Item;
    Material = Other.Material;
    Field30 = Other.Field30;
    bNonBlocking = Other.bNonBlocking;
}

__declspec(noinline) FCheckResult *FCollisionHash::ActorOverlapCheck(
    FMemStack &InMem, const FVector &InLocation, const FVector &InExtent,
    DWORD InTraceFlags, DWORD InExtraNodeFlags, UBOOL bSingleResult)
{
    Tag++;
    Mem = &InMem;
    Result = 0;
    Location = InLocation;
    Extent = InExtent;
    ExtraNodeFlags = InExtraNodeFlags;
    TraceFlags = InTraceFlags;
    if (bSingleResult)
        TraceFlags |= 0x200;
    Box = MakeBox_81ad0(Location - Extent, Location - Extent);
    HashQuery_19360(Root, this, &HashConst_10c73c9c);
    return Result;
}

__declspec(noinline) FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return *GZeroVector_10ccacc0;
    FLOAT Scale = 1.0f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

__declspec(noinline) void AActor::Event_11db70(AActor *SourceActor, FVector HitLocation,
                                               FVector HitNormal, FVector Dir)
{
    struct FEvent_11db70_Parms
    {
        AActor *SourceActor;
        FVector HitLocation;
        FVector HitNormal;
        FVector Dir;
    } Parms;
    Parms.SourceActor = SourceActor;
    Parms.HitLocation = HitLocation;
    Parms.HitNormal = HitNormal;
    Parms.Dir = Dir;
    ProcessEvent(FindFunctionChecked(FName(0x9e7)), &Parms);
}

__declspec(noinline) FCheckResult *ULevel::MultiLineCheck(
    FMemStack &Mem, FVector End, const FVector &Start, const FVector &Extent,
    DWORD TraceFlags, AActor *SourceActor, ALevelInfo *LevelInfo)
{
    FCheckResult *Res = 0;
    if (LevelInfo)
    {
        Mem.Top += 8;
        Res = (FCheckResult *)Mem.Top;
        Res->Actor = LevelInfo;
        Res->Location = Start;
    }
    if (TraceFlags & 4)
    {
        Escape(this);
        Escape(&End);
        Escape((void *)&Extent);
        Escape(SourceActor);
    }
    return Res;
}

#pragma inline_depth(0)
void Driver_11cf80(ULevel *L, FCheckResult *Hit, const FVector *Loc, const FVector *Ext,
                   DWORD Flags, ALevelInfo *Info, UBOOL bActors, FMemStack *M, FTaggedMemory *Chunk)
{
    Escape(&GMem);
    Escape(&GMalloc);
    Escape(&FMemStack_UnusedChunks);
    M->FreeChunks(Chunk);
    Escape((void *)L->SinglePointCheck(*Hit, *Loc, *Ext, Flags, Info, bActors));
    Escape((void *)L->EncroachingWorldGeometry(*Hit, *Loc, *Ext, Flags, Info));
}

void Driver_11d200(ULevel *L, FCheckResult *Hit, AActor *Src, const FVector *End,
                   const FVector *Start, DWORD Flags, const FVector *Ext,
                   FMemStack *M, ALevelInfo *Info)
{
    Escape(&GMem);
    Escape(&GMalloc);
    Escape(&FMemStack_UnusedChunks);
    Escape(&GZeroVector_10ccacc0);
    typedef UBOOL (ULevel::*SingleLineCheckFn)(FCheckResult &, AActor *, const FVector &,
                                               const FVector &, DWORD, const FVector &);
    SingleLineCheckFn Fn = &ULevel::SingleLineCheck;
    Escape(&Fn);
    Escape((void *)L->SingleLineCheck(*Hit, Src, *End, *Start, Flags, *Ext));
    Escape(L->MultiLineCheck(*M, *End, *Start, *Ext, Flags, Src, Info));
    FVector V = Start->SafeNormal();
    Escape(&V);
    Src->Event_11db70(Src, *End, *Start, *Ext);
}
#pragma inline_depth()
