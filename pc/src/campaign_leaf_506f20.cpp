// campaign_leaf_506f20.cpp -- method at VA 0x10e06f20: walks the pointer array at 0x08 (count at
// 0x0c) from the last entry down, calling virtual slot 0 of each entry's sub-object at 0x10 with
// its three arguments, and returns a false flag at the first false result, else a true flag. The
// class, method and member names are invented; the offsets and the slot are the binary's.

class UnkType_10e06f20_Result
{
public:
    UnkType_10e06f20_Result(bool InValue)
        : Value(InValue)
    {
    }

    bool Value;
};

class UnkType_10e06f20_Handler
{
public:
    virtual UnkType_10e06f20_Result VirtualSlot0(int Arg0, int Arg1, int Arg2);
};

class UnkType_10e06f20_Entry
{
public:
    unsigned char unk_00[0x10];
    UnkType_10e06f20_Handler unk_10;
};

class UnkType_10e06f20
{
public:
    UnkType_10e06f20_Result Unk_10e06f20(int Arg0, int Arg1, int Arg2);

    unsigned char unk_00[0x08];
    UnkType_10e06f20_Entry** unk_08;
    int unk_0c;
};

// UnkType_10e06f20::Unk_10e06f20
UnkType_10e06f20_Result UnkType_10e06f20::Unk_10e06f20(int Arg0, int Arg1, int Arg2)
{
    for ( int i = unk_0c - 1; i >= 0; i-- )
    {
        if ( !unk_08[i]->unk_10.VirtualSlot0(Arg0, Arg1, Arg2).Value )
        {
            return UnkType_10e06f20_Result(false);
        }
    }
    return UnkType_10e06f20_Result(true);
}
