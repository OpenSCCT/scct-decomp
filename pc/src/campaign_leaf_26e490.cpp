// campaign_leaf_26e490.cpp -- a member function at VA 0x10b6e490 taking a flag: when the pointer
// at 0x1c is set and the flag is set, and the member at VA 0x10ad58d0 of the object the pointer at
// 0x10 refers to returns false for "P_EEV", it passes the pointer to the free function at VA
// 0x10d249e0 and passes it, 1, 1 and 0 to that object's member at VA 0x10ad5820; when the flag is
// clear and that member returns true for "P_EEV", it calls its own member at VA 0x10b6df30 and
// passes the pointer, 0, 0 and 0 to the member at VA 0x10ad5820. The class, method, member and
// parameter names are invented; the offsets, addresses and string are the binary's.

class UnkType_10b6e490_Page;

void __cdecl Unk_10d249e0(UnkType_10b6e490_Page* Page);

class UnkType_10b6e490_Menu
{
public:
    void Unk_10ad5820(UnkType_10b6e490_Page* Page, int First, int Second, int Third);
    bool Unk_10ad58d0(const char* Name);
};

class UnkType_10b6e490
{
public:
    void Unk_10b6df30();
    void Unk_10b6e490(bool Flag);

private:
    unsigned char unk_00[0x10];
    UnkType_10b6e490_Menu* unk_10;
    unsigned char unk_14[0x1c - 0x14];
    UnkType_10b6e490_Page* unk_1c;
};

// UnkType_10b6e490::Unk_10b6e490
void UnkType_10b6e490::Unk_10b6e490(bool Flag)
{
    if ( unk_1c )
    {
        if ( Flag )
        {
            if ( !unk_10->Unk_10ad58d0("P_EEV") )
            {
                Unk_10d249e0(unk_1c);
                unk_10->Unk_10ad5820(unk_1c, 1, 1, 0);
            }
        }
        else if ( unk_10->Unk_10ad58d0("P_EEV") )
        {
            Unk_10b6df30();
            unk_10->Unk_10ad5820(unk_1c, 0, 0, 0);
        }
    }
}
