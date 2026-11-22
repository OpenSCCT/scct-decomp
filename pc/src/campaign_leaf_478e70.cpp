// campaign_leaf_478e70.cpp -- one function at file offset 0x478e70, preferred VA 0x10d78e70. It
// returns 1 when the floats at 0x0 and 0x4 equal its two arguments. The class, method, member
// and parameter names are invented; the offsets and the bytes are the binary's.

class UnkType_10d78e70
{
public:
    int Unk_10d78e70(float First, float Second) const;

    float unk_0;
    float unk_4;
};

// UnkType_10d78e70::Unk_10d78e70
int UnkType_10d78e70::Unk_10d78e70(float First, float Second) const
{
    return unk_0 == First && unk_4 == Second;
}
