// campaign_leaf_5eb6a0.cpp -- thiscall method at VA 0x10eeb6a0: returns the result of the method at
// VA 0x10eebeb0 when its argument is zero, otherwise that of the method at VA 0x10eebe70 given the
// argument. The class and method names are invented.

class UnkType_10eeb6a0
{
public:
    int Unk_10eebeb0();
    int Unk_10eebe70(int Value);
    int Unk_10eeb6a0(int Value);
};

// UnkType_10eeb6a0::Unk_10eeb6a0
int UnkType_10eeb6a0::Unk_10eeb6a0(int Value)
{
    if ( !Value )
    {
        return Unk_10eebeb0();
    }
    return Unk_10eebe70(Value);
}
