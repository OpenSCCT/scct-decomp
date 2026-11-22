// campaign_leaf_05aee0.cpp -- one function at file offset 0x5aee0, preferred VA 0x1095aee0. It
// returns 0 when its pointer argument is null. Otherwise, when the pointer at offset 0x2fc is set
// and the second argument is zero, it stores that pointer in the first argument; in every other
// case it stores this object. It returns 1 in the non-null case. The class, method and parameter
// names are invented; the offset and the bytes are the binary's.

class UnkType_1095aee0
{
public:
    int UnkGetOwnerUnless(void **Out, int Second);

private:
    unsigned char unk_00[0x2fc];    // not read by this function
    void *unk_2fc;                  // pointer, tested against zero
};

// UnkType_1095aee0::UnkGetOwnerUnless
int UnkType_1095aee0::UnkGetOwnerUnless(void **Out, int Second)
{
    if ( Out == 0 )
    {
        return 0;
    }
    if ( unk_2fc != 0 && Second == 0 )
    {
        *Out = unk_2fc;
        return 1;
    }
    *Out = this;
    return 1;
}
