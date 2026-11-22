// campaign_leaf_08afa0.cpp -- one function at file offset 0x8afa0, preferred VA 0x1098afa0. It
// returns 0 when the pointer at offset 0x28 of this object is null. Otherwise it returns the word
// at offset 4 of the object that the pointer at offset 0x18 of the object at offset 0xd0 of the
// object at offset 0x28 designates. The class, struct and method names are invented; the offset
// and the bytes are the binary's.

struct UnkType_1098afa0_Leaf
{
    int unk_00;
    int unk_04;
};

struct UnkType_1098afa0_Mid
{
    unsigned char unk_00[0x18];     // not read by this function
    UnkType_1098afa0_Leaf *unk_18;
};

struct UnkType_1098afa0_Outer
{
    unsigned char unk_00[0xd0];     // not read by this function
    UnkType_1098afa0_Mid *unk_d0;
};

class UnkType_1098afa0
{
public:
    int UnkGetDeep() const;

private:
    unsigned char unk_00[0x28];     // not read by this function
    UnkType_1098afa0_Outer *unk_28;
};

// UnkType_1098afa0::UnkGetDeep
int UnkType_1098afa0::UnkGetDeep() const
{
    if ( unk_28 == 0 )
    {
        return 0;
    }
    return unk_28->unk_d0->unk_18->unk_04;
}
