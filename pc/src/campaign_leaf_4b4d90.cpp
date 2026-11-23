// campaign_leaf_4b4d90.cpp -- one function at file offset 0x4b4d90, preferred VA 0x10db4d90.
// The constructor runs the base constructor at 0x10d9d560 and empties the wide strings at offsets
// 0, 0x900 and 0x800. The class and member names are invented; the offset and the bytes are the
// binary's.

class UnkType_10db4d90_Base
{
public:
    UnkType_10db4d90_Base();
};

class UnkType_10db4d90 : public UnkType_10db4d90_Base
{
public:
    unsigned short unk_0[0x400];
    unsigned short unk_800[0x80];
    unsigned short unk_900[1];

    UnkType_10db4d90();
};

// UnkType_10db4d90::UnkType_10db4d90
UnkType_10db4d90::UnkType_10db4d90()
{
    unk_0[0] = 0;
    unk_900[0] = 0;
    unk_800[0] = 0;
}
