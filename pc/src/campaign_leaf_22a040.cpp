// campaign_leaf_22a040.cpp -- a member function at VA 0x10b2a040 that passes the narrow string
// "P_LoadOut" to the member at VA 0x10ad58d0 of the object the pointer at 0x10 refers to, sets the
// byte at 0x14 of that object and returns false. It does not read its two arguments. The class,
// method and member names are invented; the offsets, addresses and string are the binary's.

class UnkType_10ad58d0
{
public:
    void Unk_10ad58d0(const char* Name);

    unsigned char unk_00[0x14];
    bool unk_14;
};

class UnkType_10b2a040
{
public:
    bool Unk_10b2a040(int First, int Second);

private:
    unsigned char unk_00[0x10];
    UnkType_10ad58d0* unk_10;
};

// UnkType_10b2a040::Unk_10b2a040
bool UnkType_10b2a040::Unk_10b2a040(int First, int Second)
{
    unk_10->Unk_10ad58d0("P_LoadOut");
    unk_10->unk_14 = true;
    return false;
}
