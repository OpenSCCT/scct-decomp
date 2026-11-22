// versus_leaf_0c0760.cpp -- the function at file offset 0xc0760, VA 0x109c0760, 4 bytes. It increments
// the dword at +0x28 of the object.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkType_109c0760
{
public:
    void UnkFunc_109c0760();

private:
    unsigned char unk_00[0x28];     // not read by this function
    int unk_28;
};

// UnkType_109c0760::UnkFunc_109c0760
void UnkType_109c0760::UnkFunc_109c0760()
{
    ++unk_28;
}
