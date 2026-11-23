// campaign_leaf_359a60.cpp -- one function at file offset 0x359a60, preferred VA 0x10c59a60. It
// calls the method at 0x10c566e0 with Arg, clears the word at 0x58c and, through the object at
// 0x57c and its object at 0x288, sets bit 0 of that object's word at 0x40 when the byte at 0x45c
// is 2 and clears it otherwise. The class, method, member and parameter names are invented; the
// offsets and the bytes are the binary's.

class UnkType_10c59a60_Target
{
public:
    unsigned char unk_0[0x40];
    unsigned int unk_40;
};

class UnkType_10c59a60_Owner
{
public:
    unsigned char unk_0[0x288];
    UnkType_10c59a60_Target* unk_288;
};

class UnkType_10c59a60
{
public:
    void Unk_10c566e0(int Arg);
    void Unk_10c59a60(int Arg);

    unsigned char unk_0[0x45c];
    unsigned char unk_45c;
    unsigned char unk_45d[0x11f];
    UnkType_10c59a60_Owner* unk_57c;
    unsigned char unk_580[0xc];
    int unk_58c;
};

// UnkType_10c59a60::Unk_10c59a60
void UnkType_10c59a60::Unk_10c59a60(int Arg)
{
    Unk_10c566e0(Arg);
    unk_58c = 0;
    if ( unk_45c == 2 )
    {
        if ( unk_57c != 0 && unk_57c->unk_288 != 0 )
        {
            unk_57c->unk_288->unk_40 |= 1;
        }
    }
    else
    {
        if ( unk_57c != 0 && unk_57c->unk_288 != 0 )
        {
            unk_57c->unk_288->unk_40 &= ~1;
        }
    }
}
