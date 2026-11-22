// campaign_leaf_7653e0.cpp -- one function at file offset 0x7653e0, preferred VA 0x110653e0. A
// constructor taking three values: it stores the second at 0x0, the first at 0x24 and the third at
// 0x4, and zeroes the words from 0x8 to 0x20. The class, constructor parameter and member names are
// invented; the offset and the bytes are the binary's.

class UnkType_110653e0
{
public:
    UnkType_110653e0(int First, int Second, int Third);

    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
};

// UnkType_110653e0::UnkType_110653e0
UnkType_110653e0::UnkType_110653e0(int First, int Second, int Third)
{
    unk_0 = Second;
    unk_4 = Third;
    unk_24 = First;
    unk_20 = 0;
    unk_8 = 0;
    unk_c = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
    unk_1c = 0;
}
