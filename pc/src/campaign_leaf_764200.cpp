// campaign_leaf_764200.cpp -- one function at file offset 0x764200, preferred VA 0x11064200. It
// returns 0 when the method at VA 0x11063820 rejects the record, when the method at VA 0x11063680
// finds nothing for the record's word at 0x4, or when the method at VA 0x11063890 rejects the
// member at 0x4 of what was found. Otherwise it passes the word at 0x1c of the block at 0x10 of
// the object at 0x4 and the address of the record's word at 0x4 to the method at VA 0x1106e6b0
// of the object at 0x70, and returns whether the method at VA 0x11063b30 accepts the record. The
// class, method and member names are invented; the offsets and the addresses are the binary's.

struct UnkType_11064200_Record
{
    int unk_0;
    int unk_4;
};

struct UnkType_11064200_Found
{
    int unk_0;
    int unk_4;
};

struct UnkType_11064200_Block
{
    unsigned char unk_0[0x1c];
    int unk_1c;
};

struct UnkType_11064200_Owner
{
    unsigned char unk_0[0x10];
    UnkType_11064200_Block unk_10;
};

class UnkType_11064200_Player
{
public:
    void Unk_1106e6b0(int Value, int* Key);
};

class UnkType_11064200
{
public:
    int Unk_11063820(UnkType_11064200_Record* Record);
    UnkType_11064200_Found* Unk_11063680(int Key);
    int Unk_11063890(int* Value);
    int Unk_11063b30(UnkType_11064200_Record* Record);
    int Unk_11064200(UnkType_11064200_Record* Record);

    int unk_0;
    UnkType_11064200_Owner* unk_4;
    unsigned char unk_8[0x70 - 0x8];
    UnkType_11064200_Player* unk_70;
};

// UnkType_11064200::Unk_11064200
int UnkType_11064200::Unk_11064200(UnkType_11064200_Record* Record)
{
    UnkType_11064200_Found* Found;
    UnkType_11064200_Block* Block;

    if ( Unk_11063820(Record) == 0 )
    {
        return 0;
    }
    Found = Unk_11063680(Record->unk_4);
    if ( Found == 0 )
    {
        return 0;
    }
    Block = &unk_4->unk_10;
    if ( Unk_11063890(&Found->unk_4) == 0 )
    {
        return 0;
    }
    unk_70->Unk_1106e6b0(Block->unk_1c, &Record->unk_4);
    return Unk_11063b30(Record) != 0;
}
