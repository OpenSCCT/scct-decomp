// campaign_leaf_26fdb0.cpp -- a member function at VA 0x10b6fdb0 taking a flag: when the pointer at
// 0x14 is set and the flag is set, and neither the byte at 0x0c is set nor the member at VA
// 0x10ad58d0 of the object the pointer at 0x08 refers to returns true for "P_opticcable", it
// passes the pointer to the free function at VA 0x10d249e0, passes it, 1, 1 and 0 to that object's
// member at VA 0x10ad5820 and sets the byte at 0x0c; when the flag is clear and either the byte is
// set or that member returns true, it clears the byte at 0x34, passes the pointer, 0, 0 and 0 to
// the member at VA 0x10ad5820 and clears the byte at 0x0c. The class, method, member and parameter
// names are invented; the offsets, addresses and string are the binary's.

class UnkType_10b6fdb0_Page;

void __cdecl Unk_10d249e0(UnkType_10b6fdb0_Page* Page);

class UnkType_10b6fdb0_Menu
{
public:
    void Unk_10ad5820(UnkType_10b6fdb0_Page* Page, int First, int Second, int Third);
    bool Unk_10ad58d0(const char* Name);
};

class UnkType_10b6fdb0
{
public:
    void Unk_10b6fdb0(bool Flag);

private:
    unsigned char unk_00[0x08];
    UnkType_10b6fdb0_Menu* unk_08;
    bool unk_0c;
    unsigned char unk_0d[0x14 - 0x0d];
    UnkType_10b6fdb0_Page* unk_14;
    unsigned char unk_18[0x34 - 0x18];
    bool unk_34;
};

// UnkType_10b6fdb0::Unk_10b6fdb0
void UnkType_10b6fdb0::Unk_10b6fdb0(bool Flag)
{
    if ( unk_14 )
    {
        if ( Flag )
        {
            if ( !unk_0c && !unk_08->Unk_10ad58d0("P_opticcable") )
            {
                Unk_10d249e0(unk_14);
                unk_08->Unk_10ad5820(unk_14, 1, 1, 0);
                unk_0c = true;
            }
        }
        else if ( unk_0c || unk_08->Unk_10ad58d0("P_opticcable") )
        {
            unk_34 = false;
            unk_08->Unk_10ad5820(unk_14, 0, 0, 0);
            unk_0c = false;
        }
    }
}
