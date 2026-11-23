// campaign_leaf_47d980.cpp -- function at VA 0x10d7d980. It returns a key built from the global
// at 0x1131a698 (0x10d9d3c0) and the given key (0x10d9d3a0). The class, function and parameter
// names are invented.

#include "campaign_global_1131a698.h"

struct UnkType_10d7d980_Key
{
    UnkType_10d7d980_Key(int Value, UnkType_10d7d980_Key Other) : unk_0(0)
    {
        Unk_10d9d3c0(Value);
        Unk_10d9d3a0(Other);
    }

    UnkType_10d7d980_Key(const UnkType_10d7d980_Key& Other) : unk_0(Other.unk_0) {}
    void Unk_10d9d3c0(int Value);
    void Unk_10d9d3a0(UnkType_10d7d980_Key Other);

    int unk_0;
};

// Unk_10d7d980
UnkType_10d7d980_Key Unk_10d7d980(UnkType_10d7d980_Key Id)
{
    UnkType_10d7d980_Key Key(GUnk_1131a698, Id);

    return Key;
}
