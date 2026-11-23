// campaign_leaf_1eea70.cpp -- thiscall method at VA 0x10aeea70. It returns 0 when virtual slot 4
// gives a different value for the other object than for this one; otherwise 1 when the three
// vectors at 0x10, 0x1c and 0x28 of the two objects are within 0.1 of each other (function at VA
// 0x10971480), else 0. The class, method and member names are invented.

class UnkType_10aeea70_Vector
{
public:
    float X;
    float Y;
    float Z;
};

int Unk_10971480(const UnkType_10aeea70_Vector& First, const UnkType_10aeea70_Vector& Second,
                 float Tolerance);

class UnkType_10aeea70
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual int VirtualSlot4();

    int Unk_10aeea70(UnkType_10aeea70* Other);

private:
    int unk_04;
    int unk_08;
    int unk_0c;
    UnkType_10aeea70_Vector unk_10;
    UnkType_10aeea70_Vector unk_1c;
    UnkType_10aeea70_Vector unk_28;
};

// UnkType_10aeea70::Unk_10aeea70
int UnkType_10aeea70::Unk_10aeea70(UnkType_10aeea70* Other)
{
    int Result = 0;
    if ( VirtualSlot4() == Other->VirtualSlot4() )
    {
        Result = Unk_10971480(unk_10, Other->unk_10, 0.1f)
                 && Unk_10971480(unk_1c, Other->unk_1c, 0.1f)
                 && Unk_10971480(unk_28, Other->unk_28, 0.1f);
    }
    return Result;
}
