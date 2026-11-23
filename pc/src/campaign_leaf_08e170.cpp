// campaign_leaf_08e170.cpp -- method at VA 0x1098e170: unless the value at 0x08 equals the value at
// 0x0c of the object the pointer at 0x00 points to, passes it to the method at VA 0x10d01cf0 of
// that object; then stores the value at 0x04 at 0x00 of that object. The class, member and method
// names are invented; the offsets and the address are the binary's.

class UnkType_1098e170_10d01cf0
{
public:
    void Unk_10d01cf0(int Value);

    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

class UnkType_1098e170
{
public:
    void Unk_1098e170();

private:
    UnkType_1098e170_10d01cf0* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_1098e170::Unk_1098e170
void UnkType_1098e170::Unk_1098e170()
{
    if ( unk_08 != unk_00->unk_0c )
    {
        unk_00->Unk_10d01cf0(unk_08);
    }
    unk_00->unk_00 = unk_04;
}
