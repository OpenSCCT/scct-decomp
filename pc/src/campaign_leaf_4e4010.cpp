// campaign_leaf_4e4010.cpp -- method at VA 0x10de4010: asks the object at 0xc for a rate (the
// method at VA 0x10dc8090) and a base (the method at VA 0x10dc80a0); returns 0 when the rate is
// -1, and otherwise Offset plus the base, times 1000, over an eighth of the rate. The class,
// member, method and parameter names are invented; the offsets, the constants and the addresses
// are the binary's.

class UnkType_10de4010_Source
{
public:
    unsigned int Unk_10dc8090();
    unsigned short Unk_10dc80a0();
};

class UnkType_10de4010
{
public:
    float Unk_10de4010(unsigned short Offset);

private:
    char unk_0[0xc];
    UnkType_10de4010_Source* unk_c;
};

// UnkType_10de4010::Unk_10de4010
float UnkType_10de4010::Unk_10de4010(unsigned short Offset)
{
    unsigned int Rate = unk_c->Unk_10dc8090();
    unsigned int Base = unk_c->Unk_10dc80a0();

    if ( Rate != 0xffffffff )
    {
        return (unsigned int)( Offset + Base ) * 1000.0f / ( Rate * 0.125f );
    }
    return 0.0f;
}
