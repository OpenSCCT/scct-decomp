// campaign_leaf_38dad0.cpp -- one function at file offset 0x38dad0, preferred VA 0x10c8dad0. It
// returns a copy of this four-float object with every component multiplied by Scale. The class,
// method, member and parameter names are invented; the offsets and the bytes are the binary's.

class UnkType_10c8dad0
{
public:
    UnkType_10c8dad0 Unk_10c8dad0(float Scale) const;

    float unk_0;
    float unk_4;
    float unk_8;
    float unk_c;
};

// UnkType_10c8dad0::Unk_10c8dad0
UnkType_10c8dad0 UnkType_10c8dad0::Unk_10c8dad0(float Scale) const
{
    UnkType_10c8dad0 Result = *this;

    Result.unk_0 *= Scale;
    Result.unk_4 *= Scale;
    Result.unk_8 *= Scale;
    Result.unk_c *= Scale;
    return Result;
}
