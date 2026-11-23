// campaign_leaf_349280.cpp -- one function at file offset 0x349280, preferred VA 0x10c49280. It
// sets bit 0 of Other's word at 0x46c, passes 0 to Other's method at 0x10995870, copies the words
// at 0x284 and 0x45c to Other, passes the first entry of the array at 0x47c to Other's method at
// 0x10a86090, links the two objects through 0x474 and Other's 0x478, copies the word at 0x410 of
// the object at 0x414 when that object's word at 0x45c is set, and calls Other's method at
// 0x10c48ee0. The class, method, member and parameter names are invented; the offsets and the
// bytes are the binary's.

class UnkType_10c49280
{
public:
    void Unk_10995870(int Value);
    void Unk_10a86090(void* Value);
    void Unk_10c48ee0();
    void Unk_10c49280(UnkType_10c49280* Other);

    unsigned char unk_0[0x284];
    int unk_284;
    unsigned char unk_288[0x188];
    int unk_410;
    UnkType_10c49280* unk_414;
    unsigned char unk_418[0x44];
    int unk_45c;
    unsigned char unk_460[0xc];
    int unk_46c;
    unsigned char unk_470[0x4];
    UnkType_10c49280* unk_474;
    UnkType_10c49280* unk_478;
    void** unk_47c;
};

// UnkType_10c49280::Unk_10c49280
void UnkType_10c49280::Unk_10c49280(UnkType_10c49280* Other)
{
    Other->unk_46c |= 1;
    Other->Unk_10995870(0);
    Other->unk_284 = unk_284;
    Other->unk_45c = unk_45c;
    Other->Unk_10a86090(unk_47c[0]);
    unk_474 = Other;
    Other->unk_478 = this;
    if ( unk_414 != 0 && unk_414->unk_45c != 0 )
    {
        unk_410 = unk_414->unk_410;
    }
    Other->Unk_10c48ee0();
}
