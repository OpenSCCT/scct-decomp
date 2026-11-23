// campaign_leaf_4ab3e0.cpp -- one function at file offset 0x4ab3e0, preferred VA 0x10dab3e0.
// The constructor runs the base constructor at 0x10d9d560 and clears the int at offset 4 and the
// short at offset 0. The class and member names are invented; the offset and the bytes are the
// binary's.

class UnkType_10dab3e0_Base
{
public:
    UnkType_10dab3e0_Base();
};

class UnkType_10dab3e0 : public UnkType_10dab3e0_Base
{
public:
    short unk_0;
    int unk_4;

    UnkType_10dab3e0();
};

// UnkType_10dab3e0::UnkType_10dab3e0
UnkType_10dab3e0::UnkType_10dab3e0()
{
    unk_4 = 0;
    unk_0 = 0;
}
