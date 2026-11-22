// versus_leaf_2076d0.cpp -- returns the float member at 0x174 of the object, at file offset 0x2076d0 (VA 0x10b076d0).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b076d0
{
public:
    float GetUnk174();

private:
    unsigned char unk_00[0x174];  // not read by this function
    float unk_174;        // read by GetUnk174
};

// UnkType_10b076d0::GetUnk174
float UnkType_10b076d0::GetUnk174()
{
    return unk_174;
}
