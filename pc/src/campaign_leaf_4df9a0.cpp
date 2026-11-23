// campaign_leaf_4df9a0.cpp -- one function at file offset 0x4df9a0, preferred VA 0x10ddf9a0.
// It returns 0 when the int at offset 8 of what the method at 0x10ddf820 returns is 0, and
// otherwise the int at offset 8 of the object reached through its pointer at offset 4. The class,
// structure, method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10ddf9a0_Leaf
{
    int unk_0;
    int unk_4;
    int unk_8;
};

struct UnkType_10ddf9a0_Info
{
    int unk_0;
    UnkType_10ddf9a0_Leaf** unk_4;
    int unk_8;
};

class UnkType_10ddf9a0
{
public:
    UnkType_10ddf9a0_Info* Unk_10ddf820();
    int Unk_10ddf9a0();
};

// UnkType_10ddf9a0::Unk_10ddf9a0
int UnkType_10ddf9a0::Unk_10ddf9a0()
{
    if ( Unk_10ddf820()->unk_8 == 0 )
    {
        return 0;
    }
    return (*Unk_10ddf820()->unk_4)->unk_8;
}
