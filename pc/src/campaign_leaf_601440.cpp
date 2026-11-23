// campaign_leaf_601440.cpp -- thiscall method at VA 0x10f01440: passes its argument to the method
// at VA 0x10f1a5d0 on the object at 0x15c and returns true. The class and method names are
// invented.

class UnkType_10f1a5d0
{
public:
    void Unk_10f1a5d0(int Value);
};

class UnkType_10f01440
{
public:
    bool Unk_10f01440(int Value);

private:
    int unk_00[87];
    UnkType_10f1a5d0* unk_15c;
};

// UnkType_10f01440::Unk_10f01440
bool UnkType_10f01440::Unk_10f01440(int Value)
{
    unk_15c->Unk_10f1a5d0(Value);
    return true;
}
