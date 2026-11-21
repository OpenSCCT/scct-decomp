// Work item 0101: RVA 0xaf4e0, LTCG serializer for an unnamed record
// (three FVectors, an FColor and three floats). Names are neutral where
// the evidence does not identify the class.
typedef int INT;
typedef unsigned char BYTE;
typedef float FLOAT;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
};

inline FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.Serialize(&F, 4); return Ar; }
inline FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }

struct FVector
{
    FLOAT X, Y, Z;
};
inline FArchive &operator<<(FArchive &Ar, FVector &V) { return Ar << V.X << V.Y << V.Z; }

struct FColor
{
    BYTE B, G, R, A;
};
inline FArchive &operator<<(FArchive &Ar, FColor &C) { return Ar << C.R << C.G << C.B << C.A; }

struct UnnamedRecord_af4e0;
// Object whose virtual slot 6 hands out the archive to write the record through.
class UnnamedArchiveOwner_af4e0
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual FArchive &GetArchive(UnnamedRecord_af4e0 *Record);
};

struct UnnamedRecord_af4e0
{
    INT Header;
    FVector A;      // 0x04
    FVector B;      // 0x10
    FVector C;      // 0x1c
    FColor Color;   // 0x28
    FLOAT F0;       // 0x2c
    FLOAT F1;       // 0x30
    FLOAT F2;       // 0x34
};

UnnamedArchiveOwner_af4e0 &operator<<(UnnamedArchiveOwner_af4e0 &Owner, UnnamedRecord_af4e0 &R)
{
    Owner.GetArchive(&R) << R.C << R.B << R.A << R.Color << R.F0 << R.F1 << R.F2;
    return Owner;
}

// Scaffolding for the link, not part of the unit.
void Driver_af4e0(UnnamedArchiveOwner_af4e0 *O, UnnamedRecord_af4e0 *R) { *O << *R; }
