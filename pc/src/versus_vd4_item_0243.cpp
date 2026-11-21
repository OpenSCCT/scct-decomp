// Work item 0243: Versus RVA 0x5a0a0-0x5a2fa. LTCG object (VC7.0 /GL).
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
void *appMemcpy(void *Dest, const void *Src, INT Count);

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Empty(INT ElementSize, INT Slack);
    INT Add(INT Count, INT ElementSize);
};

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FString(const FString &Other);
    ~FString();
    FString &operator=(const TCHAR *Other);  // RVA 0x4750, defined below
    const TCHAR *operator*() const { return ArrayNum ? Data : L""; }
};

extern "C" unsigned int wcslen(const TCHAR *);

// RVA 0x4750 (published separately; defined here so the LTCG link gives it
// its retail register convention).
FString &FString::operator=(const TCHAR *Other)
{
    if (Other != Data) {
        if (*Other == 0) {
            if (Data) { ArrayNum = 0; ArrayMax = 0; GMalloc->Free(Data); Data = 0; }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), L"FString::=");
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), L"FArray");
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}

// 16-byte value copied out of the owner (+0x50); neutral name.
struct FQuad_5a0a0
{
    INT A, B, C, D;
    FQuad_5a0a0() {}
    FQuad_5a0a0(INT InA, INT InB, INT InC, INT InD) : A(InA), B(InB), C(InC), D(InD) {}
};

// Object at owner+0x4f8: vtable slot 11 returns an INT; neutral name.
class UnnamedSub_5a0a0
{
public:
    virtual void V0(); virtual void V1(); virtual void V2(); virtual void V3();
    virtual void V4(); virtual void V5(); virtual void V6(); virtual void V7();
    virtual void V8(); virtual void V9(); virtual void V10();
    virtual INT GetValue();
};

// Owner class of 0x5a0a0; neutral name, layout from offsets used.
class UnnamedClass_5a0a0
{
public:
    char Pad00[0x28];
    INT Field28;
    char Pad2C[0x08];
    DWORD Flags;            // +0x34
    char Pad38[0x18];
    FQuad_5a0a0 Quad;       // +0x50
    char Pad60[0x34];
    FString Text;           // +0x94
    char PadA0[0x4f8 - 0xa0];
    UnnamedSub_5a0a0 *Sub;  // +0x4f8

};

struct FInfo_5a0a0
{
    FString Name;                 // +0x00
    UnnamedClass_5a0a0 *Owner;    // +0x0c
    INT Field28;                  // +0x10
    FQuad_5a0a0 Quad;             // +0x14
    INT Value;                    // +0x24
    INT Index0, Index1, Index2, Index3;  // +0x28
    INT Zero38;                   // +0x38
    INT Zero3C;                   // +0x3c
    DWORD Flags;                  // +0x40

    FInfo_5a0a0(UnnamedClass_5a0a0 *InOwner);
};

// RVA 0x5a0a0
FInfo_5a0a0::FInfo_5a0a0(UnnamedClass_5a0a0 *InOwner)
: Owner(InOwner)
, Field28(InOwner ? InOwner->Field28 : 0)
, Quad(InOwner ? InOwner->Quad : FQuad_5a0a0(0, 0, 0, 0))
, Value(InOwner ? InOwner->Sub->GetValue() : 0)
, Index0(-1)
, Index1(-1)
, Index2(-1)
, Index3(-1)
, Zero38(0)
, Zero3C(0)
, Flags(InOwner ? InOwner->Flags : 0)
{
    if (InOwner && *InOwner->Text && (InOwner->Flags & 1))
        Name = *InOwner->Text;
}

// RVA 0x5a1a0 / 0x5a210: base class and member types; neutral names.
class UnnamedBase_5a1a0
{
public:
    char Pad00[0x0c];
    ~UnnamedBase_5a1a0();
};

class UnnamedClass_5a1a0 : public UnnamedBase_5a1a0
{
public:
    void *Data;   // +0x0c
    INT Num;      // +0x10
    ~UnnamedClass_5a1a0();
};

// RVA 0x5a1a0
UnnamedClass_5a1a0::~UnnamedClass_5a1a0()
{
    if (Data)
        GMalloc->Free(Data);
    Data = 0;
    Num = 0;
}

struct UnnamedMember_5a210
{
    FString A, B;   // scaffolding layout for the stand-in below
    UnnamedMember_5a210();
};

class UnnamedClass_5a210
{
public:
    INT Pad00, Pad04;
    INT Value;                     // +0x08
    FString List;                  // +0x0c (3-dword array, empty-constructed)
    UnnamedMember_5a210 Member;    // +0x18
    UnnamedClass_5a210(INT InValue);
};

// RVA 0x5a210
UnnamedClass_5a210::UnnamedClass_5a210(INT InValue)
: Value(InValue)
{
}

// RVA 0x5a260: UE2 TMap (Pairs, Hash, HashCount) assignment pieces.
struct FKeyObject_5a260 { void *VTable; INT Index; };
struct FPair_5a260 { INT HashNext; FKeyObject_5a260 *Key; INT Value; };
struct FPairArray_5a260 : public FArray
{
    FPairArray_5a260 &operator=(const FPairArray_5a260 &Other);
};

