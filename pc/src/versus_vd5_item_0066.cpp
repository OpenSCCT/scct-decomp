// Work item 0066: Versus RVA 0x9cd90, UESBPatch::Serialize (vtable UESBPatch slot 10).
// Link-time optimised (/GL + /LTCG): the archive helpers it calls take the archive
// and the value in registers, so they are defined here (bodies reconstructed from
// retail) so the linker gives them the same custom conventions.
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

class FName { public: INT Index; };

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, INT Length);
    virtual void SerializeBits(void* V, INT LengthBits);
    virtual void SerializeInt(DWORD& Value, DWORD Max);
    virtual void Preload(class UObject* Object);
    virtual void CountBytes(INT InNum, INT InMax);
    // MSVC lays overloaded virtuals out in reverse order of declaration,
    // so this order puts operator<<(FName&) at slot 6 (0x18) as in retail.
    virtual FArchive& operator<<(class UObject*& Res);
    virtual FArchive& operator<<(FName& N);

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    void ByteOrderSerialize(void* V, INT Length) { Serialize(V, Length); }

    friend FArchive& operator<<(FArchive& Ar, BYTE& B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive& operator<<(FArchive& Ar, INT& I) { Ar.ByteOrderSerialize(&I, sizeof(I)); return Ar; }
    friend FArchive& operator<<(FArchive& Ar, DWORD& D) { Ar.ByteOrderSerialize(&D, sizeof(D)); return Ar; }
    friend FArchive& operator<<(FArchive& Ar, FLOAT& F) { Ar.ByteOrderSerialize(&F, sizeof(F)); return Ar; }

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
};

class FCompactIndex { public: INT Value; };
FArchive& operator<<(FArchive& Ar, FCompactIndex& I); // RVA 0x1ea40
#define AR_INDEX(intref) (*(FCompactIndex*)&(intref))

inline void* operator new(unsigned int, void* Mem) { return Mem; }

struct FVector
{
    FLOAT X, Y, Z;
    friend FArchive& operator<<(FArchive& Ar, FVector& V) { return Ar << V.X << V.Y << V.Z; }
};

struct FPlane : public FVector
{
    FLOAT W;
    friend FArchive& operator<<(FArchive& Ar, FPlane& P) { return Ar << P.X << P.Y << P.Z << P.W; }
};

class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);      // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);   // RVA 0x4550
};

template<class T> class TArray : public FArray
{
public:
    T& operator()(INT i) { return ((T*)Data)[i]; }
    INT Num() const { return ArrayNum; }
    void CountBytes(FArchive& Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack = 0) { FArray::Empty(sizeof(T), Slack); }

    friend FArchive& operator<<(FArchive& Ar, TArray& A)
    {
        A.CountBytes(Ar);
        if (Ar.IsLoading())
        {
            INT NewNum;
            Ar << AR_INDEX(NewNum);
            A.Empty(NewNum);
            for (INT i = 0; i < NewNum; i++)
                Ar << *new(&A(A.Add(1, sizeof(T)))) T;
        }
        else
        {
            Ar << AR_INDEX(A.ArrayNum);
            for (INT i = 0; i < A.ArrayNum; i++)
                Ar << A(i);
        }
        return Ar;
    }
};

// Rotation value serialised with a version check (RVA 0x86060).
struct FESBQuat : public FVector
{
    FLOAT W;
};
FArchive& operator<<(FArchive& Ar, FESBQuat& Q)
{
    if (Ar.Ver() <= 0x3d)
        return Ar << Q.X << Q.Y << Q.Z;
    return Ar << Q.X << Q.Y << Q.Z << Q.W;
}

// 0x18-byte transform value (RVA 0x860d0); default is rotation 1, offset 0.
extern FLOAT ESBTransform_Epsilon; // 0x10c109fc
struct FESBTransform
{
    FLOAT A, B, C, D, E, F;
    FESBTransform() : A(1.f), D(0.f) {}
};
FArchive& operator<<(FArchive& Ar, FESBTransform& T)
{
    BYTE Valid = (T.A - T.D) != ESBTransform_Epsilon;
    Ar << T.A << T.B << T.C << T.D << T.E << T.F << Valid;
    if (Ar.IsLoading() && !Valid)
    {
        T.D = 0.f;
        T.A = 1.f;
    }
    return Ar;
}

// 0x48-byte element (RVA 0x9dee0).
struct FESBPatchPoint
{
    FLOAT Weight;
    FVector V[5];
    FLOAT P, Q;
};
FArchive& operator<<(FArchive& Ar, FESBPatchPoint& P)
{
    Ar << P.Weight;
    for (INT i = 0; i < 5; i++)
        Ar << P.V[i];
    return Ar << P.P << P.Q;
}

// 0x10-byte named element.
struct FESBNamedVector
{
    FName Name;
    FVector V;
    friend FArchive& operator<<(FArchive& Ar, FESBNamedVector& N) { return Ar << N.Name << N.V; }
};

