// campaign_leaf_05af20.cpp -- one function at file offset 0x5af20, preferred VA 0x1095af20. It
// returns 0 when its pointer argument is null. Otherwise, when the pointer at offset 0x2fc is set,
// it stores that pointer in the argument, and it returns 1. The class, method and parameter names
// are invented; the offset and the bytes are the binary's.

class UnkType_1095af20
{
public:
    int UnkGetOwnerIfSet(void **Out);

private:
    unsigned char unk_00[0x2fc];    // not read by this function
    void *unk_2fc;                  // pointer, tested against zero
};

// UnkType_1095af20::UnkGetOwnerIfSet
int UnkType_1095af20::UnkGetOwnerIfSet(void **Out)
{
    if ( Out == 0 )
    {
        return 0;
    }
    if ( unk_2fc != 0 )
    {
        *Out = unk_2fc;
    }
    return 1;
}
