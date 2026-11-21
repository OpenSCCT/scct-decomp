// Work item 0166 (RVA 0xcc570-0xcc906): TArray helpers and serializers from
// an LTCG object (custom register conventions). The element types are not
// named anywhere in the binary; names are neutral, after an RVA.
//  0xcc570 TArray<FUnnamedElem_a4770>::Empty(Slack), this in ESI.
//  0xcc5b0 TArray<FUnnamedElem_a4780>::~TArray, this on the stack, EH frame.
//  0xcc620 FUnnamedStruct_cc620::operator=, this in EAX, source in EBX.
//  0xcc6c0 TArray<FUnnamedElem_a4780>::Remove(Index, Count), Index in EDI.
//  0xcc710 operator<<(FArchive&, TArray<FUnnamedElem_cd1b0>&), Ar EAX, A EBX.
//  0xcc820 operator<<(FArchive&, TArray<FUnnamedElem_a4770>&), Ar stack, A EBX.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef float FLOAT;

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

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(UObject *Object);                  // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    virtual FArchive &operator<<(UObject *&Res);            // +0x18

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B)
    {
        Ar.Serialize(&B, 1);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, INT &I)
    {
        Ar.Serialize(&I, 4);
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
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize);                    // 0x44e0
    void Empty(INT ElementSize, INT Slack);                 // 0x4550
    void Remove(INT Index, INT Count, INT ElementSize);     // 0x119c0
    void Realloc(INT ElementSize);                          // 0x4600
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray() { Remove(0, ArrayNum); }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack)
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&(*this)(i))->~T();
        FArray::Empty(sizeof(T), Slack);
    }
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
};

template <class T> inline void *operator new(unsigned int Size, TArray<T> &A)
{
    INT Index = A.Add(1, sizeof(T));
    return &A(Index);
}

// UnTemplate.h TArray serializer (a friend of TArray in Unreal's source).
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

// 20-byte element with a destructor (0xa4770, thiscall), a constructor
// (0xcd0e0, this in EAX) and a serializer (0xcd0f0, Ar in EDI, value in ESI).
struct FUnnamedElem_a4770
{
    UObject *Object;        // 0x00
    TArray<BYTE> Bytes;     // 0x04 (its destructor is the body of 0xa4770)
    INT Value;              // 0x10
    FUnnamedElem_a4770();
    ~FUnnamedElem_a4770();
    friend FArchive &operator<<(FArchive &Ar, FUnnamedElem_a4770 &E);
};

// 28-byte element whose destructor (0xa4780) takes this in EAX.
struct FUnnamedElem_a4780
{
    INT Unknown[7];
    ~FUnnamedElem_a4780();
};

// 20-byte trivially destructible element, inline constructor, serializer
// 0xcd1b0 (Ar in EDI, value in ECX).
struct FUnnamedElem_cd1b0
{
    INT A;
    INT B;
    _WORD C;
    _WORD D;
    _WORD E;
    _WORD F;
    _WORD G;
    _WORD H;            // 0x12, not set by the constructor
    FUnnamedElem_cd1b0()
    {
        A = 0;
        B = 0;
        G = 0;
        F = 0;
        C = 0;
        E = 0xffff;
        D = 0xffff;
    }
    friend FArchive &operator<<(FArchive &Ar, FUnnamedElem_cd1b0 &E);   // 0xcd1b0
};

// RVA 0xcc570.
template <> __declspec(noinline) void TArray<FUnnamedElem_a4770>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~FUnnamedElem_a4770();
    FArray::Empty(sizeof(FUnnamedElem_a4770), Slack);
}

// RVA 0xcc6c0.
template <> __declspec(noinline) void TArray<FUnnamedElem_a4780>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~FUnnamedElem_a4780();
    FArray::Remove(Index, Count, sizeof(FUnnamedElem_a4780));
}

// RVA 0xcc5b0.
template <> __declspec(noinline) TArray<FUnnamedElem_a4780>::~TArray()
{
    Remove(0, ArrayNum);
}

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
};

struct FUnnamedBlock_c0
{
    DWORD V[0x30];
};

struct FUnnamedStruct_cc620
{
    FVector A[3];           // 0x00
    FUnnamedBlock_c0 B;     // 0x24
    FVector C;              // 0xe4
    DWORD D, E, F, G, H;    // 0xf0
    FUnnamedStruct_cc620 &operator=(const FUnnamedStruct_cc620 &Other);
};

// RVA 0xcc620 (near miss: retail keeps the 3-element loop rolled, src in EBX).
__declspec(noinline) FUnnamedStruct_cc620 &FUnnamedStruct_cc620::operator=(const FUnnamedStruct_cc620 &Other)
{
    for (INT i = 0; i < 3; i++)
        A[i] = Other.A[i];
    B = Other.B;
    C = Other.C;
    D = Other.D;
    E = Other.E;
    F = Other.F;
    G = Other.G;
    H = Other.H;
    return *this;
}


// RVA 0xcc710 / 0xcc820: instantiated below.
template FArchive &operator<<(FArchive &Ar, TArray<FUnnamedElem_cd1b0> &A);
template FArchive &operator<<(FArchive &Ar, TArray<FUnnamedElem_a4770> &A);

