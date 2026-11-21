// Work item 0134. Neutral names: no symbols or strings identify these classes.

typedef int INT;
typedef float FLOAT;

// 0x90-byte element of the array at owner+0x100 (name unknown).
struct UnnamedEntry_c03c0
{
    char Pad00[0x38];
    INT Active;        // +0x38
    char Pad3C[0x5c - 0x3c];
    FLOAT Value;       // +0x5c
    INT Data;          // +0x60
    char Pad64[0x90 - 0x64];
};

struct UnnamedOwner_c03c0
{
    char Pad000[0x100];
    UnnamedEntry_c03c0 *Entries;  // +0x100
    INT NumEntries;               // +0x104
};

extern FLOAT UnnamedThreshold_c109f8;

void __fastcall SetEntry_c03c0(INT Index, UnnamedOwner_c03c0 *Owner, INT Data, FLOAT Value)
{
    if ((Index >= 0 && Index < Owner->NumEntries) || !(Value >= UnnamedThreshold_c109f8))
    {
        UnnamedEntry_c03c0 *E = &Owner->Entries[Index];
        E->Data = Data;
        E->Value = Value;
        E->Active = 1;
    }
}
