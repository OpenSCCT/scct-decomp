// campaign_leaf_2f6b40.cpp -- method at VA 0x10bf6b40: calls the method at VA 0x10bf8d90; then, when
// the object at 0x48c is set, stores 0.1 at its 0x2b8, the three floats (2, 0.5, 0.5) at its 0x2c0
// and clears bit 0 of its word at 0x2d0. The class, member and method names are invented; the
// offsets and the address are the binary's.

class UnkType_10bf6b40_Vector
{
public:
    UnkType_10bf6b40_Vector(float First, float Second, float Third)
        : unk_00(First), unk_04(Second), unk_08(Third)
    {
    }

    float unk_00;
    float unk_04;
    float unk_08;
};

class UnkType_10bf6b40_48c
{
public:
    unsigned char unk_00[0x2b8];
    float unk_2b8;
    unsigned char unk_2bc[0x2c0 - 0x2bc];
    UnkType_10bf6b40_Vector unk_2c0;
    unsigned char unk_2cc[0x2d0 - 0x2cc];
    unsigned int unk_2d0 : 1;
};

class UnkType_10bf6b40
{
public:
    void Unk_10bf6b40();
    void Unk_10bf8d90();

private:
    unsigned char unk_00[0x48c];
    UnkType_10bf6b40_48c* unk_48c;
};

// UnkType_10bf6b40::Unk_10bf6b40
void UnkType_10bf6b40::Unk_10bf6b40()
{
    Unk_10bf8d90();
    if ( unk_48c )
    {
        unk_48c->unk_2b8 = 0.1f;
        unk_48c->unk_2c0 = UnkType_10bf6b40_Vector(2.0f, 0.5f, 0.5f);
        unk_48c->unk_2d0 = 0;
    }
}
