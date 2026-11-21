// Work item 0144: Versus RVA 0xc2ff0-0xc3507.
// Built with /GL and linked with /LTCG (custom register conventions).
// 0xc3030 / 0xc31a0: FCoordsQuaternion / FQuaternionCoords (UnSkeletalMesh
// math helpers): FCoords is Origin, XAxis, YAxis, ZAxis (diagonal at 0xc,
// 0x1c, 0x2c), FQuat is X, Y, Z, W.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }
inline FLOAT appInvSqrt(FLOAT F)
{
    FLOAT R = 1.0f;
    R /= appSqrt(F);
    return R;
}

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
};

struct FQuat;
struct FCoords
{
    FVector Origin, XAxis, YAxis, ZAxis;
    FCoords() {}
    FCoords(const FQuat &CQ);
};

struct FQuat
{
    FLOAT X, Y, Z, W;
    FQuat() {}
    FQuat(const FCoords &C);
};

// RVA 0xc3030 (LTCG: coords in ECX, result pointer in EDX).
FQuat::FQuat(const FCoords &C)
{
    FQuat &CQ = *this;
    FLOAT Trace = C.XAxis.X + C.YAxis.Y + C.ZAxis.Z + 1.0f;
    if (Trace > 0.0f)
    {
        FLOAT S = appInvSqrt(Trace) * 0.5f;
        CQ.W = 0.25f / S;
        CQ.X = (C.ZAxis.Y - C.YAxis.Z) * S;
        CQ.Y = (C.XAxis.Z - C.ZAxis.X) * S;
        CQ.Z = (C.YAxis.X - C.XAxis.Y) * S;
    }
    else if (C.XAxis.X > C.YAxis.Y && C.XAxis.X > C.ZAxis.Z)
    {
        FLOAT S = appInvSqrt(C.XAxis.X + 1.0f - C.YAxis.Y - C.ZAxis.Z) * 0.5f;
        CQ.X = 0.5f * S;
        CQ.Y = (C.YAxis.X + C.XAxis.Y) * S;
        CQ.Z = (C.ZAxis.X + C.XAxis.Z) * S;
        CQ.W = (C.ZAxis.Y + C.YAxis.Z) * S;
    }
    else if (C.YAxis.Y > C.ZAxis.Z)
    {
        FLOAT S = appInvSqrt(C.YAxis.Y + 1.0f - C.XAxis.X - C.ZAxis.Z) * 0.5f;
        CQ.X = (C.YAxis.X + C.XAxis.Y) * S;
        CQ.Y = 0.5f * S;
        CQ.Z = (C.ZAxis.Y + C.YAxis.Z) * S;
        CQ.W = (C.ZAxis.X + C.XAxis.Z) * S;
    }
    else
    {
        FLOAT S = appInvSqrt(C.ZAxis.Z + 1.0f - C.XAxis.X - C.YAxis.Y) * 0.5f;
        CQ.X = (C.ZAxis.X + C.XAxis.Z) * S;
        CQ.Y = (C.ZAxis.Y + C.YAxis.Z) * S;
        CQ.Z = 0.5f * S;
        CQ.W = (C.YAxis.X + C.XAxis.Y) * S;
    }
}

