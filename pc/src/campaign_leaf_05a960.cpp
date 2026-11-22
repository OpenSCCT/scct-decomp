// campaign_leaf_05a960.cpp -- one function at file offset 0x5a960, preferred VA 0x1095a960. It
// returns 0 when its pointer argument is null. Otherwise it stores in that argument this object's
// pointer at offset 0x2fc, or this object when that pointer is null, and returns 1. The class,
// method and parameter names are invented; the offset and the bytes are the binary's.

class UnkType_1095a960
{
public:
    int UnkGetOwner(void **Out, int Second);

private:
    unsigned char unk_00[0x2fc];    // not read by this function
    void *unk_2fc;                  // pointer, tested against zero
};

// UnkType_1095a960::UnkGetOwner
int UnkType_1095a960::UnkGetOwner(void **Out, int Second)
{
    if ( Out == 0 )
    {
        return 0;
    }
    if ( unk_2fc != 0 )
    {
        *Out = unk_2fc;
    }
    else
    {
        *Out = this;
    }
    return 1;
}
