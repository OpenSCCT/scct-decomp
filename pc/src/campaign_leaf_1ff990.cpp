// campaign_leaf_1ff990.cpp -- constructor at VA 0x10aff990. It runs the empty base constructor at
// VA 0x10d9d560, then builds the two tables at 0x04 and 0x158: each clears its flag at 0x08, the
// flag of each of its 40 eight-byte entries and its flag at 0x150. The class, method and member
// names are invented; the table's lookup is named after what its uses show.

class UnkType_10aff990_Base
{
public:
    UnkType_10aff990_Base();
};

struct UnkType_10aff990_Entry
{
    // UnkType_10aff990_Entry::UnkType_10aff990_Entry
    UnkType_10aff990_Entry()
        : unk_0(0)
    {
    }

    bool unk_0;
    int unk_4;
};

class UnkType_10aff990_Slots
{
public:
    // UnkType_10aff990_Slots::UnkType_10aff990_Slots
    UnkType_10aff990_Slots()
        : unk_144(0)
    {
    }

    UnkType_10aff990_Entry unk_000[40];
    int unk_140;
    bool unk_144;
};

class UnkType_10aff990_Table
{
public:
    // UnkType_10aff990_Table::UnkType_10aff990_Table
    UnkType_10aff990_Table()
        : unk_8(0)
    {
    }

    // UnkType_10aff990_Table::Unk_Lookup
    bool Unk_Lookup(unsigned int Id)
    {
        bool bFound;
        UnkType_10aff990_Entry& Entry = unk_c.unk_000[Id % 40];
        if ( Entry.unk_0 )
        {
            Entry.unk_0 = true;
            unk_0 = Entry.unk_4;
            bFound = true;
        }
        else
        {
            bFound = false;
        }
        if ( Id >= 20 )
        {
            unk_c.unk_000[(Id - 20) % 40].unk_0 = false;
        }
        return bFound;
    }

private:
    int unk_0;
    int unk_4;
    bool unk_8;
    UnkType_10aff990_Slots unk_c;
};

class UnkType_10aff990 : public UnkType_10aff990_Base
{
public:
    UnkType_10aff990();

private:
    int unk_000;
    UnkType_10aff990_Table unk_004;
    UnkType_10aff990_Table unk_158;
};

// UnkType_10aff990::UnkType_10aff990
UnkType_10aff990::UnkType_10aff990()
{
}
