// campaign_leaf_0432f0.cpp -- one function at file offset 0x432f0, preferred VA 0x109432f0. It
// copies the three floats that its fourth argument points to into this object, stores in the word
// at offset 0xc the sum of the first argument times the first float of that vector, and the second
// and third arguments times the second and third floats, and returns this object. The class,
// struct, method and parameter names are invented; the offset and the bytes are the binary's.

struct UnkType_109432f0_Vec3
{
    float unk_00;
    float unk_04;
    float unk_08;
};

class UnkType_109432f0
{
public:
    UnkType_109432f0 *UnkSetPlane(float First, float Second, float Third,
                                  const UnkType_109432f0_Vec3 *Vec);

private:
    UnkType_109432f0_Vec3 unk_00;   // copied from the argument
    float unk_0c;                   // dot product of the arguments with the copied vector
};

// UnkType_109432f0::UnkSetPlane
UnkType_109432f0 *UnkType_109432f0::UnkSetPlane(float First, float Second, float Third,
                                                const UnkType_109432f0_Vec3 *Vec)
{
    unk_00 = *Vec;
    unk_0c = ( Second * Vec->unk_04 + Third * Vec->unk_08 ) + First * Vec->unk_00;
    return this;
}
