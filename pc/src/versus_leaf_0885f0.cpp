// versus_leaf_0885f0.cpp -- the function at file offset 0x885f0, VA 0x109885f0, 24 bytes. When its
// argument is not null and the byte at +0x34 of the argument has bit 5 set, it sets bit 2 of the
// dword at +0x2ec of the object (ret 4).
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkOther_109885f0
{
public:
    unsigned char unk_00[0x34];     // not read by this function
    unsigned char unk_34;
};

class UnkType_109885f0
{
public:
    void UnkFunc_109885f0(UnkOther_109885f0 *Other);

private:
    unsigned char unk_00[0x2ec];    // not read by this function
    unsigned int unk_2ec;
};

// UnkType_109885f0::UnkFunc_109885f0
void UnkType_109885f0::UnkFunc_109885f0(UnkOther_109885f0 *Other)
{
    if ( Other && ( Other->unk_34 & 0x20 ) )
    {
        unk_2ec |= 4;
    }
}
