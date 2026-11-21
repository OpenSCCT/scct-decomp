// Work item 0202: Versus RVA 0xe5af0-0xe5d67. Built for /GL + /LTCG.
// The first two functions were compiled without optimisation (frame pointer,
// this spilled to the stack), reproduced with #pragma optimize("", off).
// Verified with try_ltcg.py /O2 /Gy and all three Driver_* functions as --root.

// UnnamedClass_4bc0: neutral name (see versus_vd2_item_0007.cpp).
class UnnamedClass_4bc0
{
public:
    char Pad00[0x20];
    int Index;                   // +0x20
    UnnamedClass_4bc0* Children; // +0x24
    UnnamedClass_4bc0* Next;     // +0x28
    int Contains(UnnamedClass_4bc0* Other);
};

struct UnnamedEntry_4bb0 { char Pad00[0xc]; int Payload; };
extern UnnamedClass_4bc0 UnnamedSingleton_4c60;
extern UnnamedEntry_4bb0** UnnamedTable_4bb0;

// RVA 0x4c60: returns the address of a single static object (a StaticClass shape).
UnnamedClass_4bc0* UnnamedStatic_4c60()
{
    return &UnnamedSingleton_4c60;
}

// RVA 0x4bb0: looks Obj up in a global table by its index (+0x20).
int* UnnamedLookup_4bb0(UnnamedClass_4bc0* Obj)
{
    return &UnnamedTable_4bb0[Obj->Index]->Payload;
}

// RVA 0x68f20: an empty function.
void UnnamedEmpty_68f20(int* A, int B, int C);

struct UnnamedInner_e5af0 { int Field0; int Field4; };

// UnnamedClass_e5af0: neutral name; a pointer at +0 and a value at +4.
class UnnamedClass_e5af0
{
public:
    UnnamedInner_e5af0* Inner; // +0
    int Value;                 // +4
    void Touch();
};

#pragma optimize("", off)
// RVA 0xe5af0
void UnnamedClass_e5af0::Touch()
{
    int InnerValue = Inner->Field4;
    UnnamedEmpty_68f20(UnnamedLookup_4bb0(UnnamedStatic_4c60()), InnerValue, Value);
}

// RVA 0xe5b30: the Cast<T> shape: Src if it belongs to the class, else null.
UnnamedClass_4bc0* UnnamedCast_e5b30(UnnamedClass_4bc0* Src)
{
    // Two locals the original reserved but never used: /Od keeps their slots
    // above the ?: temporary (sub esp, 0xc).
    int UnusedA;
    int UnusedB;
    return Src && Src->Contains(UnnamedStatic_4c60()) ? Src : 0;
}
#pragma optimize("", on)


// ---------------------------------------------------------------------------
// RVA 0xe5b80: TLazyArray<BYTE> serialisation (UE2 UnTemplate.h shape, with
// SCCT's version 0xaf format and a GUglyHackFlags bit that loads at once).
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef int INT;
typedef DWORD UBOOL;
typedef unsigned short TCHAR;

struct FCompactIndex { INT Value; };
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FLazyLoader;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(void *Object);                     // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    virtual void Slot18();                                  // +0x18
    virtual void Slot1c();                                  // +0x1c
    virtual void Slot20();                                  // +0x20
    virtual void Slot24();                                  // +0x24
    virtual INT Tell();                                     // +0x28
    virtual INT TotalSize();                                // +0x2c
    virtual UBOOL AtEnd();                                  // +0x30
    virtual void Slot34();                                  // +0x34
    virtual void Slot38();                                  // +0x38
    virtual void Seek(INT InPos);                           // +0x3c
    virtual void AttachLazyLoader(FLazyLoader *LazyLoader); // +0x40

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.Serialize(&I, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;          // +0x04
    INT ArNetVer;       // +0x08
    INT ArLicenseeVer;  // +0x0c
    UBOOL ArIsLoading;  // +0x10
    UBOOL ArIsSaving;   // +0x14
};

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
extern const TCHAR TArrayBYTE_Tag[];

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Realloc(INT ElementSize);   // 0x4600
    void Free();
};

template <class T> class TArray : public FArray {};

class FLazyLoader
{
public:
    virtual void Load();
    FArchive *SavedAr;
    INT SavedPos;
};

template <class T> class TLazyArray : public FLazyLoader, public TArray<T> {};

extern UBOOL GLazyLoad;          // 0xc96924
extern DWORD GUglyHackFlags;     // 0xc968ec

// Retail callees given register conventions by LTCG; defined here so the
// linker can choose them (scaffolding, matched elsewhere).
#pragma auto_inline(off)
// RVA 0x1ea40 (copied from versus_vd2_item_0116.cpp).
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

// RVA 0xa8ea0: bulk TArray<BYTE> serialisation.
FArchive &operator<<(FArchive &Ar, TArray<BYTE> &A)
{
    Ar.CountBytes(A.ArrayNum, A.ArrayMax);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (!A.Data) {
            if (!A.ArrayNum)
                return Ar;
            A.Data = GMalloc->Malloc(A.ArrayNum, TArrayBYTE_Tag);
        } else if (A.ArrayNum) {
            A.Realloc(1);
        } else {
            A.Free();
            return Ar;
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum);
    return Ar;
}
#pragma auto_inline(on)

FArchive &operator<<(FArchive &Ar, TLazyArray<BYTE> &This)
{
    if (Ar.IsLoading()) {
        INT SeekPos = 0;
        if (Ar.Ver() <= 61) {
            Ar.AttachLazyLoader(&This);
            INT SkipCount;
            Ar << AR_INDEX(SkipCount);
            // SCCT drops the old-format skip: the position is read and discarded.
            Ar.Tell();
            return Ar;
        }
        if (Ar.Ver() >= 0xaf) {
            INT Skip;
            Ar << Skip << (TArray<BYTE> &)This;
            return Ar;
        }
        Ar << SeekPos;
        if (GUglyHackFlags & 8)
            Ar << (TArray<BYTE> &)This;
        else
            Ar.AttachLazyLoader(&This);
        if (!GLazyLoad)
            This.Load();
        Ar.Seek(SeekPos);
    } else if (Ar.IsSaving() && Ar.Ver() > 61) {
        if (Ar.Ver() >= 0xaf) {
            INT Skip = 0;
            Ar << Skip << (TArray<BYTE> &)This;
        } else {
            // Save out count for skipping over this data.
            INT CountPos = Ar.Tell();
            Ar << CountPos << (TArray<BYTE> &)This;
            INT EndPos = Ar.Tell();
            Ar.Seek(CountPos);
            Ar << EndPos;
            Ar.Seek(EndPos);
        }
    } else {
        Ar << (TArray<BYTE> &)This;
    }
    return Ar;
}

// Scaffolding for the link, not part of the unit.
void Escape(void*);
void Driver_e5af0(UnnamedClass_e5af0* P) { P->Touch(); }
void* Driver_e5b30(UnnamedClass_4bc0* P) { Escape(&UnnamedTable_4bb0); return UnnamedCast_e5b30(P); }
void Driver_e5b80(FArchive *Ar, TLazyArray<BYTE> *L) { Escape(&GLazyLoad); Escape(&GUglyHackFlags); *Ar << *L; }
