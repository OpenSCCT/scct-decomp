// campaign_leaf_4f3660.cpp -- method at VA 0x10df3660: fills a local object through the method at
// VA 0x10df3050 with its first argument and, when that succeeds, returns the local's method at VA
// 0x10d94df0 called with its second argument; otherwise returns false. The class, method and
// parameter names are invented; the addresses are the binary's.

class UnkType_10df3660_Local
{
public:
    UnkType_10df3660_Local();
    ~UnkType_10df3660_Local();
    bool Unk_10d94df0(int Arg);

    unsigned char unk_00[0x5c];
};

class UnkType_10df3660
{
public:
    bool Unk_10df3660(int Arg0, int Arg1);
    bool Unk_10df3050(UnkType_10df3660_Local* Local, int Arg);
};

// UnkType_10df3660::Unk_10df3660
bool UnkType_10df3660::Unk_10df3660(int Arg0, int Arg1)
{
    UnkType_10df3660_Local Local;
    if ( Unk_10df3050(&Local, Arg0) )
    {
        return Local.Unk_10d94df0(Arg1);
    }
    return false;
}
