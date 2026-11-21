// Work item w3_0022: UStructProperty::NetSerializeItem (RVA 0x567e0), UE2 UnProp.cpp.
// The object was built with /GL and linked with /LTCG. Retail expands the
// rounding inline (floor(x + 0.5)) in the Vector and Plane cases but calls
// appRound (0xf4d0) in the CompressedPosition case, so those cases are written
// with appFloor(x + 0.5f) and appRound is kept out of line. appCeilLogTwo
// (0x12050) gets its argument in EDX and TFieldIterator<UProperty> (0x1f260,
// 0x1f850) gets register conventions from the linker.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef short SWORD;
typedef float FLOAT;

extern "C" __declspec(dllimport) double __cdecl floor(double);

enum EName
{
    NAME_Vector             = 0x57,
    NAME_Rotator            = 0x58,
    NAME_Plane              = 0x5b,
    NAME_CompressedPosition = 0x5d,
};
enum { INDEX_NONE = -1 };
enum { CLASS_IsAUProperty = 0x8000 };

inline INT appFloor(FLOAT F) { return (INT)floor(F); }
// 0xf4d0
__declspec(noinline) INT appRound(FLOAT F) { return appFloor(F + 0.5f); }

// 0x12050: appCeilLogTwo. Retail keeps it out of line; the linker passes
// its argument in EDX.
extern const BYTE CeilLogTable_12050[256];
__declspec(noinline) BYTE appCeilLogTwo(DWORD Arg)
{
    if (--Arg == (DWORD)-1)
        return 0;
    BYTE Shift = Arg <= 0x10000 ? (Arg <= 0x100 ? 0 : 8) : (Arg <= 0x1000000 ? 16 : 24);
    return Shift + CeilLogTable_12050[Arg >> Shift];
}

template<class T> inline T Abs(const T A) { return (A >= (T)0) ? A : -A; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
template<class T> inline T Clamp(const T X, const T Min, const T Max) { return X < Min ? Min : X < Max ? X : Max; }

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
};
struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
};
struct FRotator
{
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
};
struct FCompressedPosition
{
    FVector Location;
    FRotator Rotation;
    FVector Velocity;
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;                                      // +0x10
    UBOOL IsLoading() { return ArIsLoading; }
};
inline FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
inline FArchive &operator<<(FArchive &Ar, SWORD &S) { Ar.Serialize(&S, 2); return Ar; }

class UClass;
class UStruct;
class UPackageMap;

class UObject
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24();
    BYTE Pad04[0x20 - 0x04];
    INT Name;               // +0x20 (FName index)
    UClass *Class;          // +0x24
    INT GetFName() const { return Name; }
};
class UField : public UObject
{
public:
    UField *SuperField;     // +0x28
    UField *Next;           // +0x2c
};
class UStruct : public UField
{
public:
    UField *Children;       // +0x30
    UStruct *GetInheritanceSuper();
};
class UClass : public UStruct
{
public:
    BYTE Pad34[0x88 - 0x34];
    DWORD ClassFlags;       // +0x88
};

class UPackageMap : public UObject
{
public:
    virtual INT ObjectToIndex(UObject *Object);             // +0x64
};

class UProperty : public UField
{
public:
    SWORD ArrayDim;         // +0x30
    SWORD ElementSize;      // +0x32
    DWORD PropertyFlags;    // +0x34
    INT Pad38;
    INT Offset;             // +0x3c
    virtual void V25(); virtual void V26(); virtual void V27(); virtual void V28();
    virtual void V29(); virtual void V30();
    virtual UBOOL NetSerializeItem(FArchive &Ar, UPackageMap *Map, void *Data) const; // +0x7c
};

class UStructProperty : public UProperty
{
public:
    BYTE Pad40[0x58 - 0x40];
    UStruct *Struct;        // +0x58
    UBOOL NetSerializeItem(FArchive &Ar, UPackageMap *Map, void *Data) const;
};

class TFieldIterator_UProperty
{
public:
    UStruct *Struct;
    UField *Field;
    TFieldIterator_UProperty(UStruct *InStruct);
    void IterateToNext();
    operator UBOOL() { return Field != 0; }
    UProperty *operator*() { return (UProperty *)Field; }
    UProperty *operator->() { return (UProperty *)Field; }
    void operator++() { Field = Field->Next; IterateToNext(); }
};

// 0x1f260
TFieldIterator_UProperty::TFieldIterator_UProperty(UStruct *InStruct)
    : Struct(InStruct), Field(InStruct ? InStruct->Children : 0)
{
    IterateToNext();
}

// 0x1f850
void TFieldIterator_UProperty::IterateToNext()
{
    while (Struct) {
        while (Field) {
            if (Field->Class->ClassFlags & CLASS_IsAUProperty)
                return;
            Field = Field->Next;
        }
        Struct = Struct->GetInheritanceSuper();
        if (Struct)
            Field = Struct->Children;
    }
}

