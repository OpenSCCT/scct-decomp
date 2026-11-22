// versus_leaf_2038a0.cpp -- returns the int member at 0x2c of the object, at file offset 0x2038a0 (VA 0x10b038a0).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b038a0
{
public:
    int GetUnk2C();

private:
    unsigned char unk_00[0x2c];  // not read by this function
    int unk_2c;        // read by GetUnk2C
};

// UnkType_10b038a0::GetUnk2C
int UnkType_10b038a0::GetUnk2C()
{
    return unk_2c;
}