// ---- Stand-ins for out-of-unit callees, defined so the LTCG link gives them
// their retail register conventions. Not part of the unit. ----
void External_Scaffold(void *);
void External_Scaffold2(void *, void *);
__declspec(noinline) FUnnamedElem_a4780::~FUnnamedElem_a4780() { External_Scaffold(this); }
__declspec(noinline) FUnnamedElem_a4770::FUnnamedElem_a4770() {}
struct FScaffoldPart { FScaffoldPart(); ~FScaffoldPart(); };
extern INT *GScaffoldMode;
extern const TCHAR ScaffoldTag[];
__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<BYTE> &A)
{
    A.CountBytes(Ar);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (A.Data == 0) {
            if (A.ArrayNum)
                A.Data = GMalloc->Malloc(A.ArrayNum, ScaffoldTag);
            else
                return Ar;
        } else {
            if (A.ArrayNum) {
                A.Realloc(1);
            } else {
                A.ArrayNum = 0;
                A.ArrayMax = 0;
                GMalloc->Free(A.Data);
                A.Data = 0;
                return Ar;
            }
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum);
    return Ar;
}
struct FScaffoldActor { BYTE Pad[0x2e8]; DWORD Flags1; DWORD Flags2; };
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FUnnamedElem_a4770 &E)
{
    UObject *Saved = E.Object;
    if (Ar.ArIsTrans) {
        INT Mode = GScaffoldMode[0x20];
        if ((Mode == 1 || Mode == 2 || Mode == 3) && Saved && !(((FScaffoldActor *)Saved)->Flags2 & 0x800000)
            && !(((FScaffoldActor *)Saved)->Flags1 & 0x20000))
            E.Object = 0;
    }
    Ar << E.Object << E.Bytes << E.Value;
    if (Ar.ArIsTrans) {
        INT Mode = GScaffoldMode[0x20];
        if (Mode == 1 || Mode == 2 || Mode == 3)
            E.Object = Saved;
    }
    return Ar;
}
struct FScaffoldLocal
{
    INT X0;
    INT Arr[3];         // a TArray<BYTE> in the real type
    INT X[3];
    FScaffoldLocal();
    ~FScaffoldLocal();
};
INT External_ScaffoldInt();
__declspec(noinline) FScaffoldLocal::FScaffoldLocal() { X0 = 0; Arr[0] = Arr[1] = Arr[2] = 0; X[1] = External_ScaffoldInt(); X[0] = X[2] = 0; }
__declspec(noinline) FScaffoldLocal::~FScaffoldLocal() { External_Scaffold(this); }
struct FScaffoldLocal2 { INT X[3]; FScaffoldLocal2() { X[0] = X[1] = X[2] = 0; } ~FScaffoldLocal2(); };
struct FScaffoldLocalB
{
    INT X0;
    INT Arr[3];         // a TArray<_WORD> in the real type
    INT X[3];
    FScaffoldLocalB();
    ~FScaffoldLocalB();
};
__declspec(noinline) FScaffoldLocalB::FScaffoldLocalB() { X0 = 1; Arr[0] = Arr[1] = Arr[2] = 0; X[1] = External_ScaffoldInt(); X[0] = X[2] = 0; }
__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<_WORD> &A)
{
    A.CountBytes(Ar);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (A.Data == 0) {
            if (A.ArrayNum)
                A.Data = GMalloc->Malloc(A.ArrayNum * 2, ScaffoldTag);
            else
                return Ar;
        } else {
            if (A.ArrayNum) {
                A.Realloc(2);
            } else {
                A.ArrayNum = 0;
                A.ArrayMax = 0;
                GMalloc->Free(A.Data);
                A.Data = 0;
                return Ar;
            }
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum * 2);
    return Ar;
}
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FUnnamedElem_cd1b0 &E)
{
    if (Ar.ArVer < 0x5c) {
        INT Dummy;
        _WORD W1, W2;
        if (Ar.ArVer >= 0x4a)
            Ar.Serialize(&E.B, 4);
        else if (Ar.ArIsLoading)
            E.B = 0;
        Ar << *(UObject **)&E.A;
        Ar.Serialize(&Dummy, 4);
        Ar.Serialize(&E.H, 2);
        Ar.Serialize(&E.F, 2);
        Ar.Serialize(&W1, 2);
        Ar.Serialize(&W2, 2);
    } else if (Ar.ArVer < 0x70) {
        FScaffoldLocal L1;
        FScaffoldLocalB L2, L3;
        INT V1, V2, V3, V4;
        Ar.Serialize(&E.B, 4);
        Ar.Serialize(&E.F, 2);
        Ar.Serialize(&E.G, 2);
        Ar << *(UObject **)&E.A << V1 << *(TArray<BYTE> *)L1.Arr << V2 << *(TArray<_WORD> *)L2.Arr << V3 << *(TArray<_WORD> *)L3.Arr << V4;
    } else {
        Ar.Serialize(&E.B, 4);
        Ar.Serialize(&E.C, 2);
        Ar.Serialize(&E.D, 2);
        Ar.Serialize(&E.E, 2);
        Ar.Serialize(&E.F, 2);
        Ar.Serialize(&E.G, 2);
    }
    return Ar;
}
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

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_cc570(TArray<FUnnamedElem_a4770> *A, INT N, INT M) { Escape(&GMalloc); A->Empty(N); A->Empty(M); }
void Driver_cc5b0(TArray<FUnnamedElem_a4780> *A, TArray<FUnnamedElem_a4780> *B) { Escape(&GMalloc); A->~TArray(); B->~TArray(); }
void Driver_cc6c0(TArray<FUnnamedElem_a4780> *A, INT I, INT N) { A->Remove(I, N); }
void Driver_cc620(FUnnamedStruct_cc620 *A, FUnnamedStruct_cc620 *B, FUnnamedStruct_cc620 *C) { *A = *B; *B = *C; *C = *A; *A = *C; *B = *A; *C = *B; }
FArchive *Driver_cc710(FArchive *Ar, TArray<FUnnamedElem_cd1b0> *A, FCompactIndex *I) { Escape(&(*Ar << *I)); return &(*Ar << *A); }
FArchive *Driver_cc820(FArchive *Ar, TArray<FUnnamedElem_a4770> *A) { return &(*Ar << *A); }
