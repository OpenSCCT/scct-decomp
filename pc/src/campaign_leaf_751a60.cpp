// campaign_leaf_751a60.cpp -- one function at file offset 0x751a60, preferred VA 0x11051a60. It
// sets bit 4 of the flags its second argument points to when the word at 0x28 of its first argument
// is zero, and otherwise bit 1 or bit 2 according to whether the word at 0x10 is non-zero. It has
// no this pointer. The class, function and member names are invented; the offset and the bytes are
// the binary's.

struct UnkType_11051a60
{
    unsigned char unk_0[0x10];
    int unk_10;
    unsigned char unk_14[0x28 - 0x14];
    int unk_28;
};

// Unk_11051a60
void Unk_11051a60(UnkType_11051a60* Object, unsigned int* Flags)
{
    if ( Object->unk_28 != 0 )
    {
        if ( Object->unk_10 != 0 )
        {
            *Flags |= 1;
        }
        else
        {
            *Flags |= 2;
        }
    }
    else
    {
        *Flags |= 4;
    }
}
