// campaign_leaf_358fc0.cpp -- one function at file offset 0x358fc0, preferred VA 0x10c58fc0. It
// calls the method at 0x10c57020; when the word at 0x4f8 is set and the name at 0x70 is clear, it
// copies the word at 0x4f8 to 0x488 and stores at 0x70 a function-local static name built once
// from the retail string "s_Alert" and 2 (constructor at 0x10cd4790). The class, method, member
// and local names are invented; the offsets, the string and the bytes are the binary's.

class UnkType_10c58fc0_Name
{
public:
    UnkType_10c58fc0_Name(const unsigned short* Text, int Flags);

    int unk_0;
};

class UnkType_10c58fc0
{
public:
    void Unk_10c57020();
    void Unk_10c58fc0();

    unsigned char unk_0[0x70];
    UnkType_10c58fc0_Name unk_70;
    unsigned char unk_74[0x414];
    int unk_488;
    unsigned char unk_48c[0x6c];
    int unk_4f8;
};

// UnkType_10c58fc0::Unk_10c58fc0
void UnkType_10c58fc0::Unk_10c58fc0()
{
    Unk_10c57020();
    if ( unk_4f8 != 0 && unk_70.unk_0 == 0 )
    {
        static UnkType_10c58fc0_Name AlertName(L"s_Alert", 2);
        unk_488 = unk_4f8;
        unk_70 = AlertName;
    }
}
