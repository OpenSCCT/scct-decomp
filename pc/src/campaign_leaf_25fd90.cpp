// campaign_leaf_25fd90.cpp -- a member function at VA 0x10b5fd90: it calls its own member at VA
// 0x10b645c0, then passes the object the pointer at 0x38 refers to with twelve control names
// ("A_PressBouton", "L_Shader", "L_Antialiasing", "L_TextureFiltering", "L_ShadowQuality",
// "L_Trilinear", "L_Specular" twice, "L_TexturesHighRes", "B_option_shader", "L_ShadowMapping" and
// "L_Vertical_sync"), each with the section the global at VA 0x111c24f4 points to, a key and
// package of localized text and 1, to the free function at VA 0x10b721a0. guess: sets the
// localized text of the advanced display settings. The class, method, member, parameter and global
// names are invented; the offsets, addresses and strings are the binary's.

#include "campaign_global_111c24f4.h"

class UnkType_10b5fd90_Page;

void __cdecl Unk_10b721a0(UnkType_10b5fd90_Page* Page, const char* Name,
                          const unsigned short* Section, const unsigned short* Key,
                          const unsigned short* Package, int Flags);

class UnkType_10b5fd90
{
public:
    void Unk_10b645c0();
    void Unk_10b5fd90();

private:
    unsigned char unk_00[0x38];
    UnkType_10b5fd90_Page* unk_38;
};

// UnkType_10b5fd90::Unk_10b5fd90
void UnkType_10b5fd90::Unk_10b5fd90()
{
    Unk_10b645c0();
    Unk_10b721a0(unk_38, "A_PressBouton", GUnk_111c24f4, L"Advanced", L"Localization\\PreGame_PC",
                 1);
    Unk_10b721a0(unk_38, "L_Shader", GUnk_111c24f4, L"Shader", L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "L_Antialiasing", GUnk_111c24f4, L"Antialiasing",
                 L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "L_TextureFiltering", GUnk_111c24f4, L"TextureFiltering",
                 L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "L_ShadowQuality", GUnk_111c24f4, L"ShadowQuality",
                 L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "L_Trilinear", GUnk_111c24f4, L"TrilinearFiltering",
                 L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "L_Specular", GUnk_111c24f4, L"SpecularLighting",
                 L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "L_Specular", GUnk_111c24f4, L"SpecularLighting",
                 L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "L_TexturesHighRes", GUnk_111c24f4, L"HiResTextures",
                 L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "B_option_shader", GUnk_111c24f4, L"ShaderOptions",
                 L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "L_ShadowMapping", GUnk_111c24f4, L"HWShadowMapping",
                 L"Localization\\PreGame_PC", 1);
    Unk_10b721a0(unk_38, "L_Vertical_sync", GUnk_111c24f4, L"VerticalSync",
                 L"Localization\\PreGame_PC", 1);
}
