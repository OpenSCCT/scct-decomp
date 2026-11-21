// Work item 0138: RVA 0x3d9d0, LTCG serializer for an unnamed struct
// holding an object reference followed by a 4-byte integer.
typedef int INT;
class UObject;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(unsigned long &Value, unsigned long Max);
    virtual void Preload(UObject *Object);
    virtual void CountBytes(INT InNum, INT InMax);
    // MSVC lays overloaded virtuals out in reverse declaration order, so
    // operator<<(FName&) lands in slot 6 and operator<<(UObject*&) in slot 7.
    virtual FArchive &operator<<(UObject *&Res);
    virtual FArchive &operator<<(class FName &N);

    friend FArchive &operator<<(FArchive &Ar, INT &I)
    {
        Ar.Serialize(&I, sizeof(I));
        return Ar;
    }
};

// Neutral name: no evidence for the struct's real name.
struct FUnnamedStruct_3d9d0
{
    UObject *Object;
    INT Value;
};

__declspec(noinline) FArchive &operator<<(FArchive &Ar, FUnnamedStruct_3d9d0 &S)
{
    Ar << S.Object;
    Ar << S.Value;
    return Ar;
}

// Scaffolding for the link, not part of the unit.
void Driver_3d9d0(FArchive *Ar, FUnnamedStruct_3d9d0 *S, INT N)
{
    for (INT i = 0; i < N; i++)
        *Ar << S[i];
}