// RVA 0xc31a0 (LTCG: quaternion in ECX, result pointer in EAX).
FCoords::FCoords(const FQuat &CQ)
{
    FCoords &Coords = *this;
    FLOAT wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
    x2 = CQ.X + CQ.X; y2 = CQ.Y + CQ.Y; z2 = CQ.Z + CQ.Z;
    xx = CQ.X * x2;   xy = CQ.X * y2;   xz = CQ.X * z2;
    yy = CQ.Y * y2;   yz = CQ.Y * z2;   zz = CQ.Z * z2;
    wx = CQ.W * x2;   wy = CQ.W * y2;   wz = CQ.W * z2;
    Coords.Origin.X = 0.0f;
    Coords.Origin.Y = 0.0f;
    Coords.Origin.Z = 0.0f;
    Coords.XAxis.X = 1.0f - (yy + zz);
    Coords.XAxis.Y = xy - wz;
    Coords.XAxis.Z = xz + wy;
    Coords.YAxis.X = xy + wz;
    Coords.YAxis.Y = 1.0f - (xx + zz);
    Coords.YAxis.Z = yz - wx;
    Coords.ZAxis.X = xz - wy;
    Coords.ZAxis.Y = yz + wx;
    Coords.ZAxis.Z = 1.0f - (xx + yy);
}

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
    virtual FArchive &operator<<(class FName &N);           // +0x1c
    virtual FArchive &operator<<(UObject *&Res);            // +0x18
    virtual INT MapName(class FName *Name);                 // +0x20
    virtual INT MapObject(UObject *Object);                 // +0x24
    virtual INT Tell();                                     // +0x28
    virtual INT TotalSize();                                // +0x2c
    virtual UBOOL AtEnd();                                  // +0x30
    virtual void Flush();                                   // +0x34
    virtual void Precache(INT HintCount);                   // +0x38
    virtual void Seek(INT InPos);                           // +0x3c
    virtual void AttachLazyLoader(class FLazyLoader *LazyLoader);   // +0x40

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B)
    {
        Ar.Serialize(&B, 1);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);
    friend FArchive &operator<<(FArchive &Ar, INT &I)
    {
        Ar.Serialize(&I, sizeof(I));
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, short &S)
    {
        Ar.Serialize(&S, sizeof(S));
        return Ar;
    }
    INT Ver() { return ArVer; }

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
    void Realloc(INT ElementSize);              // 0x4600
};

inline void *operator new(unsigned int, void *Mem) { return Mem; }

template <class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Empty(INT Slack = 0);
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
};

// RVA 0xc2ff0 (LTCG: this in ESI, Slack on the stack).
template <class T> __declspec(noinline) void TArray<T>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~T();
    FArray::Empty(sizeof(T), Slack);
}

// Neutral names: a 40-byte element whose destructor is RVA 0xc39d0 (LTCG,
// this on the stack, exception frame). It holds three array members with
// destructors of their own (0xa7f6a0, 0xc3a30, 0xa8a60 relative to the
// image); they are declared here only so the destructor has their shape.
struct UnnamedMember_a7f6a0 { FArray A; ~UnnamedMember_a7f6a0(); };
struct UnnamedMember_c3a30 { FArray A; ~UnnamedMember_c3a30(); };
struct UnnamedMember_a8a60 { FArray A; ~UnnamedMember_a8a60(); };
struct UnnamedElement_c39d0
{
    DWORD Field0;
    UnnamedMember_a7f6a0 M04;
    UnnamedMember_c3a30 M10;
    UnnamedMember_a8a60 M1C;
};

template class TArray<UnnamedElement_c39d0>;

// The compact index serializer (RVA 0x1ea40, Core, LTCG: archive in ESI,
// index in EDI), from versus_vd2_item_0116.cpp; defined here so the link
// gives its calls the retail convention.
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

