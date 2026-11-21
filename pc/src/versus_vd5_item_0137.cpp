// Work item w3 0137 (RVA 0xc0f50-0xc1328): four TArray serializers from an
// LTCG object (custom register conventions). Element types are not named in
// the binary, so they carry neutral names after their serializer's RVA.
//  0xc0f50 operator<<(FArchive&, TArray<FUnnamedRecord_c0f50>&): archive in EAX,
//          array on the stack (12-byte element: FName, INT, INT).
//  0xc1060 operator<<(FArchive&, TArray<FUnnamedRecord_c1060>&): array in EBX,
//          archive on the stack (0x68-byte element with constructor/destructor).
//  0xc1140 operator<<(FArchive&, TArray<FUnnamedRecord_c1140>&): archive in EAX,
//          array in EBX (6-byte element, bulk serializer, "operator<<(TArray)").
//  0xc11e0 operator<<(FArchive&, TArray<FUnnamedRecord_c11e0>&): both on the
//          stack (0x40-byte element).
// Callees of other functions (0x1ea40, 0xc0de0, 0xb4750, 0xc2ea0, 0xc2e00) are
// restated as stand-ins so the LTCG link gives them their retail register forms.
// 0xc2ea0's members (0xc3280, 0xc2f20, 0xb4910) are restated too: without them
// the link passes 0xc2ea0's value in EAX instead of EDI.
// All four match with try_ltcg.py --flags "/O2 /Gy", each rooted at its
// Driver_<rva> (0xc1060 at ?Driver_c1060@@YAXPAUFDriverOwner_c1060@@AAVFArchive@@@Z).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

#pragma pack(push, 4)

class UObject;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int, void *Mem) { return Mem; }

struct FCompactIndex
{
    INT Value;
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FName
{
public:
    INT Index;
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(UObject *Object);                  // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    // MSVC lays overloaded virtuals out in reverse order.
    virtual FArchive &operator<<(FName &N);                 // +0x1c
    virtual FArchive &operator<<(UObject *&Res);            // +0x18

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.Serialize(&I, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.Serialize(&F, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);        // 0x44e0
    void Empty(INT ElementSize, INT Slack);     // 0x4550
    void Realloc(INT ElementSize);              // 0x4600
};

template <class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack);
};
template <class T> inline void TArray<T>::Empty(INT Slack) { FArray::Empty(sizeof(T), Slack); }

template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

// The standard UE2 TArray serializer.
template <class T> FArchive &operator<<(FArchive &Ar, TArray<T> &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(A) T;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// ---- 0xc0f50 ----
struct FUnnamedRecord_c0f50
{
    FName Name;
    INT A;
    INT B;
    friend FArchive &operator<<(FArchive &Ar, FUnnamedRecord_c0f50 &R) { return Ar << R.Name << R.A << R.B; }
};
// RVA 0xc0f50: instance of the template above.
template FArchive &operator<<(FArchive &Ar, TArray<FUnnamedRecord_c0f50> &A);

// ---- 0xc1060 ----
// Member types of the 0x68-byte element (serializers at 0xc3280, 0xc2f20, 0xb4910).
struct FUnnamedBulk_c3280 { INT X; };
FArchive &operator<<(FArchive &Ar, TArray<FUnnamedBulk_c3280> &A);   // 0xc3280
struct FUnnamedElement_c2f20
{
    INT V[10];
    friend FArchive &operator<<(FArchive &Ar, FUnnamedElement_c2f20 &E); // element serializer
};
struct FUnnamedValue_b4910
{
    INT V;
    friend FArchive &operator<<(FArchive &Ar, FUnnamedValue_b4910 &E);  // 0xb4910
};

// The element is UnnamedClass_b4750 of item w3 0110 (vtable 0x10c049e4).
struct FUnnamedRecord_c1060
{
    FUnnamedRecord_c1060();     // 0xb4750
    virtual ~FUnnamedRecord_c1060();
    INT Unk04, Unk08, Unk0C, Unk10, Unk14, Unk18;
    TArray<FUnnamedBulk_c3280> Unk1C;
    TArray<FUnnamedElement_c2f20> Unk28;
    FUnnamedValue_b4910 Unk34;
    INT Unk38, Unk3C, Unk40, Unk44, Unk48, Unk4C, Unk50, Unk54, Unk58, Unk5C, Unk60, Unk64;
    friend FArchive &operator<<(FArchive &Ar, FUnnamedRecord_c1060 &R);   // 0xc2ea0
};
// Stand-in for 0xc0de0, TArray::Empty destroying its elements (array in ESI,
// Slack on the stack); another function, not part of this unit's match.
template <> __declspec(noinline) void TArray<FUnnamedRecord_c1060>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~FUnnamedRecord_c1060();
    FArray::Empty(sizeof(FUnnamedRecord_c1060), Slack);
}
// RVA 0xc1060: instance of the template above.
template FArchive &operator<<(FArchive &Ar, TArray<FUnnamedRecord_c1060> &A);

