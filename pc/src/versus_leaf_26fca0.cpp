// versus_leaf_26fca0.cpp -- stores its argument at 0x50 and returns true, at file offset 0x26fca0 (VA 0x10b6fca0).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b6fca0
{
public:
    bool SetUnk50(int Value);

private:
    unsigned char unk_00[0x50];         // not read by this function
    int unk_50;                         // written by SetUnk50
};

// UnkType_10b6fca0::SetUnk50
// The function pops its one argument (ret 4).
bool UnkType_10b6fca0::SetUnk50(int Value)
{
    unk_50 = Value;
    return true;
}
