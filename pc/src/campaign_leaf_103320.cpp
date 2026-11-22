// campaign_leaf_103320.cpp -- returns 1 when the pointer argument is set and the byte at its offset
// 0x2c has bit 0x10, otherwise 0. The this pointer is not used. File offset 0x103320, VA
// 0x10a03320. The class and method names are invented; the offsets are the binary's, and the
// argument's type is a guess.

class UnkType_10a03320
{
public:
    int UnkMethod_10a03320(UnkType_10a03320 *Other);

private:
    unsigned char unk_00[0x2c];     // not read by this function
    unsigned char unk_2c;           // guess: the same class as the argument
};

// UnkType_10a03320::UnkMethod_10a03320
int UnkType_10a03320::UnkMethod_10a03320(UnkType_10a03320 *Other)
{
    if ( Other && ( Other->unk_2c & 0x10 ) )
    {
        return 1;
    }
    return 0;
}
