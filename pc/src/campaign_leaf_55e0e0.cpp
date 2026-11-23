// campaign_leaf_55e0e0.cpp -- thiscall method at VA 0x10e5e0e0: passes the object it is given to
// the method at VA 0x10e6d2a0 on the same object, then copies the member at 0x18 into that object's
// member at 0x04. The class and method names are invented.

struct UnkType_10e5e0e0_Arg
{
    int unk_00;
    int unk_04;
};

class UnkType_10e5e0e0
{
public:
    void Unk_10e6d2a0(UnkType_10e5e0e0_Arg* Object);
    void Unk_10e5e0e0(UnkType_10e5e0e0_Arg* Object);

private:
    int unk_00[6];
    int unk_18;
};

// UnkType_10e5e0e0::Unk_10e5e0e0
void UnkType_10e5e0e0::Unk_10e5e0e0(UnkType_10e5e0e0_Arg* Object)
{
    Unk_10e6d2a0(Object);
    Object->unk_04 = unk_18;
}
