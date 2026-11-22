// campaign_leaf_46c1a0.cpp -- thiscall at VA 0x10d6c1a0: calls the method at VA 0x10d78e10 of its
// argument with the dwords at offsets 0 and 4, and returns the argument. All names are invented.

class UnkType_10d78e10
{
public:
    void Unk_10d78e10(int First, int Second);
};

class UnkType_10d6c1a0
{
public:
    UnkType_10d78e10* Unk_10d6c1a0(UnkType_10d78e10* Object);

private:
    int unk_00;
    int unk_04;
};

// UnkType_10d6c1a0::Unk_10d6c1a0
UnkType_10d78e10* UnkType_10d6c1a0::Unk_10d6c1a0(UnkType_10d78e10* Object)
{
    Object->Unk_10d78e10(unk_00, unk_04);
    return Object;
}