class UObject
{
public:
    UObject() {}
    virtual ~UObject();
    virtual void VF1(); virtual void VF2(); virtual void VF3(); virtual void VF4();
    virtual void VF5(); virtual void VF6(); virtual void VF7(); virtual void VF8();
    virtual void VF9();
    virtual void Serialize(FArchive& Ar);     // slot 10, RVA 0x15f50
    virtual void VF11(); virtual void VF12(); virtual void VF13(); virtual void VF14();
    virtual void VF15(); virtual void VF16(); virtual void VF17(); virtual void VF18();
    virtual void VF19(); virtual void VF20(); virtual void VF21(); virtual void VF22();
    virtual void VF23(); virtual void VF24(); virtual void VF25(); virtual void VF26();
    virtual void VF27(); virtual void VF28(); virtual void VF29(); virtual void VF30();
    virtual void VF31(); virtual void VF32(); virtual void VF33();

    INT Index;
    UObject* HashNext;
    void* StateFrame;
    void* _Linker;
    INT _LinkerIndex;
    UObject* Outer;
    DWORD ObjectFlags;
    FName Name;
    class UClass* Class;
};

extern INT UESBPatch_CurrentVersion; // 0x10c4da0c

// Field names are neutral: only their sizes and archive order are known.
class UESBPatch : public UObject
{
public:
    virtual void PostSerialize(FArchive& Ar); // slot 34 (0x88), real name unknown

    FESBTransform Transform;      // 0x28
    FESBQuat Rotation;            // 0x40
    INT Version;                  // 0x50
    FName PatchName;              // 0x54
    FESBTransform Transform2;     // 0x58
    TArray<FESBPatchPoint> Points;      // 0x70
    TArray<FVector> Vectors;            // 0x7c
    TArray<FESBNamedVector> Named;      // 0x88
    TArray<FPlane> Planes;              // 0x94
    TArray<FESBTransform> Transforms;   // 0xa0
    TArray<FPlane> Planes2;             // 0xac
    FVector Vec0;                 // 0xb8
    FVector Vec1;                 // 0xc4
    FVector Vec2;                 // 0xd0
    FLOAT FDC, FE0, FE4, FE8, FEC;      // 0xdc
    FLOAT FF0, FF4;               // 0xf0
    FLOAT FF8, FFC;               // 0xf8
    INT I100, I104;               // 0x100
    FLOAT F108, F10C, F110;       // 0x108
    FLOAT F114, F118;             // 0x114
    BYTE Pad11C[0x134 - 0x11c];
    FLOAT F134, F138;             // 0x134
    FVector Vec3;                 // 0x13c
    FVector Vec4;                 // 0x148
    FLOAT F154;                   // 0x154
    FLOAT F158;                   // 0x158

    UESBPatch();
    void Serialize(FArchive& Ar);
};

// RVA 0x9cd90
void UESBPatch::Serialize(FArchive& Ar)
{
    UObject::Serialize(Ar);
    Ar << Transform << Rotation;
    Ar << I100 << I104;
    Ar << PatchName << Version
       << Points << Vectors << Planes << Named
       << Vec0 << Vec1 << Vec2
       << FDC << FE0 << FE4 << FE8 << FEC << FF8 << F114 << F118 << FFC
       << Transforms << Planes2 << Transform2
       << F108 << F10C << F110;
    if (Version > 1)
        Ar << F134 << F138 << Vec3 << Vec4;
    if (Version > 2)
        Ar << F154;
    if (Version > 3)
        Ar << FF0 << FF4;
    if (Version > 4)
        Ar << F158;
    PostSerialize(Ar);
    if (Ar.IsLoading())
        Version = UESBPatch_CurrentVersion;
}

// Scaffolding for the link, not part of the unit. The FCompactIndex serializer
// (RVA 0x1ea40) lives in Core; it is written out here only so the linker gives
// it retail's register convention (copied from item_0245).
FArchive& operator<<(FArchive& Ar, FCompactIndex& I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving())
    {
        Ar.Serialize(&I.Value, 4);
        return Ar;
    }
    DWORD V = I.Value >= 0 ? I.Value : -I.Value;
    unsigned char B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
    I.Value = 0;
    Ar << B0;
    if (B0 & 0x40)
    {
        V >>= 6;
        unsigned char B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
        Ar << B1;
        if (B1 & 0x80)
        {
            V >>= 7;
            unsigned char B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B2;
            if (B2 & 0x80)
            {
                V >>= 7;
                unsigned char B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B3;
                if (B3 & 0x80)
                {
                    V >>= 7;
                    unsigned char B4 = V;
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
    return Ar;
}
void Escape(void *);
void Driver_9cd90(UESBPatch* P, FArchive* Ar)
{
    Escape(&UESBPatch_CurrentVersion);
    Escape(&ESBTransform_Epsilon);
    P->UESBPatch::Serialize(*Ar);
}
// Emits the vtable, so Serialize keeps the thiscall convention of a virtual.
UESBPatch::UESBPatch() {}
