// campaign_leaf_316dd0.cpp -- a member function at VA 0x10c16dd0 that calls the member at VA
// 0x1098dc80 and then, when the pointer at 0x9c8 of the object the pointer at 0x78 refers to is not
// null, passes this to the member at VA 0x10bdee20 of that pointer's object. The class, method and
// member names are invented; the offsets and addresses are the binary's.

class UnkType_10c16dd0;

class UnkType_10bdee20
{
public:
    void Unk_10bdee20(UnkType_10c16dd0* Item);
};

class UnkType_10c16dd0_Owner
{
public:
    unsigned char unk_000[0x9c8];
    UnkType_10bdee20* unk_9c8;
};

class UnkType_10c16dd0
{
public:
    void Unk_1098dc80();
    void Unk_10c16dd0();

private:
    unsigned char unk_00[0x78];
    UnkType_10c16dd0_Owner* unk_78;
};

// UnkType_10c16dd0::Unk_10c16dd0
void UnkType_10c16dd0::Unk_10c16dd0()
{
    Unk_1098dc80();
    if ( unk_78->unk_9c8 )
    {
        unk_78->unk_9c8->Unk_10bdee20(this);
    }
}
