// campaign_leaf_0a4720.cpp -- method at VA 0x109a4720: returns the float at 0x04 plus the
// difference between the floats at 0x00 and 0x04 scaled by the result of the free function at VA
// 0x10ccac40, which takes no arguments. The class, member and function names are invented; the
// offsets and the addresses are the binary's.

float Unk_10ccac40();

class UnkType_109a4720
{
public:
    float Unk_109a4720();

private:
    float unk_00;
    float unk_04;
};

// UnkType_109a4720::Unk_109a4720
float UnkType_109a4720::Unk_109a4720()
{
    return unk_04 + ( unk_00 - unk_04 ) * Unk_10ccac40();
}
