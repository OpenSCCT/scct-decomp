// w3_item_0395.cpp -- Versus RVA 0x121770-0x121967
// Retail kept every function here out of line; __declspec(noinline) stops the
// link-time inliner folding them into the single scaffolding callers.

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef int UBOOL;
typedef unsigned short TCHAR;

extern "C" void *__cdecl memset(void *Dest, int Value, unsigned int Count);
#pragma intrinsic(memset)

template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

template<class T> inline T Min(const T A, const T B)
{
    return A < B ? A : B;
}

struct FVector {
    FLOAT X, Y, Z;
};

struct FColor {
    BYTE B, G, R, A;

    void operator+=(FColor C);
    FLOAT Brightness() const;
};

class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;
};

template<class T> class TArray : public FArray {
};

class UClass;

class UObject {
public:
    virtual void VirtualSlot0();

    INT     Index;
    BYTE    unk_8[0x14];
    DWORD   ObjectFlags;
    BYTE    unk_20[0x4];
    UClass *Class;

    UClass *GetClass() const { return Class; }
    UBOOL IsA(UClass *SomeBase) const;
};

class UClass : public UObject {
public:
    BYTE         unk_28[0x84];
    TArray<BYTE> Defaults;
    BYTE         unk_b8[0x54];
    DWORD        ClassPrime;
    DWORD        ClassPrimeProduct;

    class AActor *GetDefaultActor() const { return (class AActor *)Defaults.Data; }
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    return (!SomeBase || Class == SomeBase) ? 1 : ((Class->ClassPrimeProduct % SomeBase->ClassPrime) == 0);
}

class AActor : public UObject {
public:
    BYTE    unk_28[0xb8];
    FVector Location;
    BYTE    unk_ec[0xbc];
    FLOAT   LifeSpan;
    BYTE    unk_1ac[0x14c];

    FVector GetLocation_121830();
    FLOAT LifeFraction();
};

class APawn : public AActor {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }

    BYTE    unk_2f8[0x94];
    AActor *unk_38c;
};

struct FTaggedMemory {
    FTaggedMemory *Next;
    INT            DataSize;
    BYTE           Data[1];
};

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};

extern FMalloc *GMalloc;

class FMemStack {
public:
    BYTE          *Top;
    BYTE          *End;
    INT            DefaultChunkSize;
    FTaggedMemory *TopChunk;
    static FTaggedMemory *UnusedChunks;

    BYTE *AllocateNewChunk(INT MinSize);

    BYTE *PushBytes(INT AllocSize, INT Align)
    {
        BYTE *Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
        Top = Result + AllocSize;
        if (Top > End) {
            AllocateNewChunk(AllocSize + Align);
            Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
            Top = Result + AllocSize;
        }
        return Result;
    }
};

// 0x121770: NewOned<BYTE> (FMemStack::PushBytes + appMemset 0xFF)
__declspec(noinline) BYTE *NewOned(FMemStack &Mem, INT Count, INT Align)
{
    BYTE *Result = Mem.PushBytes(Count, Align);
    memset(Result, 0xff, Count);
    return Result;
}

// 0x1217d0: NewZeroed<BYTE> (FMemStack::PushBytes + appMemzero)
// Note: retail inlined UE2's multi-instruction __asm appMemzero helper here;
// pure C memset matches PushBytes identically but cannot reproduce that __asm block.
__declspec(noinline) BYTE *NewZeroed(FMemStack &Mem, INT Count, INT Align)
{
    BYTE *Result = Mem.PushBytes(Count, Align);
    memset(Result, 0, Count);
    return Result;
}

// 0x121830: AActor::GetLocation_121830 (neutral name; lighting/view location helper)
__declspec(noinline) FVector AActor::GetLocation_121830()
{
    return (IsA(APawn::StaticClass()) && ((APawn *)this)->unk_38c)
        ? ((APawn *)this)->unk_38c->Location
        : Location;
}

// 0x121880: FColor::operator+= (ORIGINAL-ASM in retail: 4-channel saturating add via
// inline __asm add/adc/not/or; written here in equivalent pure C++).
void FColor::operator+=(FColor C)
{
    B = (BYTE)Min((INT)B + (INT)C.B, 255);
    G = (BYTE)Min((INT)G + (INT)C.G, 255);
    R = (BYTE)Min((INT)R + (INT)C.R, 255);
    A = (BYTE)Min((INT)A + (INT)C.A, 255);
}

// 0x1218e0: FColor::Brightness
__declspec(noinline) FLOAT FColor::Brightness() const
{
    return (2.f * R + 3.f * G + B) / (6.f * 256.f);
}

// 0x121920: AActor::LifeFraction
__declspec(noinline) FLOAT AActor::LifeFraction()
{
    return Clamp(1.f - LifeSpan / GetClass()->GetDefaultActor()->LifeSpan, 0.f, 1.f);
}

// Scaffolding for the link, not part of the unit.
extern void Escape(void *);
extern void UseFloat(FLOAT);
extern void UsePtr(void *);
extern FMemStack GMem;
extern const TCHAR GMemStackTag[];

// Retail 0x577c0 (FMemStack::AllocateNewChunk), defined here unverified so the
// LTCG linker gives it its retail register convention (this in EDI, MinSize in EAX).
__declspec(noinline) BYTE *FMemStack::AllocateNewChunk(INT MinSize)
{
    FTaggedMemory *Chunk = 0;
    for (FTaggedMemory **Link = &UnusedChunks; *Link; Link = &(*Link)->Next) {
        if ((*Link)->DataSize >= MinSize) {
            Chunk = *Link;
            *Link = (*Link)->Next;
            break;
        }
    }
    if (!Chunk) {
        INT DataSize = MinSize;
        if (DataSize < DefaultChunkSize - (INT)sizeof(FTaggedMemory))
            DataSize = DefaultChunkSize - (INT)sizeof(FTaggedMemory);
        Chunk = (FTaggedMemory *)GMalloc->Malloc(DataSize + sizeof(FTaggedMemory), GMemStackTag);
        Chunk->DataSize = DataSize;
    }
    Chunk->Next = TopChunk;
    TopChunk = Chunk;
    Top = Chunk->Data;
    End = Top + Chunk->DataSize;
    return Top;
}

struct FVecUser {
    void Consume(const FVector *Other);
};

void Driver_121770(INT Count, INT Align)
{
    Escape(&GMem);
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    UsePtr(NewOned(GMem, Count, Align));
}

void Driver_1217d0(INT Count, INT Align)
{
    Escape(&GMem);
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    UsePtr(NewZeroed(GMem, Count, Align));
}

void Driver_121830(AActor *A, FVector *Other)
{
    Escape(&APawn::PrivateStaticClass);
    FVector V = A->GetLocation_121830();
    ((FVecUser *)&V)->Consume(Other);
}

void Driver_1218e0(FColor *C)
{
    UseFloat(C->Brightness());
}

void Driver_121920(AActor *A)
{
    UseFloat(A->LifeFraction());
}
