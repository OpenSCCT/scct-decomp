// versus_leaf_0a39b0.cpp -- the function at file offset 0xa39b0, VA 0x109a39b0, 10 bytes. It stores its
// argument in the dword at +0x54 of the object (ret 4).
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkType_109a39b0
{
public:
    void UnkFunc_109a39b0(int Value);

private:
    unsigned char unk_00[0x54];     // not read by this function
    int unk_54;
};

// UnkType_109a39b0::UnkFunc_109a39b0
void UnkType_109a39b0::UnkFunc_109a39b0(int Value)
{
    unk_54 = Value;
}
