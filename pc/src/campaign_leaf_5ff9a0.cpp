// campaign_leaf_5ff9a0.cpp -- thiscall method at VA 0x10eff9a0: passes its argument to the method
// at VA 0x10f146c0 on the object at 0x150 and returns true. The class and method names are
// invented.

class UnkType_10f146c0
{
public:
    void Unk_10f146c0(int Value);
};

class UnkType_10eff9a0
{
public:
    bool Unk_10eff9a0(int Value);

private:
    int unk_00[84];
    UnkType_10f146c0* unk_150;
};

// UnkType_10eff9a0::Unk_10eff9a0
bool UnkType_10eff9a0::Unk_10eff9a0(int Value)
{
    unk_150->Unk_10f146c0(Value);
    return true;
}
