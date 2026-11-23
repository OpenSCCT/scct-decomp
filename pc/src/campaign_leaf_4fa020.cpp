// campaign_leaf_4fa020.cpp -- method at VA 0x10dfa020: on entry 2 of the six 0x154-byte entries at
// 0x04, takes the value of the slot the argument selects in a ring of 40 eight-byte slots when that
// slot is set, clears the slot twenty places back, and returns whether a value was taken. The value
// type's destructor is the empty function at VA 0x10df4290. The class, method and member names are
// invented; the offsets and the address are the binary's.

class UnkType_10dfa020_Value
{
public:
    ~UnkType_10dfa020_Value();

    UnkType_10dfa020_Value operator=(const UnkType_10dfa020_Value& Other)
    {
        unk_00 = Other.unk_00;
        return *this;
    }

    int unk_00;
};

class UnkType_10dfa020_Slot
{
public:
    bool unk_00;
    UnkType_10dfa020_Value unk_04;
};

class UnkType_10dfa020_Entry
{
public:
    UnkType_10dfa020_Value unk_00;
    int unk_04;
    int unk_08;
    UnkType_10dfa020_Slot unk_0c[40];
    int unk_14c;
    int unk_150;
};

class UnkType_10dfa020
{
public:
    bool Unk_10dfa020(unsigned int Index);

    int unk_00;
    UnkType_10dfa020_Entry unk_04[6];
};

// UnkType_10dfa020::Unk_10dfa020
bool UnkType_10dfa020::Unk_10dfa020(unsigned int Index)
{
    bool Found;
    UnkType_10dfa020_Entry& Entry = unk_04[2];
    UnkType_10dfa020_Slot& Slot = Entry.unk_0c[Index % 40];
    if ( Slot.unk_00 )
    {
        Slot.unk_00 = true;
        Entry.unk_00 = Slot.unk_04;
        Found = true;
    }
    else
    {
        Found = false;
    }
    if ( Index >= 20 )
    {
        Entry.unk_0c[( Index - 20 ) % 40].unk_00 = false;
    }
    return Found;
}
