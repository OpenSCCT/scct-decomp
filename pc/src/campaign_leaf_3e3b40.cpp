// campaign_leaf_3e3b40.cpp -- a member function at VA 0x10ce3b40 that calls the member at VA
// 0x10cdfeb0 and then, when the pointer at 0x28 is not null, the member at VA 0x10cd7a60 of the
// object it points to. The class, method and member names are invented; the offsets and addresses
// are the binary's.

class UnkType_10cd7a60
{
public:
    void Unk_10cd7a60();
};

class UnkType_10ce3b40
{
public:
    void Unk_10cdfeb0();
    void Unk_10ce3b40();

private:
    unsigned char unk_00[0x28];
    UnkType_10cd7a60* unk_28;
};

// UnkType_10ce3b40::Unk_10ce3b40
void UnkType_10ce3b40::Unk_10ce3b40()
{
    Unk_10cdfeb0();
    if ( unk_28 )
    {
        unk_28->Unk_10cd7a60();
    }
}
