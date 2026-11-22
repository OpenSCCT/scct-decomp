// campaign_leaf_5eb5e0.cpp -- thiscall method at VA 0x10eeb5e0: returns the result of the method at
// VA 0x10eeb980 when its argument is zero, otherwise that of the method at VA 0x10eeb940 given the
// argument. The class and method names are invented.

class UnkType_10eeb5e0
{
public:
    int Unk_10eeb980();
    int Unk_10eeb940(int Value);
    int Unk_10eeb5e0(int Value);
};

// UnkType_10eeb5e0::Unk_10eeb5e0
int UnkType_10eeb5e0::Unk_10eeb5e0(int Value)
{
    if ( !Value )
    {
        return Unk_10eeb980();
    }
    return Unk_10eeb940(Value);
}
