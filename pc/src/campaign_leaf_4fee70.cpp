// campaign_leaf_4fee70.cpp -- one function at file offset 0x4fee70, preferred VA 0x10dfee70. It
// copies six words of the object (0x8, 0xc, 0x10, 0x14, 0x20, 0x24) into the argument at 0x0,
// 0x8, 0x4, 0xc, 0x18 and 0x1c. The class, method, structure and member names are invented; the
// offsets and the bytes are the binary's.

struct UnkOut_10dfee70
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
};

class UnkType_10dfee70
{
public:
    void Unk_10dfee70(UnkOut_10dfee70& Out) const;

    unsigned char unk_0[0x8];
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
    unsigned char unk_18[0x8];
    int unk_20;
    int unk_24;
};

// UnkType_10dfee70::Unk_10dfee70
void UnkType_10dfee70::Unk_10dfee70(UnkOut_10dfee70& Out) const
{
    Out.unk_0 = unk_8;
    Out.unk_8 = unk_c;
    Out.unk_4 = unk_10;
    Out.unk_c = unk_14;
    Out.unk_18 = unk_20;
    Out.unk_1c = unk_24;
}
