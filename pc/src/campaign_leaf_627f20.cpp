// campaign_leaf_627f20.cpp -- thiscall method at VA 0x10f27f20: returns the result of the method at
// VA 0x10f28180 when its argument is zero, otherwise that of the method at VA 0x10f28140 given the
// argument. The class and method names are invented.

class UnkType_10f27f20
{
public:
    int Unk_10f28180();
    int Unk_10f28140(int Value);
    int Unk_10f27f20(int Value);
};

// UnkType_10f27f20::Unk_10f27f20
int UnkType_10f27f20::Unk_10f27f20(int Value)
{
    if ( !Value )
    {
        return Unk_10f28180();
    }
    return Unk_10f28140(Value);
}
