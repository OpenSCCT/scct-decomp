// campaign_leaf_341d70.cpp -- one function at file offset 0x341d70, preferred VA 0x10c41d70. When
// its first argument is not -1 and its second is non-null, it takes the 0x3c-byte entry it selects
// in the array at offset 0x68 of the object reached through offsets 0x400 and 0x34c, stores the
// first of that entry's three words at offset 0xc that is not -1 through the second argument and
// returns 1; otherwise it returns 0. The class, method and member names are invented; the offset
// and the bytes are the binary's.

struct UnkType_10c41d70_Entry
{
    unsigned char unk_0[0xc];
    int unk_c[3];
    unsigned char unk_18[0x3c - 0x18];
};

class UnkType_10c41d70_Table
{
public:
    unsigned char unk_0[0x68];
    UnkType_10c41d70_Entry* unk_68;
};

class UnkType_10c41d70_Owner
{
public:
    unsigned char unk_0[0x34c];
    UnkType_10c41d70_Table* unk_34c;
};

class UnkType_10c41d70
{
public:
    unsigned char unk_0[0x400];
    UnkType_10c41d70_Owner* unk_400;

    int Unk_10c41d70(int Index, int* Out);
};

// UnkType_10c41d70::Unk_10c41d70
int UnkType_10c41d70::Unk_10c41d70(int Index, int* Out)
{
    if ( Index != -1 && Out )
    {
        for ( int i = 0; i < 3; i++ )
        {
            if ( unk_400->unk_34c->unk_68[Index].unk_c[i] != -1 )
            {
                *Out = unk_400->unk_34c->unk_68[Index].unk_c[i];
                return 1;
            }
        }
        return 0;
    }
    return 0;
}
