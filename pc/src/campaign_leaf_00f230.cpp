// campaign_leaf_00f230.cpp -- method at VA 0x1090f230: when IsWindow accepts the window handle at
// 0x04, passes its three arguments as a message to the window procedure at 0x38 for that window
// through CallWindowProcW when the global at VA 0x112327f8 is set and CallWindowProcA otherwise,
// and returns the result; otherwise returns 1. The class, member and method names are invented;
// the offsets and the address are the binary's.

#include "campaign_global_112327f8.h"
#include "campaign_import_CallWindowProcA.h"
#include "campaign_import_CallWindowProcW.h"
#include "campaign_import_IsWindow.h"

class UnkType_1090f230
{
public:
    long Unk_1090f230(unsigned int Message, unsigned int WParam, long LParam);

private:
    int unk_00;
    HWND unk_04;
    unsigned char unk_08[0x30];
    WNDPROC unk_38;
};

// UnkType_1090f230::Unk_1090f230
long UnkType_1090f230::Unk_1090f230(unsigned int Message, unsigned int WParam, long LParam)
{
    if ( IsWindow(unk_04) )
    {
        if ( GUnk_112327f8 )
        {
            return CallWindowProcW(unk_38, unk_04, Message, WParam, LParam);
        }
        return CallWindowProcA(unk_38, unk_04, Message, WParam, LParam);
    }
    return 1;
}
