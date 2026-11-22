// campaign_leaf_5fff20.cpp -- thiscall method at VA 0x10efff20: passes its argument to the method at
// VA 0x10f115c0 on the object at 0x154 and returns true. The class and method names are invented.

class UnkType_10f115c0
{
public:
    void Unk_10f115c0(int Value);
};

class UnkType_10efff20
{
public:
    bool Unk_10efff20(int Value);

private:
    int unk_00[85];
    UnkType_10f115c0* unk_154;
};

// UnkType_10efff20::Unk_10efff20
bool UnkType_10efff20::Unk_10efff20(int Value)
{
    unk_154->Unk_10f115c0(Value);
    return true;
}
