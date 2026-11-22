// versus_leaf_0ae790.cpp -- the function at file offset 0xae790, VA 0x109ae790, 8 bytes. It sets bit 2
// of the dword at +0x360 of the object.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkType_109ae790
{
public:
    void UnkFunc_109ae790();

private:
    unsigned char unk_00[0x360];    // not read by this function
    unsigned int unk_360;
};

// UnkType_109ae790::UnkFunc_109ae790
void UnkType_109ae790::UnkFunc_109ae790()
{
    unk_360 |= 4;
}
