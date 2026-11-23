// campaign_leaf_2ef7f0.cpp -- method at VA 0x10bef7f0 taking one argument: passes it to the method
// at VA 0x10bf1670 of each of the objects at 0x404 and 0x408 that is set, then does the same for
// the objects at 0x404 and 0x408 of the object at 0x40c when that is set. The class, member and
// method names are invented; the offsets and the address are the binary's.

class UnkType_10bef7f0_Item
{
public:
    void Unk_10bf1670(int Value);
};

class UnkType_10bef7f0
{
public:
    void Unk_10bef7f0(int Value);

private:
    unsigned char unk_00[0x404];
    UnkType_10bef7f0_Item* unk_404;
    UnkType_10bef7f0_Item* unk_408;
    UnkType_10bef7f0* unk_40c;
};

// UnkType_10bef7f0::Unk_10bef7f0
void UnkType_10bef7f0::Unk_10bef7f0(int Value)
{
    if ( unk_404 )
    {
        unk_404->Unk_10bf1670(Value);
    }
    if ( unk_408 )
    {
        unk_408->Unk_10bf1670(Value);
    }
    if ( unk_40c )
    {
        if ( unk_40c->unk_404 )
        {
            unk_40c->unk_404->Unk_10bf1670(Value);
        }
        if ( unk_40c->unk_408 )
        {
            unk_40c->unk_408->Unk_10bf1670(Value);
        }
    }
}
