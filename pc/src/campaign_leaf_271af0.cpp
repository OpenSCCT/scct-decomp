// campaign_leaf_271af0.cpp -- a free function at VA 0x10b71af0: when its first argument is not null
// it passes the second to that object's member at VA 0x10d30670 and returns the int at 0x08 of the
// result, or 0 when either is null. The class, function and member names are invented; the offsets
// and addresses are the binary's.

class UnkType_10d30670_Result
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10d30670
{
public:
    UnkType_10d30670_Result* Unk_10d30670(int Key);
};

// Unk_10b71af0
int Unk_10b71af0(UnkType_10d30670* Table, int Key)
{
    if ( Table )
    {
        UnkType_10d30670_Result* Result = Table->Unk_10d30670(Key);
        if ( Result )
        {
            return Result->unk_08;
        }
    }
    return 0;
}
