// campaign_leaf_46bfc0.cpp -- one function at file offset 0x46bfc0, preferred VA 0x10d6bfc0. It
// returns 1 when the floats at 0x0, 0x4 and 0x8 equal its three arguments. The class, method,
// member and parameter names are invented; the offsets and the bytes are the binary's.

class UnkType_10d6bfc0
{
public:
    int Unk_10d6bfc0(float First, float Second, float Third) const;

    float unk_0;
    float unk_4;
    float unk_8;
};

// UnkType_10d6bfc0::Unk_10d6bfc0
int UnkType_10d6bfc0::Unk_10d6bfc0(float First, float Second, float Third) const
{
    return unk_0 == First && unk_4 == Second && unk_8 == Third;
}
