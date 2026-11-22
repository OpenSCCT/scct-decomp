// versus_leaf_207570.cpp -- returns the float member at 0x158 of the object, at file offset 0x207570 (VA 0x10b07570).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b07570
{
public:
    float GetUnk158();

private:
    unsigned char unk_00[0x158];  // not read by this function
    float unk_158;        // read by GetUnk158
};

// UnkType_10b07570::GetUnk158
float UnkType_10b07570::GetUnk158()
{
    return unk_158;
}
