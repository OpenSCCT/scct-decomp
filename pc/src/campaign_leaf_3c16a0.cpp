// campaign_leaf_3c16a0.cpp -- one function at file offset 0x3c16a0, preferred VA 0x10cc16a0. It
// takes the window at 0x4 of the object at 0x1f0 and, through SetWindowPos, puts it topmost when
// its menu's item 0x8031 is checked and not topmost otherwise, without moving, sizing or
// activating it. The class, method and member names are invented; the imports and their
// constants are named by the Win32 headers, and the offsets and the bytes are the binary's.

#include "campaign_import_GetMenu.h"
#include "campaign_import_GetMenuState.h"
#include "campaign_import_SetWindowPos.h"

class UnkType_10cc16a0_Window
{
public:
    int unk_0;
    HWND unk_4;
};

class UnkType_10cc16a0
{
public:
    void Unk_10cc16a0();

    unsigned char unk_0[0x1f0];
    UnkType_10cc16a0_Window* unk_1f0;
};

// UnkType_10cc16a0::Unk_10cc16a0
void UnkType_10cc16a0::Unk_10cc16a0()
{
    HWND InsertAfter = HWND_NOTOPMOST;

    if ( GetMenu(unk_1f0->unk_4) != 0
        && (GetMenuState(GetMenu(unk_1f0->unk_4), 0x8031, MF_BYCOMMAND) & MF_CHECKED) )
    {
        InsertAfter = HWND_TOPMOST;
    }
    SetWindowPos(unk_1f0->unk_4, InsertAfter, 0, 0, 0, 0,
        SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
}
