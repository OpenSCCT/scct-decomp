// campaign_leaf_5435f0.cpp -- one function at file offset 0x5435f0, preferred VA 0x10e435f0. For
// each of the three floats it replaces Out's component with Value where Test's component exceeds
// Limit. It has no this pointer. The function, structure, member and parameter names are
// invented; the bytes are the binary's.

struct UnkType_10e435f0_Vector
{
    float unk_0;
    float unk_4;
    float unk_8;
};

// Unk_10e435f0
void Unk_10e435f0(UnkType_10e435f0_Vector& Out, const float& Value,
                  const UnkType_10e435f0_Vector& Test, const float& Limit)
{
    Out.unk_0 = Test.unk_0 > Limit ? Value : Out.unk_0;
    Out.unk_4 = Test.unk_4 > Limit ? Value : Out.unk_4;
    Out.unk_8 = Test.unk_8 > Limit ? Value : Out.unk_8;
}
