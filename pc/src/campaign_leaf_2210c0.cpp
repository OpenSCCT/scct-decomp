// campaign_leaf_2210c0.cpp -- a member function at VA 0x10b210c0 that returns 1 when the pointer at
// 0x40 is not null and the member at VA 0x10b225e0 of its object returns false, and 0 otherwise.
// The class, method and member names are invented; the offsets and addresses are the binary's.

class UnkType_10b225e0
{
public:
    bool Unk_10b225e0();
};

class UnkType_10b210c0
{
public:
    int Unk_10b210c0();

private:
    unsigned char unk_00[0x40];
    UnkType_10b225e0* unk_40;
};

// UnkType_10b210c0::Unk_10b210c0
int UnkType_10b210c0::Unk_10b210c0()
{
    if ( unk_40 && !unk_40->Unk_10b225e0() )
    {
        return 1;
    }
    return 0;
}
