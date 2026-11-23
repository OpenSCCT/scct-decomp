// campaign_leaf_2645c0.cpp -- a member function at VA 0x10b645c0: it passes the object the
// pointer at 0x38 refers to with "L_Title", "B_Controls", "B_Display" and "B_Sounds", each with a
// section, key and package of localized text and 1, to the free function at VA 0x10b721a0, and
// with the globals at VA 0x1122e428 and 0x1122e42c likewise to the free function at VA 0x10b71f10.
// guess: sets the localized text of the settings menu. The class, method, member, parameter and
// global names are invented; the offsets, addresses and strings are the binary's.

#include "campaign_global_1122e428.h"
#include "campaign_global_1122e42c.h"

class UnkType_10b645c0_Page;

void __cdecl Unk_10b71f10(UnkType_10b645c0_Page* Page, int Name, const unsigned short* Section,
                          const unsigned short* Key, const unsigned short* Package, int Flags);
void __cdecl Unk_10b721a0(UnkType_10b645c0_Page* Page, const char* Name,
                          const unsigned short* Section, const unsigned short* Key,
                          const unsigned short* Package, int Flags);

class UnkType_10b645c0
{
public:
    void Unk_10b645c0();

private:
    unsigned char unk_00[0x38];
    UnkType_10b645c0_Page* unk_38;
};

// UnkType_10b645c0::Unk_10b645c0
void UnkType_10b645c0::Unk_10b645c0()
{
    Unk_10b721a0(unk_38, "L_Title", L"MenuSettings", L"Title", L"Localization\\PreGame_PC", 1);
    Unk_10b71f10(unk_38, GUnk_1122e428, L"MenuSettings", L"Save", L"Localization\\PreGame_PC", 1);
    Unk_10b71f10(unk_38, GUnk_1122e42c, L"MenuSettings", L"Reset", L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "B_Controls", L"MenuSettings", L"Controls", L"Localization\\PreGame_PC",
                 1);
    Unk_10b721a0(unk_38, "B_Display", L"MenuSettings", L"Display", L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "B_Sounds", L"MenuSettings", L"Sounds", L"Localization\\PreGame_PC", 1);
}
