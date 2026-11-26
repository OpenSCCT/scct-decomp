// campaign_leaf_498020.cpp -- thiscall at VA 0x10d98020: when the method at VA 0x10d97e40 of the
// global object at VA 0x1131a714 returns an object, calls its method at VA 0x10dc2140 with the
// dword at offset 0. All names are invented.

#include "campaign_global_1131a714.h"

class UnkType_10d98020
{
public:
    void Unk_10d98020();

private:
    int unk_00;
};

// UnkType_10d98020::Unk_10d98020
void UnkType_10d98020::Unk_10d98020()
{
    UnkType_1131a714_Item* Object = GUnk_1131a714.Unk_10d97e40();
    if (Object) {
        Object->Unk_10dc2140(unk_00);
    }
}
