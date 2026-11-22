// campaign_leaf_10e2a0.cpp -- one function at file offset 0x10e2a0, preferred VA 0x10a0e2a0. It
// takes the object at offset 0x2c, or when that is null the first entry of the array reached
// through offsets 0x30, 0x28 and 0x2c, and returns the word at offset 0x30 of it, or 0 when there
// is none. The class, method and member names are invented; the offset and the bytes are the
// binary's.

class UnkType_10a0e2a0_Item
{
public:
    unsigned char unk_0[0x30];
    int unk_30;
};

class UnkType_10a0e2a0_Inner
{
public:
    unsigned char unk_0[0x2c];
    UnkType_10a0e2a0_Item** unk_2c;
};

class UnkType_10a0e2a0_Outer
{
public:
    unsigned char unk_0[0x28];
    UnkType_10a0e2a0_Inner* unk_28;
};

class UnkType_10a0e2a0
{
public:
    unsigned char unk_0[0x2c];
    UnkType_10a0e2a0_Item* unk_2c;
    UnkType_10a0e2a0_Outer* unk_30;

    UnkType_10a0e2a0_Item* GetUnkItem() const
    {
        return unk_2c ? unk_2c : unk_30->unk_28->unk_2c[0];
    }

    int Unk_10a0e2a0();
};

// UnkType_10a0e2a0::Unk_10a0e2a0
int UnkType_10a0e2a0::Unk_10a0e2a0()
{
    if ( GetUnkItem() )
    {
        return GetUnkItem()->unk_30;
    }
    return 0;
}
