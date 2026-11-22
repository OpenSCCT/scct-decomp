// campaign_leaf_1a1830.cpp -- returns the float at offset 0x19d8 of this. File offset 0x1a1830,
// VA 0x10aa1830. The class and method names are invented; the offsets are the binary's.

class UnkType_10aa1830
{
public:
    float GetUnk19D8();

private:
    unsigned char unk_00[0x19d8];   // not read by this function
    float unk_19d8;
};

// UnkType_10aa1830::GetUnk19D8
float UnkType_10aa1830::GetUnk19D8()
{
    return unk_19d8;
}
