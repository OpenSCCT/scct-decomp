// versus_leaf_054340.cpp -- the function at file offset 0x54340, VA 0x10954340, 7 bytes. It loads the
// pointer at +0x24 and returns the byte at +0x20 of the object it points to.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkRef_10954340
{
public:
    unsigned char unk_00[0x20];     // not read by this function
    unsigned char unk_20;
};

class UnkType_10954340
{
public:
    unsigned char UnkFunc_10954340();

private:
    unsigned char unk_00[0x24];     // not read by this function
    UnkRef_10954340 *unk_24;
};

// UnkType_10954340::UnkFunc_10954340
unsigned char UnkType_10954340::UnkFunc_10954340()
{
    return unk_24->unk_20;
}
