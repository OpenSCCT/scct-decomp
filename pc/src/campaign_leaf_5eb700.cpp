// campaign_leaf_5eb700.cpp -- thiscall method at VA 0x10eeb700: returns the result of the method at
// VA 0x10eec0f0 when its argument is zero, otherwise that of the method at VA 0x10eec0b0 given the
// argument. The class and method names are invented.

class UnkType_10eeb700
{
public:
    int Unk_10eec0f0();
    int Unk_10eec0b0(int Value);
    int Unk_10eeb700(int Value);
};

// UnkType_10eeb700::Unk_10eeb700
int UnkType_10eeb700::Unk_10eeb700(int Value)
{
    if ( !Value )
    {
        return Unk_10eec0f0();
    }
    return Unk_10eec0b0(Value);
}
