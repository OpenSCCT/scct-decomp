// versus_leaf_207e30.cpp -- sets the int at 0x160 of the object to 2 unless it is 2 already, at file offset 0x207e30 (VA 0x10b07e30).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b07e30
{
public:
    void SetUnk160Two();

private:
    unsigned char unk_00[0x160];        // not read by this function
    int unk_160;                        // compared with 2 and set to 2 by SetUnk160Two
};

// UnkType_10b07e30::SetUnk160Two
void UnkType_10b07e30::SetUnk160Two()
{
    if ( unk_160 != 2 )
        unk_160 = 2;
}
