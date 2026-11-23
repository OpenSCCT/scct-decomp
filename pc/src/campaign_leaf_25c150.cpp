// campaign_leaf_25c150.cpp -- a member function at VA 0x10b5c150: it calls its own member at VA
// 0x10b645c0, then passes the object the pointer at 0x38 refers to with "A_PressBouton",
// "L_Voice", "L_Music", "L_Ambient", "L_SFX", "L_VoiceChatEnable" and "L_OriginalVoices", each
// with a section, key and package of localized text and 1, to the free function at VA 0x10b721a0.
// guess: sets the localized text of the sound settings. The class, method, member and parameter
// names are invented; the offsets, addresses and strings are the binary's.

class UnkType_10b5c150_Page;

void __cdecl Unk_10b721a0(UnkType_10b5c150_Page* Page, const char* Name,
                          const unsigned short* Section, const unsigned short* Key,
                          const unsigned short* Package, int Flags);

class UnkType_10b5c150
{
public:
    void Unk_10b645c0();
    void Unk_10b5c150();

private:
    unsigned char unk_00[0x38];
    UnkType_10b5c150_Page* unk_38;
};

// UnkType_10b5c150::Unk_10b5c150
void UnkType_10b5c150::Unk_10b5c150()
{
    Unk_10b645c0();
    Unk_10b721a0(unk_38, "A_PressBouton", L"MenuSettings", L"Sounds", L"Localization\\PreGame_PC",
                 1);
    Unk_10b721a0(unk_38, "L_Voice", L"MenuSettings", L"VoiceConfig", L"Localization\\PreGame_PC",
                 1);
    Unk_10b721a0(unk_38, "L_Music", L"MenuSettings", L"MusicVolume", L"Localization\\PreGame_PC",
                 1);
    Unk_10b721a0(unk_38, "L_Ambient", L"MenuSettings", L"AmbientVolume",
                 L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "L_SFX", L"MenuSettings", L"SFXVolume", L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "L_VoiceChatEnable", L"MenuSettings", L"VoiceChatEnable",
                 L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "L_OriginalVoices", L"MenuSettings", L"OriginalVoices",
                 L"Localization\\PreGame_PC", 1);
}
