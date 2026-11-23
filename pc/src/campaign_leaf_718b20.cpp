// campaign_leaf_718b20.cpp -- one function at file offset 0x718b20, preferred VA 0x11018b20. It
// constructs an object in place at its argument when that is not null: the empty base's
// constructor at VA 0x10e6d490 runs, the words at 0x8 and 0xc are zeroed, 0x80000000 is stored at
// 0x10, the float 0.01 at 0x0 and a zero byte at 0x4. The class and function names are invented;
// the offsets and the callee's address are the binary's.

inline void* operator new(unsigned int Size, void* Place)
{
    return Place;
}

class UnkType_11018b20_Base
{
public:
    UnkType_11018b20_Base();
};

class UnkType_11018b20 : public UnkType_11018b20_Base
{
public:
    UnkType_11018b20()
    {
        unk_8 = 0;
        unk_c = 0;
        unk_10 = 0x80000000;
        unk_0 = 0.01f;
        unk_4 = 0;
    }

    float unk_0;
    unsigned char unk_4;
    int unk_8;
    int unk_c;
    unsigned int unk_10;
};

// Unk_11018b20
void Unk_11018b20(void* Place)
{
    new (Place) UnkType_11018b20;
}
