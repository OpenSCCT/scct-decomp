// campaign_leaf_271ee0.cpp -- a free function at VA 0x10b71ee0: when its argument is not null it
// calls the members at VA 0x10b71de0, VA 0x10b71e70 and VA 0x10b71c80 of its object, in that order.
// The class, function and parameter names are invented; the addresses are the binary's.

class UnkType_10b71ee0
{
public:
    void Unk_10b71de0();
    void Unk_10b71e70();
    void Unk_10b71c80();
};

// Unk_10b71ee0
void Unk_10b71ee0(UnkType_10b71ee0* Item)
{
    if ( Item )
    {
        Item->Unk_10b71de0();
        Item->Unk_10b71e70();
        Item->Unk_10b71c80();
    }
}