// 0x567e0
UBOOL UStructProperty::NetSerializeItem(FArchive &Ar, UPackageMap *Map, void *Data) const
{
    if (Struct->GetFName() == NAME_Vector)
    {
        FVector &V = *(FVector *)Data;
        INT X(appFloor(V.X + 0.5f)), Y(appFloor(V.Y + 0.5f)), Z(appFloor(V.Z + 0.5f));
        DWORD Bits = Clamp<DWORD>(appCeilLogTwo(1 + Max(Max(Abs(X), Abs(Y)), Abs(Z))), 1, 20) - 1;
        Ar.SerializeInt(Bits, 20);
        INT Bias = 1 << (Bits + 1);
        DWORD Max = 1 << (Bits + 2);
        DWORD DX(X + Bias), DY(Y + Bias), DZ(Z + Bias);
        Ar.SerializeInt(DX, Max);
        Ar.SerializeInt(DY, Max);
        Ar.SerializeInt(DZ, Max);
        if (Ar.IsLoading())
            V = FVector((INT)DX - Bias, (INT)DY - Bias, (INT)DZ - Bias);
    }
    else if (Struct->GetFName() == NAME_Rotator)
    {
        FRotator &R = *(FRotator *)Data;
        BYTE Pitch(R.Pitch >> 8), Yaw(R.Yaw >> 8), Roll(R.Roll >> 8), B;
        B = (Pitch != 0);
        Ar.SerializeBits(&B, 1);
        if (B)
            Ar << Pitch;
        else
            Pitch = 0;
        B = (Yaw != 0);
        Ar.SerializeBits(&B, 1);
        if (B)
            Ar << Yaw;
        else
            Yaw = 0;
        B = (Roll != 0);
        Ar.SerializeBits(&B, 1);
        if (B)
            Ar << Roll;
        else
            Roll = 0;
        if (Ar.IsLoading())
            R = FRotator(Pitch << 8, Yaw << 8, Roll << 8);
    }
    else if (Struct->GetFName() == NAME_Plane)
    {
        FPlane &P = *(FPlane *)Data;
        SWORD X(appFloor(P.X + 0.5f)), Y(appFloor(P.Y + 0.5f)), Z(appFloor(P.Z + 0.5f)), W(appFloor(P.W + 0.5f));
        Ar << X << Y << Z << W;
        if (Ar.IsLoading())
            P = FPlane(X, Y, Z, W);
    }
    else if (Struct->GetFName() == NAME_CompressedPosition)
    {
        FCompressedPosition &C = *(FCompressedPosition *)Data;
        INT VX(appRound(C.Velocity.X)), VY(appRound(C.Velocity.Y)), VZ(appRound(C.Velocity.Z));
        DWORD VBits = Clamp<DWORD>(appCeilLogTwo(1 + Max(Max(Abs(VX), Abs(VY)), Abs(VZ))), 1, 20) - 1;
        INT X(appRound(C.Location.X)), Y(appRound(C.Location.Y)), Z(appRound(C.Location.Z));
        DWORD Bits = Clamp<DWORD>(appCeilLogTwo(1 + Max(Max(Abs(X), Abs(Y)), Abs(Z))), 1, 20) - 1;
        Ar.SerializeInt(Bits, 20);
        INT Bias = 1 << (Bits + 1);
        DWORD Max = 1 << (Bits + 2);
        DWORD DX(X + Bias), DY(Y + Bias), DZ(Z + Bias);
        Ar.SerializeInt(DX, Max);
        Ar.SerializeInt(DY, Max);
        Ar.SerializeInt(DZ, Max);
        if (Ar.IsLoading())
            C.Location = FVector((INT)DX - Bias, (INT)DY - Bias, (INT)DZ - Bias);
        BYTE Pitch(C.Rotation.Pitch >> 8), Yaw(C.Rotation.Yaw >> 8);
        Ar << Pitch << Yaw;
        if (Ar.IsLoading())
            C.Rotation = FRotator(Pitch << 8, Yaw << 8, 0);
        Ar.SerializeInt(VBits, 20);
        Bias = 1 << (VBits + 1);
        Max = 1 << (VBits + 2);
        DX = VX + Bias; DY = VY + Bias; DZ = VZ + Bias;
        Ar.SerializeInt(DX, Max);
        Ar.SerializeInt(DY, Max);
        Ar.SerializeInt(DZ, Max);
        if (Ar.IsLoading())
            C.Velocity = FVector((INT)DX - Bias, (INT)DY - Bias, (INT)DZ - Bias);
    }
    else
    {
        for (TFieldIterator_UProperty It(Struct); It; ++It)
            if (Map->ObjectToIndex(*It) != INDEX_NONE)
                for (INT i = 0; i < It->ArrayDim; i++)
                    It->NetSerializeItem(Ar, Map, (BYTE *)Data + It->Offset + i * It->ElementSize);
    }
    return 1;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_567e0(void *Mem)
{
    // Emits the vtable so the function keeps its virtual (thiscall) form.
    Escape(new (Mem) UStructProperty);
}
