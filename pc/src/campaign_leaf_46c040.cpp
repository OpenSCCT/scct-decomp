// campaign_leaf_46c040.cpp -- one function at file offset 0x46c040, preferred VA 0x10d6c040. It
// returns 1 when each of the floats at 0x0, 0x4 and 0x8 is below Limit. The class, method,
// member and parameter names are invented; the offsets and the bytes are the binary's.

class UnkType_10d6c040
{
public:
    int Unk_10d6c040(const float& Limit) const;

    float unk_0;
    float unk_4;
    float unk_8;
};

// UnkType_10d6c040::Unk_10d6c040
int UnkType_10d6c040::Unk_10d6c040(const float& Limit) const
{
    return unk_0 < Limit && unk_4 < Limit && unk_8 < Limit;
}
