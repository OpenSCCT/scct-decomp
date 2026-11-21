// Work item 0235 (RVA 0x57950-0x57a71): two archive serializers for small
// structs that hold FNames. Built with /GL and linked with /LTCG:
// 0x57950 takes the archive in EAX and the struct in EBX; 0x57a00 takes the
// archive in ESI and the struct in EDI. Both return the archive in EAX.
// The struct names are not recovered (neutral names after their RVAs).
// The compact index serializer (0x1ea40) takes the archive in ESI and the
// index in EDI; its body is taken from item 0116.
typedef unsigned short TCHAR;
typedef int INT;
typedef short SWORD;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

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
    // MSVC lays overloaded virtuals out in reverse order.
    virtual FArchive &operator<<(class FName &N);           // +0x1c
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
        Ar.Serialize(&I, sizeof(I));
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

struct FNameEntry
{
    INT Index;
    DWORD Flags;
};

template <class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    T &operator()(INT i) { return Data[i]; }
};

// Name flag set on names written by a saving archive (value from retail).
#define NAME_FLAG_SAVED 0x20000000

class FName
{
public:
    INT Index;
    static TArray<FNameEntry *> Names;   // 0x10cc9e5c
    void SetFlags(DWORD Set) const { Names(Index)->Flags |= Set; }
};

// RVA 0x1ea40 (not part of this item; defined for its register convention).
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

struct UnnamedStruct_57950
{
    SWORD A;        // 0x00, compact index
    SWORD B;        // 0x02, compact index
    SWORD C;        // 0x04
    FName Name;     // 0x08
    INT D;          // 0x0c
    INT E;          // 0x10, compact index, present when F is non-zero
    INT Unused14;   // 0x14
    INT F;          // 0x18, compact index

    friend FArchive &operator<<(FArchive &Ar, UnnamedStruct_57950 &S);
};

// RVA 0x57950.
FArchive &operator<<(FArchive &Ar, UnnamedStruct_57950 &S)
{
    INT Temp;
    Temp = S.A; Ar << AR_INDEX(Temp); S.A = (SWORD)Temp;
    Temp = S.B; Ar << AR_INDEX(Temp); S.B = (SWORD)Temp;
    Temp = S.C; Ar << Temp; S.C = (SWORD)Temp;
    Ar << S.Name;
    Ar << S.D;
    Ar << AR_INDEX(S.F);
    if (S.F)
        Ar << AR_INDEX(S.E);
    if (Ar.IsSaving())
        S.Name.SetFlags(NAME_FLAG_SAVED);
    return Ar;
}

struct UnnamedStruct_57a00
{
    FName Name0;    // 0x00
    FName Name4;    // 0x04
    SWORD W8;       // 0x08
    SWORD WA;       // 0x0a, reset on load
    FName NameC;    // 0x0c
    INT D10;        // 0x10, reset on load

    friend FArchive &operator<<(FArchive &Ar, UnnamedStruct_57a00 &S);
};

// RVA 0x57a00.
FArchive &operator<<(FArchive &Ar, UnnamedStruct_57a00 &S)
{
    Ar << S.Name0 << S.Name4;
    INT Temp = S.W8;
    Ar << Temp;
    S.W8 = (SWORD)Temp;
    Ar << S.NameC;
    if (Ar.IsLoading()) {
        S.WA = -1;
        S.D10 = 0;
    }
    if (Ar.IsSaving())
        S.NameC.SetFlags(NAME_FLAG_SAVED);
    return Ar;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_57950(FArchive *Ar, UnnamedStruct_57950 *S, UnnamedStruct_57a00 *T, FCompactIndex *I)
{
    Escape(&FName::Names);
    Escape(&(*Ar << *S));
    Escape(&(*Ar << *T));
    Escape(&(*Ar << *I));
}
