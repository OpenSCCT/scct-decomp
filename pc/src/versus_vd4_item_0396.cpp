// UVertexStreamVECTOR destructor and Serialize from the Steam Versus payload.
// UVertexStreamVECTOR (class size 0x44) derives from UVertexStreamBase, whose
// destructor is published as UnnamedClass3098A0 at 0xa6df0; its vertex array
// (TArray<FVector>) lives at offset 0x38.
enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

class FArchive {
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, int Length);
    virtual void SerializeBits(void *V, int LengthBits);
    virtual void SerializeInt(unsigned long &Value, unsigned long Max);
    virtual void Preload(void *Object);
    virtual void CountBytes(unsigned long InNum, unsigned long InMax);
    int ArVer;
    int ArNetVer;
    int ArLicenseeVer;
    int ArIsLoading;
    int ArIsSaving;
};

class FMalloc {
public:
    virtual void *Malloc(unsigned long Count, const unsigned short *Tag);
    virtual void *Realloc(void *Original, unsigned long Count, const unsigned short *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
extern const unsigned short TArray_SerializeTag[];

struct FCompactIndex { int Value; };
FArchive &operator<<(FArchive &Ar, unsigned char &B) { Ar.Serialize(&B, 1); return Ar; }
struct FVector { float X, Y, Z; };

template<class T> class TArray {
public:
    T *Data;
    int ArrayNum;
    int ArrayMax;
    ~TArray();
    void Realloc(int ElementSize);
};

class UObject {
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    int Index;
    unsigned Reserved[5];
    unsigned ObjectFlags;
    int ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed)) {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            Destroy();
            return 1;
        }
        return 0;
    }
};

class UVertexStreamBase : public UObject {
public:
    virtual ~UVertexStreamBase();
    virtual void Serialize(FArchive &Ar);
    unsigned char BaseData[0x38 - 0x20];
};

class UVertexStreamVECTOR : public UVertexStreamBase {
public:
    virtual ~UVertexStreamVECTOR();
    virtual void Serialize(FArchive &Ar);
    TArray<FVector> Data;
};

// Compact index serializer; matched elsewhere, defined so the link gives it
// retail's register convention (Ar in ESI, the index in EDI).
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.ArIsLoading && !Ar.ArIsSaving) {
        Ar.Serialize(&I.Value, 4);
        return Ar;
    }
    int Original = I.Value;
    unsigned long V = Original < 0 ? -Original : Original;
    unsigned char B0 = (unsigned char)(((Original >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40)));
    I.Value = 0;
    Ar << B0;
    if (B0 & 0x40) {
        V >>= 6;
        unsigned char B1 = (unsigned char)((V < 0x80) ? V : ((V & 0x7f) + 0x80));
        Ar << B1;
        if (B1 & 0x80) {
            V >>= 7;
            unsigned char B2 = (unsigned char)((V < 0x80) ? V : ((V & 0x7f) + 0x80));
            Ar << B2;
            I.Value = (I.Value << 7) + (B2 & 0x7f);
        }
        I.Value = (I.Value << 7) + (B1 & 0x7f);
    }
    I.Value = (I.Value << 6) + (B0 & 0x3f);
    if (B0 & 0x80) I.Value = -I.Value;
    if (Ar.ArIsSaving && I.Value != Original) I.Value = Original;
    return Ar;
}

// Bulk TArray serializer (FUN_10986bb0); retail keeps it out of line with its
// arguments in EAX (archive) and EBX (array).
FArchive &operator<<(FArchive &Ar, TArray<FVector> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(FVector), A.ArrayMax * sizeof(FVector));
    Ar << *(FCompactIndex *)&A.ArrayNum;
    if (Ar.ArIsLoading) {
        A.ArrayMax = A.ArrayNum;
        if (A.Data) {
            if (A.ArrayNum) {
                A.Realloc(sizeof(FVector));
            } else {
                A.ArrayNum = 0;
                A.ArrayMax = 0;
                GMalloc->Free(A.Data);
                A.Data = 0;
                return Ar;
            }
        } else if (A.ArrayNum) {
            A.Data = (FVector *)GMalloc->Malloc(A.ArrayNum * sizeof(FVector), TArray_SerializeTag);
        } else {
            return Ar;
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(FVector));
    return Ar;
}

UVertexStreamVECTOR::~UVertexStreamVECTOR() { ConditionalDestroy(); }

void UVertexStreamVECTOR::Serialize(FArchive &Ar)
{
    UVertexStreamBase::Serialize(Ar);
    Ar << Data;
}

// Scaffolding for the link, not part of the unit.
void Driver_a76d0(UVertexStreamVECTOR *S, FArchive *Ar) { S->Serialize(*Ar); S->UVertexStreamVECTOR::~UVertexStreamVECTOR(); }
