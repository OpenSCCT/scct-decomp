// campaign_leaf_4b4c60.cpp -- one function at file offset 0x4b4c60, preferred VA 0x10db4c60.
// The constructor runs the base constructor at 0x10d9d560 and empties the wide strings at offsets
// 0, 0x800 and 0x900. The class and member names are invented; the offset and the bytes are the
// binary's.

class UnkType_10db4c60_Base
{
public:
    UnkType_10db4c60_Base();
};

class UnkType_10db4c60 : public UnkType_10db4c60_Base
{
public:
    unsigned short unk_0[0x400];
    unsigned short unk_800[0x80];
    unsigned short unk_900[1];

    UnkType_10db4c60();
};

// UnkType_10db4c60::UnkType_10db4c60
UnkType_10db4c60::UnkType_10db4c60()
{
    unk_0[0] = 0;
    unk_800[0] = 0;
    unk_900[0] = 0;
}
