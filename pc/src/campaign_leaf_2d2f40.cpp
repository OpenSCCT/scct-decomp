// campaign_leaf_2d2f40.cpp -- a member function at VA 0x10bd2f40 that takes the object returned by
// the member at VA 0x10a037c0 and returns bit 2 of its flags at 0x984, or 0 when there is none. The
// class, method and member names are invented; the offsets and addresses are the binary's.

class UnkType_10a037c0_Result
{
public:
    unsigned char unk_000[0x984];
    unsigned int unk_984;
};

class UnkType_10bd2f40
{
public:
    UnkType_10a037c0_Result* Unk_10a037c0();
    unsigned int Unk_10bd2f40();
};

// UnkType_10bd2f40::Unk_10bd2f40
unsigned int UnkType_10bd2f40::Unk_10bd2f40()
{
    UnkType_10a037c0_Result* Result = Unk_10a037c0();
    if ( Result )
    {
        return ( Result->unk_984 >> 2 ) & 1;
    }
    return 0;
}
