// campaign_leaf_2514a0.cpp -- a member function at VA 0x10b514a0 that calls the member at VA
// 0x10b76120 of the object at 0x14 and the member at VA 0x10d2f530 of the object the pointer at
// 0x08 refers to, clears the ints at 0x0c and 0x10 and returns true. The class, method and member
// names are invented; the offsets and addresses are the binary's.

class UnkType_10b76120
{
public:
    void Unk_10b76120();
};

class UnkType_10d2f530
{
public:
    void Unk_10d2f530();
};

class UnkType_10b514a0
{
public:
    bool Unk_10b514a0();

private:
    int unk_00;
    int unk_04;
    UnkType_10d2f530* unk_08;
    int unk_0c;
    int unk_10;
    UnkType_10b76120 unk_14;
};

// UnkType_10b514a0::Unk_10b514a0
bool UnkType_10b514a0::Unk_10b514a0()
{
    unk_14.Unk_10b76120();
    unk_08->Unk_10d2f530();
    unk_0c = 0;
    unk_10 = 0;
    return true;
}
