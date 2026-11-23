// campaign_leaf_257580.cpp -- a member function at VA 0x10b57580: it calls its own member at VA
// 0x10b55f50, then passes the object the pointer at 0x58 refers to with "L_Map" and with
// "L_Difficulty", and the one the pointer at 0x38 refers to with "A_press", each with a section,
// key and package of localized text and 1, to the free function at VA 0x10b721a0. guess: sets the
// localized text of three controls. The class, method, member and parameter names are invented;
// the offsets, addresses and strings are the binary's.

class UnkType_10b57580_Page;

void __cdecl Unk_10b721a0(UnkType_10b57580_Page* Page, const char* Name,
                          const unsigned short* Section, const unsigned short* Key,
                          const unsigned short* Package, int Flags);

class UnkType_10b57580
{
public:
    void Unk_10b55f50();
    void Unk_10b57580();

private:
    unsigned char unk_00[0x38];
    UnkType_10b57580_Page* unk_38;
    unsigned char unk_3c[0x58 - 0x3c];
    UnkType_10b57580_Page* unk_58;
};

// UnkType_10b57580::Unk_10b57580
void UnkType_10b57580::Unk_10b57580()
{
    Unk_10b55f50();
    Unk_10b721a0(unk_58, "L_Map", L"LOADSAVE", L"MissionInfo", L"Localization\\PreGameMenus",
                 1);
    Unk_10b721a0(unk_58, "L_Difficulty", L"LOADSAVE", L"DifficultyInfo",
                 L"Localization\\PreGameMenus", 1);
    Unk_10b721a0(unk_38, "A_press", L"MenuLoadGame", L"Saves", L"Localization\\PreGame_PC", 1);
}
