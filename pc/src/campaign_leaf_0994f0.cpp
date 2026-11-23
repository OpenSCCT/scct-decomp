// campaign_leaf_0994f0.cpp -- method at VA 0x109994f0: calls the method at VA 0x1098dc80, then, if
// the pointer at 0x3e8 is set, the method at VA 0x1099aef0 on the object it points to with this
// object. The class, member and method names are invented; the offsets and the addresses are the
// binary's.

class UnkType_109994f0;

class UnkType_109994f0_1099aef0
{
public:
    void Unk_1099aef0(UnkType_109994f0* Owner);
};

class UnkType_109994f0
{
public:
    void Unk_109994f0();
    void Unk_1098dc80();

private:
    unsigned char unk_000[0x3e8];
    UnkType_109994f0_1099aef0* unk_3e8;
};

// UnkType_109994f0::Unk_109994f0
void UnkType_109994f0::Unk_109994f0()
{
    Unk_1098dc80();
    if ( unk_3e8 )
    {
        unk_3e8->Unk_1099aef0(this);
    }
}
