// RVA 0xb6080: adds or updates a 0x44-byte entry, keyed by name, in an array
// held at +0x124 of its owner (at most 256 entries). Neutral names: the owner
// class is not identified yet (UnnamedClass_b6080). Retail is LTCG-compiled:
// `this` arrives in EBX and the five arguments on the stack (ret 0x14).
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

#define INDEX_NONE -1
class FName
{
public:
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
    INT Index;
};
struct FVector { FLOAT X, Y, Z; };

class FArray
{
public:
    INT Add(INT Count, INT ElementSize);   // @add_array@12 at 0x44e0
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

struct FNamedEntry_b6080
{
    INT Index;          // +0x00 result of FindIndex
    FName Name;         // +0x04 key
    FVector A;          // +0x08
    FVector B;          // +0x14
    INT Param;          // +0x20
    FLOAT Value;        // +0x24
    FLOAT Value2;       // +0x28
    unsigned char Pad[0x44 - 0x2c];
};

class UnnamedClass_b6080
{
public:
    INT FindIndex(FName Name);   // 0xb57b0
    UBOOL AddEntry(FName Name, const FVector &A, const FVector &B, FLOAT Value, INT Param);

    unsigned char Pad[0x124];
    FArray Entries;     // +0x124 TArray<FNamedEntry_b6080>
};

UBOOL UnnamedClass_b6080::AddEntry(FName Name, const FVector &A, const FVector &B, FLOAT Value, INT Param)
{
    if (Entries.ArrayNum >= 256)
        return 0;
    INT Index = FindIndex(Name);
    if (Index >= 0)
    {
        INT i = INDEX_NONE;
        for (INT j = 0; j < Entries.ArrayNum; j++)
        {
            if (((FNamedEntry_b6080 *)Entries.Data)[j].Name == Name)
            {
                i = j;
                break;
            }
        }
        if (i < 0)
        {
            i = Entries.ArrayNum;
            Entries.Add(1, sizeof(FNamedEntry_b6080));
            ((FNamedEntry_b6080 *)Entries.Data)[i].Name = Name;
            ((FNamedEntry_b6080 *)Entries.Data)[i].Value2 = 0;
            ((FNamedEntry_b6080 *)Entries.Data)[i].Index = Index;
        }
        ((FNamedEntry_b6080 *)Entries.Data)[i].Param = Param;
        ((FNamedEntry_b6080 *)Entries.Data)[i].Value = Value;
        ((FNamedEntry_b6080 *)Entries.Data)[i].Value2 = Value;
        ((FNamedEntry_b6080 *)Entries.Data)[i].A = A;
        ((FNamedEntry_b6080 *)Entries.Data)[i].B = B;
        return 1;
    }
    return 0;
}

// Scaffolding for the link, not part of the unit. The single retail caller
// (0x124a48) pushes the arguments, then fetches the owner (0xdf4e0) into EBX.
UnnamedClass_b6080 *FindOwner_b6080(INT Key);
void Driver_b6080(INT Key, FName Name, FLOAT V, INT P)
{
    FVector A, B;
    FindOwner_b6080(Key)->AddEntry(Name, A, B, V, P);
}
