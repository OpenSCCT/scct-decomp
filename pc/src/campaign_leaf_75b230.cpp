// campaign_leaf_75b230.cpp -- one function at file offset 0x75b230, preferred VA 0x1105b230. For
// each 0x68-byte entry of the array at 0x34 of the object at 0xc, counted by the word at 0x4 of
// the object at 0x14, it stores at 0x48 of the entry whether the stdcall function at VA
// 0x11045e40 accepts the entry and the word at 0x40 of the object at 0xc; it then sets the state
// at 0x4 to 0x12. The class, method and member names are invented; the offsets and the callee's
// address are the binary's.

struct UnkType_1105b230_Entry
{
    unsigned char unk_0[0x48];
    int unk_48;
    unsigned char unk_4c[0x68 - 0x4c];
};

struct UnkType_1105b230_Table
{
    unsigned char unk_0[0x34];
    UnkType_1105b230_Entry* unk_34;
    unsigned char unk_38[0x40 - 0x38];
    int unk_40;
};

struct UnkType_1105b230_Count
{
    int unk_0;
    int unk_4;
};

int __stdcall Unk_11045e40(UnkType_1105b230_Entry* Entry, int Value);

class UnkType_1105b230
{
public:
    void Unk_1105b230();

    int unk_0;
    int unk_4;
    unsigned char unk_8[0xc - 0x8];
    UnkType_1105b230_Table* unk_c;
    unsigned char unk_10[0x14 - 0x10];
    UnkType_1105b230_Count* unk_14;
};

// UnkType_1105b230::Unk_1105b230
void UnkType_1105b230::Unk_1105b230()
{
    int Index;

    for ( Index = 0; Index < unk_14->unk_4; Index++ )
    {
        if ( Unk_11045e40(&unk_c->unk_34[Index], unk_c->unk_40) == 0 )
        {
            unk_c->unk_34[Index].unk_48 = 0;
        }
        else
        {
            unk_c->unk_34[Index].unk_48 = 1;
        }
    }
    unk_4 = 0x12;
}
