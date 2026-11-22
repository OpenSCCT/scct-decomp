// campaign_leaf_1a1840.cpp -- returns the float at offset 0x1b2c of this. File offset 0x1a1840,
// VA 0x10aa1840. The class and method names are invented; the offsets are the binary's.

class UnkType_10aa1840
{
public:
    float GetUnk1B2C();

private:
    unsigned char unk_00[0x1b2c];   // not read by this function
    float unk_1b2c;
};

// UnkType_10aa1840::GetUnk1B2C
float UnkType_10aa1840::GetUnk1B2C()
{
    return unk_1b2c;
}
