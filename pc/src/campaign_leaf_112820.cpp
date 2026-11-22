// campaign_leaf_112820.cpp -- returns 1 when the byte at offset 0x51 of this is zero. File offset
// 0x112820, VA 0x10a12820. The class and method names are invented; the offset is the binary's.

class UnkType_10a12820
{
public:
    int TestUnk51Clear();

private:
    unsigned char unk_00[0x51];     // not read by this function
    unsigned char unk_51;
};

// UnkType_10a12820::TestUnk51Clear
int UnkType_10a12820::TestUnk51Clear()
{
    return unk_51 == 0;
}