struct FMap_5a260
{
    FPairArray_5a260 Pairs;  // +0x00
    INT *Hash;               // +0x0c
    INT HashCount;           // +0x10
    void Rehash();
    FMap_5a260 &operator=(const FMap_5a260 &Other)
    {
        Pairs = Other.Pairs;
        HashCount = Other.HashCount;
        Rehash();
        return *this;
    }
};

struct FIntArray_5a260 : public FArray
{
    FIntArray_5a260 &operator=(const FIntArray_5a260 &Other)
    {
        if (this != &Other)
        {
            Empty(sizeof(INT), Other.ArrayNum);
            appMemcpy(Data, Other.Data, Other.ArrayNum * sizeof(INT));
            ArrayNum = Other.ArrayNum;
        }
        return *this;
    }
};

// TArray<FInfo_5a0a0> (0x44-byte elements).
struct FObjArray_5a260 : public FArray
{
    FObjArray_5a260 &operator=(const FObjArray_5a260 &Other);
    void EmptyObjects(INT Slack);   // FUN_1095ad30
};

class UnnamedClass_5a260
{
public:
    char Pad00[0x28];
    FObjArray_5a260 Objects;   // +0x28
    FMap_5a260 MapA;           // +0x34
    FMap_5a260 MapB;           // +0x48
    FIntArray_5a260 Ints;      // +0x5c
    INT Field68;               // +0x68
    INT Field6C;               // +0x6c
    void CopyFrom(const UnnamedClass_5a260 &Other);
};

// RVA 0x5a260
void UnnamedClass_5a260::CopyFrom(const UnnamedClass_5a260 &Other)
{
    Objects = Other.Objects;
    Field6C = Other.Field6C;
    MapA = Other.MapA;
    MapB = Other.MapB;
    Ints = Other.Ints;
    Field68 = Other.Field68;
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *P) { return P; }
void Escape(void *);
INT Driver_5a0a0(UnnamedClass_5a0a0 *O) { FInfo_5a0a0 I(O); return I.Value; }
void Driver_5a1a0(UnnamedClass_5a1a0 *O) { O->~UnnamedClass_5a1a0(); }
void Driver_5a210(UnnamedClass_5a210 *O, INT V) { new (O) UnnamedClass_5a210(V); }
void Driver_5a260(UnnamedClass_5a260 *A, const UnnamedClass_5a260 *B, UnnamedClass_5a260 *C) { A->CopyFrom(*B); C->CopyFrom(*A); B = C; A->CopyFrom(*B); }
// Stand-ins for callees retail calls (FUN_10aeecc0, FUN_1094f670), defined so
// the LTCG link gives them their retail this-on-stack convention (both have
// exception frames in retail).
void External_Scaffold(void *);
struct FScaffoldPart { FScaffoldPart(); ~FScaffoldPart(); };
__declspec(noinline) UnnamedBase_5a1a0::~UnnamedBase_5a1a0() { FScaffoldPart P; External_Scaffold(this); }
__declspec(noinline) UnnamedMember_5a210::UnnamedMember_5a210() { FScaffoldPart P; External_Scaffold(this); }
// Stand-ins for FUN_1095aae0, FUN_1095ad70 and FUN_1095aca0 (UE2 TArray copy
// and TMap::Rehash), written after retail so the LTCG link gives them their
// retail register conventions.
extern const TCHAR HashMapHash_Tag[];   // L"HashMapHash"
inline void *operator new(unsigned int Size, FArray &A, INT ElementSize)
{
    INT Index = A.Add(1, ElementSize);
    return (char *)A.Data + Index * ElementSize;
}
__declspec(noinline) void FObjArray_5a260::EmptyObjects(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&((FInfo_5a0a0 *)Data)[i])->~FInfo_5a0a0();
    Empty(sizeof(FInfo_5a0a0), Slack);
}
__declspec(noinline) FObjArray_5a260 &FObjArray_5a260::operator=(const FObjArray_5a260 &Other)
{
    if (this != &Other)
    {
        EmptyObjects(Other.ArrayNum);
        for (INT i = 0; i < Other.ArrayNum; i++)
            new(*this, sizeof(FInfo_5a0a0)) FInfo_5a0a0(((FInfo_5a0a0 *)Other.Data)[i]);
    }
    return *this;
}
__declspec(noinline) FPairArray_5a260 &FPairArray_5a260::operator=(const FPairArray_5a260 &Other)
{
    if (this != &Other)
    {
        Empty(sizeof(FPair_5a260), Other.ArrayNum);
        for (INT i = 0; i < Other.ArrayNum; i++)
            new(*this, sizeof(FPair_5a260)) FPair_5a260(((FPair_5a260 *)Other.Data)[i]);
    }
    return *this;
}
__declspec(noinline) void FMap_5a260::Rehash()
{
    INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), HashMapHash_Tag);
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.ArrayNum; i++)
    {
        FPair_5a260 &Pair = ((FPair_5a260 *)Pairs.Data)[i];
        INT iHash = (Pair.Key ? Pair.Key->Index : 0) & (HashCount - 1);
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        GMalloc->Free(Hash);
    Hash = NewHash;
}
