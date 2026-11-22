// campaign_leaf_6281c0.cpp -- stdcall function at VA 0x10f281c0: when the object is not null,
// returns the result of the method at VA 0x10f290b0 on it given the second argument; otherwise
// false. All names are invented.

class UnkType_10f290b0
{
public:
    bool Unk_10f290b0(int Value);
};

// Unk_10f281c0
bool __stdcall Unk_10f281c0(UnkType_10f290b0* Object, int Value)
{
    if ( Object )
    {
        return Object->Unk_10f290b0(Value);
    }
    return false;
}
