// campaign_leaf_76f460.cpp -- one function at file offset 0x76f460, preferred VA 0x1106f460. A
// destructor: it installs the vtable at VA 0x11176d28; for each of the handles at 0x24 and 0x28
// that is not -1 it calls the stdcall functions at VA 0x11094950 and VA 0x110949b0 on it; when the
// word at 0x44 is set it decrements the global counter at VA 0x1132eb38 and clears the word; it
// then runs the base destructor at VA 0x11065040. The class names are invented; the offsets and
// the addresses are the binary's.

#include "campaign_global_1132eb38.h"

void __stdcall Unk_11094950(int Handle);
void __stdcall Unk_110949b0(int Handle);

class UnkType_1106f460_Base
{
public:
    virtual ~UnkType_1106f460_Base();

    unsigned char unk_4[0x24 - 0x4];
};

class UnkType_1106f460 : public UnkType_1106f460_Base
{
public:
    virtual ~UnkType_1106f460();

    int unk_24;
    int unk_28;
    unsigned char unk_2c[0x44 - 0x2c];
    int unk_44;
};

// UnkType_1106f460::~UnkType_1106f460
UnkType_1106f460::~UnkType_1106f460()
{
    if ( unk_24 != -1 )
    {
        Unk_11094950(unk_24);
        Unk_110949b0(unk_24);
    }
    if ( unk_28 != -1 )
    {
        Unk_11094950(unk_28);
        Unk_110949b0(unk_28);
    }
    if ( unk_44 != 0 )
    {
        GUnk_1132eb38--;
        unk_44 = 0;
    }
}
