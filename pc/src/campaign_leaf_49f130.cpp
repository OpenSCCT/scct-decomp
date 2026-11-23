// campaign_leaf_49f130.cpp -- thiscall method at VA 0x10d9f130. It returns a key built from the
// global at 0x1131b2ac (0x10d9d3c0) and this object's key at 0x4 (0x10d9d3a0). The class, method
// and parameter names are invented.

#include "campaign_global_1131b2ac.h"

struct UnkType_10d9f130_Key
{
    UnkType_10d9f130_Key(int Value, UnkType_10d9f130_Key Other) : unk_0(0)
    {
        Unk_10d9d3c0(Value);
        Unk_10d9d3a0(Other);
    }

    UnkType_10d9f130_Key(const UnkType_10d9f130_Key& Other) : unk_0(Other.unk_0) {}
    void Unk_10d9d3c0(int Value);
    void Unk_10d9d3a0(UnkType_10d9f130_Key Other);

    int unk_0;
};

class UnkType_10d9f130
{
public:
    UnkType_10d9f130_Key Unk_10d9f130();

private:
    int unk_0;
    UnkType_10d9f130_Key unk_4;
};

// UnkType_10d9f130::Unk_10d9f130
UnkType_10d9f130_Key UnkType_10d9f130::Unk_10d9f130()
{
    UnkType_10d9f130_Key Key(GUnk_1131b2ac, unk_4);

    return Key;
}
