// campaign_leaf_5885a0.cpp -- thiscall method at VA 0x10e885a0: walks the array of object pointers
// at 0x08 (count at 0x0c), passes its three arguments to the second virtual method of each object
// and returns the first nonzero result, or 0. The class and method names are invented.

class UnkType_10e885a0_Item
{
public:
    virtual void VirtualSlot0();
    virtual int VirtualSlot1(int First, int Second, int Third);
};

struct UnkType_10e885a0_Array
{
    UnkType_10e885a0_Item** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e885a0_Array::Begin
    UnkType_10e885a0_Item** Begin()
    {
        return unk_00;
    }

    // UnkType_10e885a0_Array::End
    UnkType_10e885a0_Item** End()
    {
        return unk_00 + unk_04;
    }
};

class UnkType_10e885a0
{
public:
    int Unk_10e885a0(int First, int Second, int Third);

private:
    int unk_00;
    int unk_04;
    UnkType_10e885a0_Array unk_08;
};

// UnkType_10e885a0::Unk_10e885a0
int UnkType_10e885a0::Unk_10e885a0(int First, int Second, int Third)
{
    for ( UnkType_10e885a0_Item** Item = unk_08.Begin(); Item < unk_08.End(); Item++ )
    {
        int Result = (*Item)->VirtualSlot1(First, Second, Third);
        if ( Result )
        {
            return Result;
        }
    }
    return 0;
}
