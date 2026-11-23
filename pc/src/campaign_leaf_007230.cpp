// campaign_leaf_007230.cpp -- method at VA 0x10907230: deletes the GDI object at 0x0c with
// DeleteObject when it is set, stores there what the free function at VA 0x10d079a0 returns for its
// argument, this object and the member at 0x04, and returns whether that is set. The class, member
// and function names are invented; the offsets and the address are the binary's.

#include "campaign_import_DeleteObject.h"

class UnkType_10907230;

class UnkType_10907230_04
{
public:
    int unk_00;
    int unk_04;
};

HGDIOBJ Unk_10d079a0(int Value, UnkType_10907230* Object, UnkType_10907230_04* Member);

class UnkType_10907230
{
public:
    int Unk_10907230(int Value);

private:
    int unk_00;
    UnkType_10907230_04 unk_04;
    HGDIOBJ unk_0c;
};

// UnkType_10907230::Unk_10907230
int UnkType_10907230::Unk_10907230(int Value)
{
    if ( unk_0c )
    {
        DeleteObject(unk_0c);
    }
    unk_0c = Unk_10d079a0(Value, this, &unk_04);
    return unk_0c != 0;
}
