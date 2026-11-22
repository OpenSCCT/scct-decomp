// campaign_leaf_110820.cpp -- returns 1 when the byte at offset 0x8c of this is zero. File offset
// 0x110820, VA 0x10a10820. The class and method names are invented; the offset is the binary's.

class UnkType_10a10820
{
public:
    int TestUnk8CClear();

private:
    unsigned char unk_00[0x8c];     // not read by this function
    unsigned char unk_8c;
};

// UnkType_10a10820::TestUnk8CClear
int UnkType_10a10820::TestUnk8CClear()
{
    return unk_8c == 0;
}
