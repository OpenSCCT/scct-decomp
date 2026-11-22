// versus_leaf_25e840.cpp -- clears the byte at 0x54, at file offset 0x25e840 (VA 0x10b5e840).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b5e840
{
public:
    void ClearUnk54();

private:
    unsigned char unk_00[0x54];         // not read by this function
    unsigned char unk_54;               // cleared by ClearUnk54
};

// UnkType_10b5e840::ClearUnk54
void UnkType_10b5e840::ClearUnk54()
{
    unk_54 = 0;
}
