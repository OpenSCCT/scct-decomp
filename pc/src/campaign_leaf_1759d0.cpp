// campaign_leaf_1759d0.cpp -- returns the entry of the array at offset 0x70 of this, whose dword at
// offset 0x34 equals the argument, or null. An argument of -1 gives null at once. File offset
// 0x1759d0, VA 0x10a759d0. The class and method names are invented; the offsets are the binary's,
// and the entry type is a guess.

class UnkItem_10a759d0;

class UnkType_10a759d0
{
public:
    UnkItem_10a759d0 *UnkMethod_10a759d0(int Key);

private:
    unsigned char unk_00[0x70];     // not read by this function
    UnkItem_10a759d0 **unk_70;      // guess: array of pointers to items
    int unk_74;                     // count of items
};

class UnkItem_10a759d0
{
public:
    unsigned char unk_00[0x34];     // not read by this function
    int unk_34;
};

// UnkType_10a759d0::UnkMethod_10a759d0
UnkItem_10a759d0 *UnkType_10a759d0::UnkMethod_10a759d0(int Key)
{
    int i;

    if ( Key == -1 )
    {
        return 0;
    }
    for ( i = 0; i < unk_74; i++ )
    {
        if ( Key == unk_70[i]->unk_34 )
        {
            return unk_70[i];
        }
    }
    return 0;
}
