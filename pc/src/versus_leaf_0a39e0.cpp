// versus_leaf_0a39e0.cpp -- the function at file offset 0xa39e0, VA 0x109a39e0, 4 bytes. It returns
// the dword at +0x58 of the object.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkType_109a39e0
{
public:
    int UnkFunc_109a39e0();

private:
    unsigned char unk_00[0x58];     // not read by this function
    int unk_58;
};

// UnkType_109a39e0::UnkFunc_109a39e0
int UnkType_109a39e0::UnkFunc_109a39e0()
{
    return unk_58;
}
