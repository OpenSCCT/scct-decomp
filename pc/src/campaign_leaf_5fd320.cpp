// campaign_leaf_5fd320.cpp -- thiscall method at VA 0x10efd320: passes its two arguments to the
// method at VA 0x10efcac0 on the member at 0x30 and returns true. The class and method names are
// invented.

class UnkType_10efcac0
{
public:
    void Unk_10efcac0(int First, int Second);
};

class UnkType_10efd320
{
public:
    bool Unk_10efd320(int First, int Second);

private:
    int unk_00[12];
    UnkType_10efcac0 unk_30;
};

// UnkType_10efd320::Unk_10efd320
bool UnkType_10efd320::Unk_10efd320(int First, int Second)
{
    unk_30.Unk_10efcac0(First, Second);
    return true;
}