// ---- 0xc1140 ----
struct FUnnamedRecord_c1140
{
    BYTE Bytes[6];
};

extern const TCHAR OperatorShlTArray_Tag[];   // L"operator<<(TArray)"

// RVA 0xc1140: the bulk serializer for plain-data elements.
FArchive &operator<<(FArchive &Ar, TArray<FUnnamedRecord_c1140> &A)
{
    A.CountBytes(Ar);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (A.Data == 0) {
            if (A.ArrayNum)
                A.Data = GMalloc->Malloc(A.ArrayNum * sizeof(FUnnamedRecord_c1140), OperatorShlTArray_Tag);
            else
                return Ar;
        } else {
            if (A.ArrayNum) {
                A.Realloc(sizeof(FUnnamedRecord_c1140));
            } else {
                A.ArrayNum = 0;
                A.ArrayMax = 0;
                GMalloc->Free(A.Data);
                A.Data = 0;
                return Ar;
            }
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(FUnnamedRecord_c1140));
    return Ar;
}

// ---- 0xc11e0 ----
struct FUnnamedPart_c2e00
{
    BYTE Bytes[0x2c];
    friend FArchive &operator<<(FArchive &Ar, FUnnamedPart_c2e00 &P);    // 0xc2e00
};
struct FUnnamedRecord_c11e0
{
    FName Name;                 // 0x00
    INT A;                      // 0x04
    FUnnamedPart_c2e00 Part;    // 0x08
    INT B;                      // 0x34
    INT C;                      // 0x38
    INT Unused;                 // 0x3c, not serialized
    friend FArchive &operator<<(FArchive &Ar, FUnnamedRecord_c11e0 &R) { return Ar << R.Name << R.A << R.Part << R.C << R.B; }
};
// RVA 0xc11e0: instance of the template above.
template FArchive &operator<<(FArchive &Ar, TArray<FUnnamedRecord_c11e0> &A);

// ---- Stand-ins for callees of other functions, defined so the link gives them
// their retail register conventions. Not part of this unit's match. ----

// 0x1ea40 (archive in ESI, index in EDI in retail), from item 0116.
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

void Scaffold_Use(void *);

// 0xb4750 (this in EAX, returns this), after item w3 0110.
__declspec(noinline) FUnnamedRecord_c1060::FUnnamedRecord_c1060()
{
    Unk1C.Data = 0; Unk1C.ArrayNum = 0; Unk1C.ArrayMax = 0;
    Unk28.Data = 0; Unk28.ArrayNum = 0; Unk28.ArrayMax = 0;
    Unk38 = 0; Unk3C = 0; Unk40 = 0; Unk44 = 0; Unk48 = 0; Unk4C = 0;
    Unk50 = 0; Unk54 = 0; Unk58 = 0; Unk5C = 0; Unk60 = 0; Unk64 = 0;
}

// 0xc2ea0 (archive in ESI, value in EDI), shape after item w3 0143.
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FUnnamedRecord_c1060 &R)
{
    Ar << R.Unk04 << R.Unk08 << R.Unk0C;
    Ar << R.Unk10 << R.Unk14 << R.Unk18;
    return Ar << R.Unk1C << R.Unk28 << R.Unk34;
}

// 0xc3280 (archive in EAX, array in EBX), bulk form like 0xc1140.
__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<FUnnamedBulk_c3280> &A)
{
    A.CountBytes(Ar);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        A.Realloc(sizeof(FUnnamedBulk_c3280));
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(FUnnamedBulk_c3280));
    return Ar;
}

// 0xc2e00 (archive in ESI, value in EAX).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FUnnamedPart_c2e00 &P)
{
    Ar.Serialize(P.Bytes, 4);
    Ar.Serialize(P.Bytes + 8, 4);
    return Ar;
}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
FArchive &Driver_c0f50(FArchive &Ar, char *Owner)
{
    return Ar << *(TArray<FUnnamedRecord_c0f50> *)(Owner + 0x30);
}
struct FDriverOwner_c1060
{
    BYTE Pad[0x30];
    TArray<FUnnamedRecord_c1060> Records;
    void Serialize(FArchive &Ar) { Ar << Records; Ar << Records; }
};
void Driver_c1060(FDriverOwner_c1060 *Owner, FArchive &Ar)
{
    Owner->Serialize(Ar);
}
FArchive &Driver_c1140(FArchive &Ar, char *Owner)
{
    Escape(&GMalloc);
    return Ar << *(TArray<FUnnamedRecord_c1140> *)(Owner + 0x30);
}
FArchive &Driver_c11e0(FArchive &Ar, char *Owner)
{
    return Ar << *(TArray<FUnnamedRecord_c11e0> *)(Owner + 0x30);
}
