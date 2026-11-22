// campaign_leaf_099530.cpp -- one function at file offset 0x99530, preferred VA 0x10999530. It
// stores its second argument in the word at offset 0x3b0 when that word equals its first argument.
// The class and method names are invented; the offset and the bytes are the binary's.

class UnkType_10999530
{
public:
    void UnkSetIfEqual(int Expected, int NewValue);

private:
    unsigned char unk_00[0x3b0];    // not read by this function
    int unk_3b0;
};

// UnkType_10999530::UnkSetIfEqual
void UnkType_10999530::UnkSetIfEqual(int Expected, int NewValue)
{
    if ( unk_3b0 == Expected )
    {
        unk_3b0 = NewValue;
    }
}
