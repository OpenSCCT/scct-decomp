// campaign_leaf_010ea0.cpp -- method at VA 0x10910ea0: sends message 0x0b to the window at 0x04
// with its argument as the first parameter and 0 as the second, through SendMessageW when the
// global at VA 0x112327f8 is set and SendMessageA otherwise. The class, member and method names are
// invented; the offset, the constant and the address are the binary's.

#include "campaign_global_112327f8.h"
#include "campaign_import_SendMessageA.h"
#include "campaign_import_SendMessageW.h"

class UnkType_10910ea0
{
public:
    void Unk_10910ea0(unsigned int Value);

private:
    int unk_00;
    HWND unk_04;
};

// UnkType_10910ea0::Unk_10910ea0
void UnkType_10910ea0::Unk_10910ea0(unsigned int Value)
{
    if ( GUnk_112327f8 )
    {
        SendMessageW(unk_04, 0x0b, Value, 0);
    }
    else
    {
        SendMessageA(unk_04, 0x0b, Value, 0);
    }
}
