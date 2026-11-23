// campaign_leaf_25e1c0.cpp -- a member function at VA 0x10b5e1c0: it calls its own member at VA
// 0x10b645c0, then passes the object the pointer at 0x38 refers to with "A_PressBouton",
// "B_Advanced", "L_Brightness", "L_Contrast" and "L_Resolution", each with a section, key and
// package of localized text and 1, to the free function at VA 0x10b721a0. guess: sets the
// localized text of five controls. The class, method, member and parameter names are invented;
// the offsets, addresses and strings are the binary's.

class UnkType_10b5e1c0_Page;

void __cdecl Unk_10b721a0(UnkType_10b5e1c0_Page* Page, const char* Name,
                          const unsigned short* Section, const unsigned short* Key,
                          const unsigned short* Package, int Flags);

class UnkType_10b5e1c0
{
public:
    void Unk_10b645c0();
    void Unk_10b5e1c0();

private:
    unsigned char unk_00[0x38];
    UnkType_10b5e1c0_Page* unk_38;
};

// UnkType_10b5e1c0::Unk_10b5e1c0
void UnkType_10b5e1c0::Unk_10b5e1c0()
{
    Unk_10b645c0();
    Unk_10b721a0(unk_38, "A_PressBouton", L"MenuSettings", L"Display", L"Localization\\PreGame_PC",
                 1);
    Unk_10b721a0(unk_38, "B_Advanced", L"MenuSettings", L"Advanced", L"Localization\\PreGame_PC",
                 1);
    Unk_10b721a0(unk_38, "L_Brightness", L"MenuSettings", L"Brightness",
                 L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "L_Contrast", L"MenuSettings", L"Contrast", L"Localization\\PreGame_PC",
                 1);
    Unk_10b721a0(unk_38, "L_Resolution", L"MenuSettings", L"Resolution",
                 L"Localization\\PreGame_PC", 1);
}
