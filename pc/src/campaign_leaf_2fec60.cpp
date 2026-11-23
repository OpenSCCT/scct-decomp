// campaign_leaf_2fec60.cpp -- method at VA 0x10bfec60: makes a function-local static name
// L"EReviveSyringe" on first use (through the name constructor at VA 0x10cd4790 with 2); returns 0
// unless bit 0 of the word at 0x2e8 is set; otherwise returns whether the method at VA 0x10c267c0
// of the object reached through 0x4a0 and 0x6dc of the object at 0x6c accepts that name, trying
// next the object that object's method at VA 0x10a037c0 returns. The class, member and method names
// are invented; the offsets, the string and the addresses are the binary's.

class UnkType_10bfec60_Name
{
public:
    UnkType_10bfec60_Name(const unsigned short* Text, int FindType);

private:
    int unk_00;
};

class UnkType_10bfec60_6dc
{
public:
    int Unk_10c267c0(UnkType_10bfec60_Name Name);
};

class UnkType_10bfec60_4a0
{
public:
    unsigned char unk_00[0x6dc];
    UnkType_10bfec60_6dc* unk_6dc;
};

class UnkType_10bfec60_6c
{
public:
    UnkType_10bfec60_6c* Unk_10a037c0();

    unsigned char unk_00[0x4a0];
    UnkType_10bfec60_4a0* unk_4a0;
};

class UnkType_10bfec60
{
public:
    int Unk_10bfec60();

private:
    unsigned char unk_00[0x6c];
    UnkType_10bfec60_6c* unk_6c;
    unsigned char unk_70[0x2e8 - 0x70];
    int unk_2e8;
};

// UnkType_10bfec60::Unk_10bfec60
int UnkType_10bfec60::Unk_10bfec60()
{
    UnkType_10bfec60_6c* Owner = unk_6c;
    static UnkType_10bfec60_Name ReviveSyringe(L"EReviveSyringe", 2);
    if ( unk_2e8 & 1 )
    {
        if ( Owner->unk_4a0->unk_6dc->Unk_10c267c0(ReviveSyringe) )
        {
            return 1;
        }
        UnkType_10bfec60_6c* Next = Owner->Unk_10a037c0();
        return Next->unk_4a0->unk_6dc->Unk_10c267c0(ReviveSyringe) != 0;
    }
    return 0;
}
