// campaign_leaf_5eb610.cpp -- thiscall method at VA 0x10eeb610: returns the result of the method at
// VA 0x10eebc10 when its argument is zero, otherwise that of the method at VA 0x10eebbd0 given the
// argument. The class and method names are invented.

class UnkType_10eeb610
{
public:
    int Unk_10eebc10();
    int Unk_10eebbd0(int Value);
    int Unk_10eeb610(int Value);
};

// UnkType_10eeb610::Unk_10eeb610
int UnkType_10eeb610::Unk_10eeb610(int Value)
{
    if ( !Value )
    {
        return Unk_10eebc10();
    }
    return Unk_10eebbd0(Value);
}
