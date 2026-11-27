// UPalette construction and versioned colour serialization.
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short _WORD;
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef DWORD UBOOL;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArchive {
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(class UObject *Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }
    FArchive &operator<<(BYTE &B) { Serialize(&B, 1); return *this; }
};

struct FCompactIndex { INT Value; };
FArchive &operator<<(FArchive &Ar, FCompactIndex &I); // 0x1ea40, defined in the scaffolding
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Add(INT Count, INT ElementSize);   // 0x44e0
    void Empty(INT ElementSize, INT Slack); // 0x4550
    INT Num() const { return ArrayNum; }
};

struct FColor {
    BYTE B, G, R, A;
};

inline FArchive &operator<<(FArchive &Ar, FColor &C)
{
    return Ar << C.R << C.G << C.B << C.A;
}

inline void *operator new(unsigned int, void *Mem) { return Mem; }

// TArray<FColor> serializer (0xf48e0).
FArchive &operator<<(FArchive &Ar, FArray &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(FColor), A.ArrayMax * sizeof(FColor));
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(sizeof(FColor), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << ((FColor *)A.Data)[A.Add(1, sizeof(FColor))];
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << ((FColor *)A.Data)[i];
    }
    return Ar;
}

class UObject {
public:
    BYTE ObjectPad[0x28 - 4];
    UObject() {}
    virtual ~UObject();
    void Serialize(FArchive &Ar); // 0x15f50
};

class UPalette : public UObject {
public:
    FArray Colors; // 0x28
    INT Field34;   // 0x34
    INT Field38;   // 0x38, serialized from version 163
    UPalette();
    virtual ~UPalette();
    void Serialize(FArchive &Ar);
};

UPalette::UPalette() // 0xf2ee0
    : Field34(0), Field38(0)
{
}

void UPalette::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);
    Ar << Colors;
    if (Ar.Ver() < 66) {
        for (INT i = 0; i < Colors.Num(); i++)
            ((FColor *)Colors.Data)[i].A = 255;
    }
    if (Ar.Ver() >= 163)
        Ar.Serialize(&Field38, 4);
}

// LTCG context for the placement constructor.
void Escape(void *);
void *AllocateObject(INT Kind);
UPalette *Driver_f2ee0(INT Kind)
{
    void *Mem = AllocateObject(Kind);
    UPalette *P = Mem ? new(Mem) UPalette : 0;
    Escape(P);
    Mem = AllocateObject(Kind + 1);
    return Mem ? new(Mem) UPalette : 0;
}
// Compact index serializer (0x1ea40, another unit), so the link gives it its retail registers.
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
        return Ar;
    }
    DWORD V = I.Value >= 0 ? I.Value : -I.Value;
    BYTE B0 = (I.Value >= 0 ? 0 : 0x80) + (V < 0x40 ? V : (V & 0x3f) + 0x40);
    I.Value = 0;
    Ar << B0;
    if (B0 & 0x40) {
        V >>= 6;
        BYTE B1 = V < 0x80 ? V : (V & 0x7f) + 0x80;
        Ar << B1;
        if (B1 & 0x80) {
            V >>= 7;
            BYTE B2 = V < 0x80 ? V : (V & 0x7f) + 0x80;
            Ar << B2;
            if (B2 & 0x80) {
                V >>= 7;
                BYTE B3 = V < 0x80 ? V : (V & 0x7f) + 0x80;
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
    return Ar;
}
