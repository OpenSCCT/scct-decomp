// campaign_leaf_3558a0.cpp -- one function at file offset 0x3558a0, preferred VA 0x10c558a0. It
// copies the three-word structures at 0xe8 and 0xf4 into Target at 0x368 and 0x380. The class,
// method, structure and member names are invented; the offsets and the bytes are the binary's.

struct UnkTriple
{
    int unk_0;
    int unk_4;
    int unk_8;
};

struct UnkTarget
{
    unsigned char unk_0[0x368];
    UnkTriple unk_368;
    unsigned char unk_374[0xc];
    UnkTriple unk_380;
};

class UnkType_10c558a0
{
public:
    void Unk_10c558a0(UnkTarget* Target) const;

    unsigned char unk_0[0xe8];
    UnkTriple unk_e8;
    UnkTriple unk_f4;
};

// UnkType_10c558a0::Unk_10c558a0
void UnkType_10c558a0::Unk_10c558a0(UnkTarget* Target) const
{
    Target->unk_368 = unk_e8;
    Target->unk_380 = unk_f4;
}
