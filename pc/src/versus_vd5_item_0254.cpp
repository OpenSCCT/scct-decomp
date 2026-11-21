// Work item 0254 (w3): Versus RVA 0xf47a0-0xf49d7.
// Built with VC7.0 /GL and linked with /LTCG: the TArray helpers take the
// array in ESI, the FColor array serializer takes the archive in EAX.
// Neutral names (UnnamedClass_47a0 etc.): no vtable label or string names
// the class with vtable 0x10c04020 yet.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
inline void *operator new(unsigned int, void *Mem) { return Mem; }

class UObject;

struct FCompactIndex
{
    INT Value;
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(UObject *Object);                  // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B)
    {
        Ar.Serialize(&B, 1);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);        // 0x44e0
    void Empty(INT ElementSize, INT Slack);     // 0x4550
};

template <class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
};

struct FColor
{
    BYTE B, G, R, A;
    friend FArchive &operator<<(FArchive &Ar, FColor &Color)
    {
        return Ar << Color.R << Color.G << Color.B << Color.A;
    }
};

// RVA 0x1ea40 (published in versus_vd2_item_0116.cpp): defined here so the
// LTCG link gives it its retail convention (archive in ESI, index in EDI).
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
    } else {
        INT Original = I.Value;
        DWORD V = Original >= 0 ? Original : -Original;
        BYTE B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
        I.Value = 0;
        Ar << B0;
        if (B0 & 0x40) {
            V >>= 6;
            BYTE B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B1;
            if (B1 & 0x80) {
                V >>= 7;
                BYTE B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B2;
                if (B2 & 0x80) {
                    V >>= 7;
                    BYTE B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                    Ar << B3;
                    if (B3 & 0x80) {
                        V >>= 7;
                        BYTE B4 = V;
                        Ar << B4;
                        I.Value = B4;
                    }
                    I.Value = (I.Value << 7) + (B3 & 0x7f);
                }
                I.Value = (I.Value << 7) + (B2 & 0x7f);
            }
            I.Value = (I.Value << 7) + (B1 & 0x7f);
        }
        I.Value = (I.Value << 6) + (B0 & 0x3f);
        if (B0 & 0x80)
            I.Value = -I.Value;
    }
    return Ar;
}