// Generic TArray serializer (RVA 0xa5df0 for the 8-byte element below).
template <class T> FArchive &operator<<(FArchive &Ar, TArray<T> &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(&((T *)A.Data)[A.Add(1, sizeof(T))]) T;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

extern const TCHAR TArraySerializeTag[];    // L"operator<<(TArray)"

// RVA 0xc3280 (LTCG: archive in EAX, array in EBX). Four-byte elements are
// serialized as one block.
template <> FArchive &operator<<(FArchive &Ar, TArray<DWORD> &A)
{
    A.CountBytes(Ar);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (A.Data == 0) {
            if (A.ArrayMax == 0)
                return Ar;
            A.Data = GMalloc->Malloc(A.ArrayMax * sizeof(DWORD), TArraySerializeTag);
        } else if (A.ArrayMax) {
            A.Realloc(sizeof(DWORD));
        } else {
            A.ArrayNum = 0;
            A.ArrayMax = 0;
            GMalloc->Free(A.Data);
            A.Data = 0;
            return Ar;
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(DWORD));
    return Ar;
}

// Neutral name: the 8-byte lazy-array element (an INT and two words).
struct UnnamedLazyElement
{
    INT A;
    short B, C;
    friend FArchive &operator<<(FArchive &Ar, UnnamedLazyElement &E) { return Ar << E.A << E.B << E.C; }
};

class FLazyLoader
{
public:
    FArchive *SavedAr;
    INT SavedPos;
    virtual void Load() = 0;
    virtual void Unload() = 0;
};

extern DWORD GUglyHackFlags;
extern UBOOL GLazyLoad;

template <class T> class TLazyArray : public TArray<T>, public FLazyLoader
{
public:
    void Load()
    {
        if (SavedPos > 0) {
            INT PushedPos = SavedAr->Tell();
            SavedAr->Seek(SavedPos);
            *SavedAr << (TArray<T> &)*this;
            SavedPos *= -1;
            SavedAr->Seek(PushedPos);
        }
    }
    void Unload();
    friend FArchive &operator<<(FArchive &Ar, TLazyArray &This);
};

// RVA 0xc3320 (LTCG: archive in ECX, array in EAX). UnTemplate.h's
// TLazyArray serializer with the Versus additions for version 175.
// Near miss: the link passes the TArray to the generic serializer (0xa5df0)
// on the stack instead of in EBX, which shifts registers and the frame.
FArchive &operator<<(FArchive &Ar, TLazyArray<UnnamedLazyElement> &This)
{
    if (Ar.IsLoading()) {
        INT SeekPos = 0;
        if (Ar.Ver() <= 61) {
            Ar.AttachLazyLoader(&This);
            INT SkipCount;
            Ar << AR_INDEX(SkipCount);
            SeekPos = Ar.Tell() + SkipCount * sizeof(UnnamedLazyElement);
            return Ar;
        }
        if (Ar.Ver() >= 175) {
            INT Skip;
            Ar << Skip;
            Ar << (TArray<UnnamedLazyElement> &)This;
            return Ar;
        }
        Ar << SeekPos;
        if (GUglyHackFlags & 8)
            Ar << (TArray<UnnamedLazyElement> &)This;
        else
            Ar.AttachLazyLoader(&This);
        if (!GLazyLoad)
            This.Load();
        Ar.Seek(SeekPos);
    } else if (Ar.IsSaving() && Ar.Ver() > 61) {
        if (Ar.Ver() >= 175) {
            INT Zero = 0;
            Ar << Zero;
            Ar << (TArray<UnnamedLazyElement> &)This;
            return Ar;
        }
        INT CountPos = Ar.Tell();
        Ar << CountPos << (TArray<UnnamedLazyElement> &)This;
        INT EndPos = Ar.Tell();
        Ar.Seek(CountPos);
        Ar << EndPos;
        Ar.Seek(EndPos);
    } else {
        Ar << (TArray<UnnamedLazyElement> &)This;
    }
    return Ar;
}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_c3030(FQuat *Out, const FCoords *C) { new(Out) FQuat(*C); }
void Driver_c31a0(FCoords *Out, const FQuat *Q) { new(Out) FCoords(*Q); }
void Driver_c2ff0(TArray<UnnamedElement_c39d0> *A, INT Slack, UnnamedElement_c39d0 *E) { A->Empty(Slack); E->~UnnamedElement_c39d0(); }
void Driver_c3280(FArchive *Ar, TArray<DWORD> *A) { Escape(&GMalloc); *Ar << *A; }
void Driver_c3320(FArchive *Ar, TLazyArray<UnnamedLazyElement> *L, TArray<UnnamedLazyElement> *T)
{
    Escape(&GUglyHackFlags); Escape(&GLazyLoad);
    *Ar << *L;
    Escape(new(T) TLazyArray<UnnamedLazyElement>);
}
