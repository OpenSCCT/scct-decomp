// campaign_leaf_0a4740.cpp -- method at VA 0x109a4740: returns the float at 0x04 plus the
// difference between the floats at 0x00 and 0x04 scaled by the result of the free function at VA
// 0x10ccac70, which takes no arguments. The class, member and function names are invented; the
// offsets and the addresses are the binary's.

float Unk_10ccac70();

class UnkType_109a4740
{
public:
    float Unk_109a4740();

private:
    float unk_00;
    float unk_04;
};

// UnkType_109a4740::Unk_109a4740
float UnkType_109a4740::Unk_109a4740()
{
    return unk_04 + ( unk_00 - unk_04 ) * Unk_10ccac70();
}
