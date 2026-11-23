// campaign_leaf_35f0d0.cpp -- one function at file offset 0x35f0d0, preferred VA 0x10c5f0d0. It
// builds a function-local static name once from the retail string "s_CoopHackRopePrimary" and 2
// (constructor at 0x10cd4790); when the object at 0x2c8 is set and the name its method at
// 0x10cee180 returns differs from it, it passes Value to the method at 0x10c5ed70. The class,
// method, member, local and parameter names are invented; the offsets, the string and the bytes are
// the binary's.

class UnkType_10c5f0d0_Name
{
public:
    UnkType_10c5f0d0_Name(const unsigned short* Text, int Flags);

    int unk_0;
};

class UnkType_10c5f0d0_Target
{
public:
    UnkType_10c5f0d0_Name Unk_10cee180();
};

class UnkType_10c5f0d0
{
public:
    void Unk_10c5ed70(int Value);
    void Unk_10c5f0d0(int Value);

    unsigned char unk_0[0x2c8];
    UnkType_10c5f0d0_Target* unk_2c8;
};

// UnkType_10c5f0d0::Unk_10c5f0d0
void UnkType_10c5f0d0::Unk_10c5f0d0(int Value)
{
    static UnkType_10c5f0d0_Name RopeName(L"s_CoopHackRopePrimary", 2);
    if ( unk_2c8 != 0 && unk_2c8->Unk_10cee180().unk_0 != RopeName.unk_0 )
    {
        Unk_10c5ed70(Value);
    }
}
