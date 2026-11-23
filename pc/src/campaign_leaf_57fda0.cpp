// campaign_leaf_57fda0.cpp -- thiscall method at VA 0x10e7fda0: walks the array of object pointers
// at 0x104 and sums the member at 0xe8 of every object whose name (third virtual method) the cdecl
// function at VA 0x10dffc00 reports equal to "FastConstraintSolver". The class and method names
// are invented.

int Unk_10dffc00(const char* First, const char* Second);

class UnkType_10e7fda0_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual const char* VirtualSlot2();

    int unk_04[0xe4 / 4];
    int unk_e8;
};

struct UnkType_10e7fda0_Array
{
    UnkType_10e7fda0_Item** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e7fda0_Array::Begin
    UnkType_10e7fda0_Item** Begin()
    {
        return unk_00;
    }

    // UnkType_10e7fda0_Array::End
    UnkType_10e7fda0_Item** End()
    {
        return unk_00 + unk_04;
    }
};

class UnkType_10e7fda0
{
public:
    int Unk_10e7fda0();

private:
    int unk_00[0x104 / 4];
    UnkType_10e7fda0_Array unk_104;
};

// UnkType_10e7fda0::Unk_10e7fda0
int UnkType_10e7fda0::Unk_10e7fda0()
{
    int Total = 0;
    for ( UnkType_10e7fda0_Item** Item = unk_104.Begin(); Item < unk_104.End(); Item++ )
    {
        if ( Unk_10dffc00((*Item)->VirtualSlot2(), "FastConstraintSolver") == 0 )
        {
            Total += (*Item)->unk_e8;
        }
    }
    return Total;
}
