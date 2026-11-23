// campaign_leaf_0ee4a0.cpp -- method at VA 0x109ee4a0 taking a byte and a 12-byte vector: unless
// the object at 0x58 has the byte 11 at 0x4c and the object reached through its 0x78 and 0x5d0
// pointers has bit 4 of the flags at 0x2dc set, builds a 16-byte record of the byte and the vector
// and passes it to the method at VA 0x109e9c20 of the member at 0x238. The class, member and method
// names are invented; the offsets and the addresses are the binary's.

struct UnkType_109ee4a0_Vector
{
    float unk_00;
    float unk_04;
    float unk_08;
};

struct UnkType_109ee4a0_Record
{
    unsigned char unk_00;
    UnkType_109ee4a0_Vector unk_04;
};

class UnkType_109ee4a0_Queue
{
public:
    void Unk_109e9c20(const UnkType_109ee4a0_Record& Record);
};

class UnkType_109ee4a0_Controller
{
public:
    unsigned char unk_00[0x2dc];
    unsigned int unk_2dc;
};

class UnkType_109ee4a0_Pawn
{
public:
    unsigned char unk_00[0x5d0];
    UnkType_109ee4a0_Controller* unk_5d0;
};

class UnkType_109ee4a0_Owner
{
public:
    unsigned char unk_00[0x4c];
    unsigned char unk_4c;
    unsigned char unk_4d[0x78 - 0x4d];
    UnkType_109ee4a0_Pawn* unk_78;
};

class UnkType_109ee4a0
{
public:
    void Unk_109ee4a0(unsigned char Kind, const UnkType_109ee4a0_Vector& Value);

private:
    unsigned char unk_00[0x58];
    UnkType_109ee4a0_Owner* unk_58;
    unsigned char unk_5c[0x238 - 0x5c];
    UnkType_109ee4a0_Queue unk_238;
};

// UnkType_109ee4a0::Unk_109ee4a0
void UnkType_109ee4a0::Unk_109ee4a0(unsigned char Kind, const UnkType_109ee4a0_Vector& Value)
{
    if ( unk_58 && unk_58->unk_4c == 11 && unk_58->unk_78 && unk_58->unk_78->unk_5d0
         && (unk_58->unk_78->unk_5d0->unk_2dc & 4) )
    {
        return;
    }
    UnkType_109ee4a0_Record Record;
    Record.unk_00 = Kind;
    Record.unk_04 = Value;
    unk_238.Unk_109e9c20(Record);
}
