// campaign_leaf_600410.cpp -- thiscall method at VA 0x10f00410: passes its argument to the method
// at VA 0x10f0bf90 on the object at 0x158 and returns true. The class and method names are
// invented.

class UnkType_10f0bf90
{
public:
    void Unk_10f0bf90(int Value);
};

class UnkType_10f00410
{
public:
    bool Unk_10f00410(int Value);

private:
    int unk_00[86];
    UnkType_10f0bf90* unk_158;
};

// UnkType_10f00410::Unk_10f00410
bool UnkType_10f00410::Unk_10f00410(int Value)
{
    unk_158->Unk_10f0bf90(Value);
    return true;
}
