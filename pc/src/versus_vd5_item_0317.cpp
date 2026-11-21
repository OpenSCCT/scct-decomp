// Work item 0317: Versus RVA 0x10a1b0-0x10a2a4.
// Three link-time-optimised (/GL, /LTCG) helpers: an archive serializer for a
// pair of 16-bit indices, and two constructors. Class names are neutral:
// nothing in the binary names them.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short _WORD;
typedef short SWORD;
typedef unsigned char BYTE;

class UObject;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(UObject *Object);
    virtual void CountBytes(INT InNum, INT InMax);
    virtual FArchive &operator<<(UObject *&Res);

    INT Ver() { return ArVer; }

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
};

struct FCompactIndex
{
    INT Value;
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

inline INT Abs(INT A) { return A >= 0 ? A : -A; }

// RVA 0x1ea40 (not part of this item; defined so the linker gives it the
// retail register convention: Ar in ESI, I in EDI).
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.ArIsLoading && !Ar.ArIsSaving)
    {
        Ar.Serialize(&I.Value, sizeof(I.Value));
        return Ar;
    }
    INT Original = I.Value;
    DWORD V = Abs(I.Value);
    BYTE B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
    I.Value = 0;
    Ar << B0;
    if (B0 & 0x40)
    {
        V >>= 6;
        BYTE B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
        Ar << B1;
        if (B1 & 0x80)
        {
            V >>= 7;
            BYTE B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B2;
            if (B2 & 0x80)
            {
                V >>= 7;
                BYTE B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B3;
                if (B3 & 0x80)
                {
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

// Unnamed pair of 16-bit indices serialized at 0x10a1b0 (neutral name).
struct UnnamedIndexPair_10a1b0
{
    _WORD A;
    SWORD B;
};

// RVA 0x10a1b0. Ar in EAX, P in EBX.
FArchive &operator<<(FArchive &Ar, UnnamedIndexPair_10a1b0 &P)
{
    // One index temporary is reused; the third index is read and discarded.
    INT Index = P.A;
    Ar << AR_INDEX(Index);
    P.A = (_WORD)Index;
    Index = P.B;
    Ar << AR_INDEX(Index);
    P.B = (SWORD)Index;
    Ar << AR_INDEX(Index);
    if (Ar.Ver() <= 154)
    {
        BYTE Deprecated[8];
        Ar.Serialize(Deprecated, 8);
    }
    return Ar;
}

// Unnamed class constructed at 0x10a250 (vtable 0x10c03b58; neutral name).
// Near miss: the fields sit in a non-polymorphic base (vtable pointer first,
// base fields after it); retail stores the vtable pointer earlier.
extern unsigned __int64 UnnamedClass_10a250_NextId; // 0x10c96930

#pragma pack(push, 4)
#pragma pack(push, 4)
struct UnnamedBase_10a250
{
    UnnamedBase_10a250()
    {
        unsigned __int64 Next = UnnamedClass_10a250_NextId;
        A = 0;
        B = 0;
        C = 0;
        D = 0;
        Id = Next * 256 + 0xe1;
        UnnamedClass_10a250_NextId = Next + 1;
    }
    INT A;               // +04
    INT B;               // +08
    INT C;               // +0c
    unsigned __int64 Id; // +10
    INT D;               // +18
};
#pragma pack(pop)
class UnnamedClass_10a250 : public UnnamedBase_10a250
{
public:
    UnnamedClass_10a250();
    virtual void Slot0();
};

// Three zero-initialised values (neutral name).
struct UnnamedTriple_10a220
{
    UnnamedTriple_10a220() : X(0), Y(0), Z(0) {}
    INT X;
    INT Y;
    INT Z;
};

// Pair of indices defaulting to INDEX_NONE (neutral name).
struct UnnamedIndexRange_10a220
{
    UnnamedIndexRange_10a220() : First(-1), Last(-1) {}
    INT First;
    INT Last;
};

// Unnamed struct constructed at 0x10a220 (neutral name); holds the class
// above as its first member.
struct UnnamedStruct_10a220
{
    UnnamedStruct_10a220();

    UnnamedClass_10a250 Inner; // +00
    UnnamedTriple_10a220 Triple;    // +1c
    UnnamedIndexRange_10a220 Range; // +28
    INT J;                     // +30
    INT K;                     // +34
};
#pragma pack(pop)

// RVA 0x10a250. this in ESI.
__declspec(noinline) UnnamedClass_10a250::UnnamedClass_10a250()
{
}

// RVA 0x10a220. this in EAX.
__declspec(noinline) UnnamedStruct_10a220::UnnamedStruct_10a220()
{
    J = 0;
    K = 0;
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }
FArchive &Driver_10a1b0(FArchive *Ar, UnnamedIndexPair_10a1b0 *P)
{
    *Ar << P[0];
    *Ar << P[1];
    return *Ar << P[2];
}
void Driver_10a220(void **Mem)
{
    Escape(&UnnamedClass_10a250_NextId);
    for (INT i = 0; i < 16; i++)
        Mem[i] = new (Mem[i]) UnnamedStruct_10a220;
    new (Mem[20]) UnnamedStruct_10a220;
    new (Mem[21]) UnnamedStruct_10a220;
    new (Mem[22]) UnnamedStruct_10a220;
    new (Mem[23]) UnnamedStruct_10a220;
    new (Mem[24]) UnnamedStruct_10a220;
    new (Mem[25]) UnnamedStruct_10a220;
}
void Driver_10a250(void **Mem)
{
    new (Mem[0]) UnnamedClass_10a250;
    new (Mem[1]) UnnamedClass_10a250;
    new (Mem[2]) UnnamedClass_10a250;
    new (Mem[3]) UnnamedClass_10a250;
    new (Mem[4]) UnnamedClass_10a250;
    new (Mem[5]) UnnamedClass_10a250;
    new (Mem[6]) UnnamedClass_10a250;
    new (Mem[7]) UnnamedClass_10a250;
}