// RVA 0xf48e0: TArray<FColor> serializer (archive in EAX, array on the stack).
FArchive &operator<<(FArchive &Ar, TArray<FColor> &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(sizeof(FColor), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(&((FColor *)A.Data)[A.Add(1, sizeof(FColor))]) FColor;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// 0x28-byte element with an out-of-line destructor (RVA 0xf49e0).
struct UnnamedElement_49e0
{
    ~UnnamedElement_49e0();
    INT Fields[10];
};

// RVA 0xf48a0: TArray<UnnamedElement_49e0>::Empty (array in ESI).
class UnnamedElementArray_48a0 : public TArray<UnnamedElement_49e0>
{
public:
    // Retail callers live in other objects; noinline stands in for them.
    __declspec(noinline) void Empty(INT Slack);
};
void UnnamedElementArray_48a0::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~UnnamedElement_49e0();
    FArray::Empty(sizeof(UnnamedElement_49e0), Slack);
}

// RVA 0xf4860: TLazyArray::Unload (array in ESI). SavedPos < 0 marks a
// loaded lazy array; unloading empties it and flips the sign back.
class FLazyLoader
{
public:
    virtual void Load() = 0;
    FArchive *SavedAr;
    INT SavedPos;
};
template <class T> class TLazyArray : public FLazyLoader, public TArray<T>
{
public:
    void Load();
    // Non-virtual here: retail calls it directly with the array in ESI.
    // Retail callers live in other objects; noinline stands in for them.
    __declspec(noinline) void Unload();
};
template <class T> void TLazyArray<T>::Unload()
    {
        if (SavedPos < 0) {
            this->ArrayNum = 0;
            if (this->Data) {
                GMalloc->Free(this->Data);
                this->Data = 0;
                this->ArrayMax = 0;
            }
            SavedPos *= -1;
        }
}
template void TLazyArray<BYTE>::Unload();


// ---- RVA 0xf47a0 (constructor) and 0xf4820 (Destroy) of the class with
// vtable 0x10c04020. Super::Destroy() is UObject::Destroy (RVA 0x15ce0).
class UObject
{
public:
    virtual ~UObject();
    virtual void Destroy();
    BYTE ObjectData[0x2c];
};

extern const TCHAR UnnamedTag_47a0[];       // 0x10c109d8, the allocation tag

// 0x14-byte helper with vtable 0x10c040d8; constructor at RVA 0xf4460
// (object in ESI, owner in EAX). Defined here only so the LTCG link gives
// its callers the retail convention; it is published with work item 0253.
extern unsigned __int64 GUnnamedCounter_4460;   // 0x10c96930
#pragma pack(push, 4)
struct UnnamedHelper_4460
{
    __declspec(noinline) UnnamedHelper_4460(void *InOwner)
        : Owner(InOwner), Id(GUnnamedCounter_4460++ * 0x100 + 0xe0), Active(1) {}
    virtual void Slot0();
    void *Owner;
    unsigned __int64 Id;
    INT Active;
};
#pragma pack(pop)

// Base class; constructor at RVA 0xf26e0 (work item 0245), declared here
// with a stand-in body so the link gives it the retail convention
// (this on the stack, ret 4). Its field at +0x6c holds another helper.
class UnnamedBase_26e0 : public UObject
{
public:
    __declspec(noinline) UnnamedBase_26e0();
    BYTE BaseData[0x6c - 0x30];
    UnnamedHelper_4460 *Helper6c;            // +0x6c
    BYTE BaseData2[0xd8 - 0x70];
};

class UnnamedClass_47a0 : public UnnamedBase_26e0
{
public:
    __declspec(noinline) UnnamedClass_47a0();
    void Destroy();
    UnnamedHelper_4460 *HelperD8;            // +0xd8
};

// RVA 0xf47a0.
UnnamedClass_47a0::UnnamedClass_47a0()
{
    HelperD8 = new(UnnamedTag_47a0) UnnamedHelper_4460(this);
}

// RVA 0xf4820.
void UnnamedClass_47a0::Destroy()
{
    GMalloc->Free(HelperD8);
    HelperD8 = 0;
    GMalloc->Free(Helper6c);
    Helper6c = 0;
    UObject::Destroy();
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_48e0(FArchive *Ar, TArray<FColor> *A) { Escape(&GMalloc); *Ar << *A; }
void Driver_48a0(UnnamedElementArray_48a0 *A, UnnamedElementArray_48a0 *B, INT Slack)
{
    Escape(&GMalloc);
    A->Empty(Slack); Escape(A); B->Empty(Slack); Escape(B); A->Empty(0); Escape(A); B->Empty(0);
}
void Driver_4860(TLazyArray<BYTE> *A, TLazyArray<BYTE> *B, TLazyArray<BYTE> *C, TLazyArray<BYTE> *D)
{
    Escape(&GMalloc);
    A->Unload(); Escape(A); B->Unload(); Escape(B); C->Unload(); Escape(C); D->Unload(); Escape(D);
    A->Unload(); B->Unload(); C->Unload(); D->Unload();
}
UnnamedBase_26e0::UnnamedBase_26e0()
{
    Helper6c = new(UnnamedTag_47a0) UnnamedHelper_4460(this);
}
void Driver_47a0(void *Mem, void *Mem2)
{
    Escape(&GMalloc); Escape(&GUnnamedCounter_4460);
    UnnamedClass_47a0 *A = new(Mem) UnnamedClass_47a0;
    Escape(A);
    UnnamedClass_47a0 *B = new(Mem2) UnnamedClass_47a0;
    Escape(B);
    A->Destroy();
}
