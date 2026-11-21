// Work item 0002: FArchive helpers (Unreal Engine 2 Core).
// Layout and vtable order follow UE2's FArchive: vtable[1] Serialize,
// vtable[10] Tell, vtable[11] TotalSize, ArIsLoading at +0x10.

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum { INDEX_NONE = -1 };

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, INT Length);
    virtual void SerializeBits(void* V, INT LengthBits);
    virtual void SerializeInt(DWORD& Value, DWORD Max);
    virtual void Preload(void* Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual void SerializeName(void* N);
    virtual void SerializeObject(void* Res);
    virtual INT MapName(void* Name);
    virtual INT MapObject(void* Object);
    virtual INT Tell();
    virtual INT TotalSize();
    virtual UBOOL AtEnd();

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
};

// RVA 0x4310: FArchive::SerializeBits
void FArchive::SerializeBits(void* V, INT LengthBits)
{
    Serialize(V, (LengthBits + 7) / 8);
    if (ArIsLoading)
        ((BYTE*)V)[LengthBits / 8] &= ((1 << (LengthBits & 7)) - 1);
}

// RVA 0x4390: FArchive::AtEnd
UBOOL FArchive::AtEnd()
{
    INT Pos = Tell();
    return Pos != INDEX_NONE && Pos >= TotalSize();
}

// RVA 0x43c0: an FArchive subclass whose AtEnd compares Tell() with a cached
// size at +0x3c. Class and member names are neutral guesses.
class FArchiveSized_43c0 : public FArchive
{
public:
    UBOOL AtEnd();
    BYTE Pad14[0x3c - 0x14];
    INT Size;
};

UBOOL FArchiveSized_43c0::AtEnd()
{
    INT Pos = Tell();
    return Pos != INDEX_NONE && Size != INDEX_NONE && Pos >= Size;
}
