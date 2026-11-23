// campaign_leaf_2627e0.cpp -- a member function at VA 0x10b627e0: it calls its own member at VA
// 0x10b645c0, then passes the object the pointer at 0x38 refers to with "A_PressBouton",
// "L_SensitivityMouse" and "L_InvertMouse", and the one the pointer at 0x78 refers to with
// "T_PressAKey" and "T_EscCancel", each with a section, key and package of localized text and 1,
// to the free function at VA 0x10b721a0, and the object at 0x38 with the global at VA 0x1122e3fc
// likewise to the free function at VA 0x10b71f10. guess: sets the localized text of the controls.
// The class, method, member, parameter and global names are invented; the offsets, addresses and
// strings are the binary's.

#include "campaign_global_1122e3fc.h"

class UnkType_10b627e0_Page;

void __cdecl Unk_10b71f10(UnkType_10b627e0_Page* Page, int Name, const unsigned short* Section,
                          const unsigned short* Key, const unsigned short* Package, int Flags);
void __cdecl Unk_10b721a0(UnkType_10b627e0_Page* Page, const char* Name,
                          const unsigned short* Section, const unsigned short* Key,
                          const unsigned short* Package, int Flags);

class UnkType_10b627e0
{
public:
    void Unk_10b645c0();
    void Unk_10b627e0();

private:
    unsigned char unk_00[0x38];
    UnkType_10b627e0_Page* unk_38;
    unsigned char unk_3c[0x78 - 0x3c];
    UnkType_10b627e0_Page* unk_78;
};

// UnkType_10b627e0::Unk_10b627e0
void UnkType_10b627e0::Unk_10b627e0()
{
    Unk_10b645c0();
    Unk_10b721a0(unk_38, "A_PressBouton", L"MenuSettings", L"Controls", L"Localization\\PreGame_PC",
                 1);
    Unk_10b721a0(unk_38, "L_SensitivityMouse", L"MenuSettings", L"MouseSensitivity",
                 L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "L_InvertMouse", L"MenuSettings", L"InvertMouse",
                 L"Localization\\PreGame_PC", 1);
    Unk_10b71f10(unk_38, GUnk_1122e3fc, L"MenuSettings", L"Joystick", L"Localization\\PreGame_PC",
                 1);
    Unk_10b721a0(unk_78, "T_PressAKey", L"MenuSettings", L"PressAKey", L"Localization\\PreGame_PC",
                 1);
    Unk_10b721a0(unk_78, "T_EscCancel", L"MenuSettings", L"EscCancel", L"Localization\\PreGame_PC",
                 1);
}
