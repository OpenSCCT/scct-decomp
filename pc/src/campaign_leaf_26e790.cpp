// campaign_leaf_26e790.cpp -- a member function at VA 0x10b6e790 taking a pointer: when the free
// function at VA 0x10b71bf0 returns non-zero for it and "P_EEV", it passes it, a string made from
// L"AL_clic,EEV_AL_clic,A,EEV_A" and 0, then it, a string made from
// L"DL,EEV_DL,DR,EEV_DR,DU,OpticCable_DU,AR_clic,EEV_AR_clic" and 1, to the member at VA 0x10ad93d0
// of the object the pointer at 0x10 refers to, and returns true; otherwise it returns false. The
// strings are made with the constructor at VA 0x1090ba00 and destroyed with the destructor at VA
// 0x1090ba70. The class, method, member and parameter names are invented; the offsets, addresses
// and strings are the binary's.

class UnkType_10b6e790_Page;

int __cdecl Unk_10b71bf0(UnkType_10b6e790_Page* Page, const char* Name);

class UnkType_10b6e790_String
{
public:
    UnkType_10b6e790_String(const unsigned short* Text);
    ~UnkType_10b6e790_String();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b6e790_Menu
{
public:
    void Unk_10ad93d0(UnkType_10b6e790_Page* Page, const UnkType_10b6e790_String& Text,
                      int Flags);
};

class UnkType_10b6e790
{
public:
    bool Unk_10b6e790(UnkType_10b6e790_Page* Page);

private:
    unsigned char unk_00[0x10];
    UnkType_10b6e790_Menu* unk_10;
};

// UnkType_10b6e790::Unk_10b6e790
bool UnkType_10b6e790::Unk_10b6e790(UnkType_10b6e790_Page* Page)
{
    if ( Unk_10b71bf0(Page, "P_EEV") )
    {
        {
            UnkType_10b6e790_String Text(L"AL_clic,EEV_AL_clic,A,EEV_A");
            unk_10->Unk_10ad93d0(Page, Text, 0);
        }
        UnkType_10b6e790_String Text(L"DL,EEV_DL,DR,EEV_DR,DU,OpticCable_DU,AR_clic,EEV_AR_clic");
        unk_10->Unk_10ad93d0(Page, Text, 1);
        return true;
    }
    return false;
}
