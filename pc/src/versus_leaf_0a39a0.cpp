// versus_leaf_0a39a0.cpp -- the function at file offset 0xa39a0, VA 0x109a39a0, 4 bytes. It returns
// the dword at +0x54 of the object.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkType_109a39a0
{
public:
    int UnkFunc_109a39a0();

private:
    unsigned char unk_00[0x54];     // not read by this function
    int unk_54;
};

// UnkType_109a39a0::UnkFunc_109a39a0
int UnkType_109a39a0::UnkFunc_109a39a0()
{
    return unk_54;
}
