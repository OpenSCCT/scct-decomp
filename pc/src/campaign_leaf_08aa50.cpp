// campaign_leaf_08aa50.cpp -- one function at file offset 0x8aa50, preferred VA 0x1098aa50. It
// stores in its third argument the three products of its second argument with the three floats of
// its first argument. It has no this pointer. The class, method and parameter names are invented;
// the offset and the bytes are the binary's.

class UnkType_1098aa50
{
public:
    static void UnkScale(const float *Vec, float Scale, float *Out);
};

// UnkType_1098aa50::UnkScale
void UnkType_1098aa50::UnkScale(const float *Vec, float Scale, float *Out)
{
    Out[0] = Scale * Vec[0];
    Out[1] = Scale * Vec[1];
    Out[2] = Scale * Vec[2];
}
