// campaign_leaf_2d7cd0.cpp -- a member function at VA 0x10bd7cd0 that calls two other members on
// the same object, at VA 0x10a93130 and VA 0x10bd77e0. The class and method names are invented;
// the addresses are the binary's.

class UnkType_10bd7cd0
{
public:
    void Unk_10a93130();
    void Unk_10bd77e0();
    void Unk_10bd7cd0();
};

// UnkType_10bd7cd0::Unk_10bd7cd0
void UnkType_10bd7cd0::Unk_10bd7cd0()
{
    Unk_10a93130();
    Unk_10bd77e0();
}
