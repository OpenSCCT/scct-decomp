// campaign_leaf_586950.cpp -- thiscall method at VA 0x10e86950: walks the array of object pointers
// at 0xe4 and returns the first object whose name (member at 0x08) the cdecl function at VA
// 0x10dffc00 reports equal to the name it is given (result 0), or null. guess: a lookup by name
// with a string comparison. The class and method names are invented.

int Unk_10dffc00(const unsigned short* First, const unsigned short* Second);

struct UnkType_10e86950_Item
{
    int unk_00;
    int unk_04;
    const unsigned short* unk_08;
};

struct UnkType_10e86950_Array
{
    UnkType_10e86950_Item** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e86950_Array::Begin
    UnkType_10e86950_Item** Begin()
    {
        return unk_00;
    }

    // UnkType_10e86950_Array::End
    UnkType_10e86950_Item** End()
    {
        return unk_00 + unk_04;
    }
};

class UnkType_10e86950
{
public:
    UnkType_10e86950_Item* Unk_10e86950(const unsigned short* Name);

private:
    int unk_00[57];
    UnkType_10e86950_Array unk_e4;
};

// UnkType_10e86950::Unk_10e86950
UnkType_10e86950_Item* UnkType_10e86950::Unk_10e86950(const unsigned short* Name)
{
    for ( UnkType_10e86950_Item** Item = unk_e4.Begin(); Item < unk_e4.End(); Item++ )
    {
        const unsigned short* ItemName = (*Item)->unk_08;
        if ( Unk_10dffc00(ItemName, Name) == 0 )
        {
            return *Item;
        }
    }
    return 0;
}
