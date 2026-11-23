// campaign_leaf_506ec0.cpp -- method at VA 0x10e06ec0: walks the pointer array at 0x0c (count at
// 0x10) from the last entry down, calling virtual slot 0 of each entry's sub-object at 0x0c with
// its five arguments, and returns a false flag at the first false result, else a true flag. The
// class, method and member names are invented; the offsets and the slot are the binary's.

class UnkType_10e06ec0_Result
{
public:
    UnkType_10e06ec0_Result(bool InValue)
        : Value(InValue)
    {
    }

    bool Value;
};

class UnkType_10e06ec0_Handler
{
public:
    virtual UnkType_10e06ec0_Result VirtualSlot0(int Arg0, int Arg1, int Arg2, int Arg3, int Arg4);
};

class UnkType_10e06ec0_Entry
{
public:
    unsigned char unk_00[0x0c];
    UnkType_10e06ec0_Handler unk_0c;
};

class UnkType_10e06ec0
{
public:
    UnkType_10e06ec0_Result Unk_10e06ec0(int Arg0, int Arg1, int Arg2, int Arg3, int Arg4);

    unsigned char unk_00[0x0c];
    UnkType_10e06ec0_Entry** unk_0c;
    int unk_10;
};

// UnkType_10e06ec0::Unk_10e06ec0
UnkType_10e06ec0_Result UnkType_10e06ec0::Unk_10e06ec0(int Arg0, int Arg1, int Arg2, int Arg3,
                                                       int Arg4)
{
    for ( int i = unk_10 - 1; i >= 0; i-- )
    {
        if ( !unk_0c[i]->unk_0c.VirtualSlot0(Arg0, Arg1, Arg2, Arg3, Arg4).Value )
        {
            return UnkType_10e06ec0_Result(false);
        }
    }
    return UnkType_10e06ec0_Result(true);
}
