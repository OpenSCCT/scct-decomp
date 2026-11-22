// campaign_leaf_02f3e0.cpp -- one function at file offset 0x2f3e0, preferred VA 0x1092f3e0. It
// returns 1 when any index in the array of words its argument describes (data pointer, count)
// selects a 0x3c-byte entry, in the array at offset 0x68 of the object reached through offsets
// 0x3f8 and 0x518, whose word at offset 0x2c has bit 0x1 set; otherwise 0. The class, method and
// member names are invented; the offset and the bytes are the binary's.

struct UnkType_1092f3e0_IntArray
{
    int* unk_0;
    int unk_4;
};

struct UnkType_1092f3e0_Entry
{
    unsigned char unk_0[0x2c];
    int unk_2c;
    unsigned char unk_30[0x3c - 0x30];
};

class UnkType_1092f3e0_Table
{
public:
    unsigned char unk_0[0x68];
    UnkType_1092f3e0_Entry* unk_68;
};

class UnkType_1092f3e0_Owner
{
public:
    unsigned char unk_0[0x518];
    UnkType_1092f3e0_Table* unk_518;
};

class UnkType_1092f3e0
{
public:
    unsigned char unk_0[0x3f8];
    UnkType_1092f3e0_Owner* unk_3f8;

    int Unk_1092f3e0(const UnkType_1092f3e0_IntArray& Indices);
};

// UnkType_1092f3e0::Unk_1092f3e0
int UnkType_1092f3e0::Unk_1092f3e0(const UnkType_1092f3e0_IntArray& Indices)
{
    UnkType_1092f3e0_Table* Table = unk_3f8->unk_518;
    int Result = 0;
    for ( int i = 0; i < Indices.unk_4; i++ )
    {
        if ( Table->unk_68[Indices.unk_0[i]].unk_2c & 1 )
        {
            Result = 1;
            break;
        }
    }
    return Result;
}
