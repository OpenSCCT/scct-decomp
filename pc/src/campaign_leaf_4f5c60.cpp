// campaign_leaf_4f5c60.cpp -- method at VA 0x10df5c60: passes its argument to the method at VA
// 0x10df9080 of its member at 0x844 and to the method at VA 0x10dfa760 of its member at 0x48, and
// returns true when both return true. The class, method and parameter names are invented; the
// offsets and the addresses are the binary's.

class UnkType_10df5c60;

class UnkType_10df5c60_Stream;

class UnkType_10df5c60_Part48
{
public:
    bool Unk_10dfa760(int Arg);
};

class UnkType_10df5c60_Part844
{
public:
    bool Unk_10df9080(int Arg);
};

class UnkType_10df5c60
{
public:
    bool Unk_10df5c60(int Arg);

    unsigned char unk_00[0x48];
    UnkType_10df5c60_Part48 unk_48;
    unsigned char unk_49[0x844 - 0x49];
    UnkType_10df5c60_Part844 unk_844;
};

// UnkType_10df5c60::Unk_10df5c60
bool UnkType_10df5c60::Unk_10df5c60(int Arg)
{
    bool Result = true;
    Result &= unk_844.Unk_10df9080(Arg);
    Result &= unk_48.Unk_10dfa760(Arg);
    return Result;
}
