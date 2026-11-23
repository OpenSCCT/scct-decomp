// campaign_leaf_264990.cpp -- a member function at VA 0x10b64990: when the byte at 0x5c is set it
// passes the pointer at 0x04, the global at VA 0x1122e470, L"Loading", L"LoadingMsg",
// L"Localization\\PreGame_PC" and 1 to the free function at VA 0x10b71f10, then the same with the
// global at VA 0x1122e480 and L"PressKey". The class, function, method, member, parameter and
// global names are invented; the offsets, strings and addresses are the binary's.

#include "campaign_global_1122e470.h"
#include "campaign_global_1122e480.h"

void Unk_10b71f10(void* Owner, int Name, const unsigned short* Section, const unsigned short* Value,
                  const unsigned short* File, int Flags);

class UnkType_10b64990
{
public:
    void Unk_10b64990();

private:
    int unk_00;
    void* unk_04;
    unsigned char unk_08[0x5c - 0x08];
    bool unk_5c;
};

// UnkType_10b64990::Unk_10b64990
void UnkType_10b64990::Unk_10b64990()
{
    if ( unk_5c )
    {
        Unk_10b71f10(unk_04, GUnk_1122e470, L"Loading", L"LoadingMsg",
                     L"Localization\\PreGame_PC", 1);
        Unk_10b71f10(unk_04, GUnk_1122e480, L"Loading", L"PressKey", L"Localization\\PreGame_PC",
                     1);
    }
}
