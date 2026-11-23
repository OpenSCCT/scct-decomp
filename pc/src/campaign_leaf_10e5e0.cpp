// campaign_leaf_10e5e0.cpp -- one function at file offset 0x10e5e0, preferred VA 0x10a0e5e0.
// A constructor taking an index and an object: it points the member at offset 0x8 at offset 0x3f8
// of the object's object at offset 0x30 and the one at offset 0xc at the 12-byte entry the index
// selects at offset 0x2ac of the object's object at offset 0x5c, then stores the result of its
// method at VA 0x10a0e000 (the index and bit field 8 of the word at offset 0x398 of the first
// object) at offset 0 and the index at offset 4.
// The class and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10a0e5e0_Entry
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10a0e5e0_Pawn
{
public:
    unsigned char unk_0[0x398];
    unsigned int unk_398_0 : 8;
    unsigned int unk_398_8 : 1;
    unsigned char unk_39c[0x3f8 - 0x39c];
    int unk_3f8;
};

class UnkType_10a0e5e0_Info
{
public:
    unsigned char unk_0[0x2ac];
    UnkType_10a0e5e0_Entry unk_2ac[1];
};

class UnkType_10a0e5e0_Owner
{
public:
    unsigned char unk_0[0x30];
    UnkType_10a0e5e0_Pawn* unk_30;
    unsigned char unk_34[0x5c - 0x34];
    UnkType_10a0e5e0_Info* unk_5c;
};

class UnkType_10a0e5e0
{
public:
    void* unk_0;
    short unk_4;
    int* unk_8;
    UnkType_10a0e5e0_Entry* unk_c;

    void* Unk_10a0e000(int Index, unsigned char Flag);
    UnkType_10a0e5e0(int Index, UnkType_10a0e5e0_Owner* Owner);
};

// UnkType_10a0e5e0::UnkType_10a0e5e0
UnkType_10a0e5e0::UnkType_10a0e5e0(int Index, UnkType_10a0e5e0_Owner* Owner)
    : unk_0(0), unk_4(0), unk_8(&Owner->unk_30->unk_3f8), unk_c(&Owner->unk_5c->unk_2ac[Index])
{
    unk_0 = Unk_10a0e000(Index, Owner->unk_30->unk_398_8);
    unk_4 = Index;
}
