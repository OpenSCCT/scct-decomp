// campaign_leaf_135970.cpp -- returns 1 when the dword at offset 0xa8c of this is nonzero and the
// byte at offset 0xa90 is nonzero, otherwise 0. File offset 0x135970, VA 0x10a35970. The class and
// method names are invented; the offsets are the binary's.

class UnkType_10a35970
{
public:
    int TestUnkA8CAndA90();

private:
    unsigned char unk_00[0xa8c];    // not read by this function
    int unk_a8c;
    unsigned char unk_a90;
};

// UnkType_10a35970::TestUnkA8CAndA90
int UnkType_10a35970::TestUnkA8CAndA90()
{
    if ( unk_a8c != 0 && unk_a90 != 0 )
    {
        return 1;
    }
    return 0;
}
