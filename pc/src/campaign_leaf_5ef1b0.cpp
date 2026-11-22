// campaign_leaf_5ef1b0.cpp -- thiscall method at VA 0x10eef1b0: passes its two arguments to the
// method at VA 0x10ef28a0 on the object at 0x0c and returns true. The class and method names are
// invented.

class UnkType_10ef28a0
{
public:
    void Unk_10ef28a0(int First, int Second);
};

class UnkType_10eef1b0
{
public:
    bool Unk_10eef1b0(int First, int Second);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_10ef28a0* unk_0c;
};

// UnkType_10eef1b0::Unk_10eef1b0
bool UnkType_10eef1b0::Unk_10eef1b0(int First, int Second)
{
    unk_0c->Unk_10ef28a0(First, Second);
    return true;
}
