// campaign_leaf_342040.cpp -- one function at file offset 0x342040, preferred VA 0x10c42040. When
// Id is not -1 and Out is set, it asks the method at 0x10c41d70 for the id of each index below
// the count at 0x6c of the object at 0x34c of the object at 0x400; at the first index whose id is
// Id it stores the index in Out and returns 1. Otherwise it returns 0. The class, method, member,
// local and parameter names are invented; the offsets, the constants and the bytes are the
// binary's.

class UnkType_10c42040_Table
{
public:
    unsigned char unk_0[0x6c];
    int unk_6c;
};

class UnkType_10c42040_Owner
{
public:
    unsigned char unk_0[0x34c];
    UnkType_10c42040_Table* unk_34c;
};

class UnkType_10c42040
{
public:
    void Unk_10c41d70(int Index, int* Id);
    int Unk_10c42040(int Id, int* Out);

    unsigned char unk_0[0x400];
    UnkType_10c42040_Owner* unk_400;
};

// UnkType_10c42040::Unk_10c42040
int UnkType_10c42040::Unk_10c42040(int Id, int* Out)
{
    int Count;
    int Index;

    if ( Id == -1 || Out == 0 )
    {
        return 0;
    }
    Count = unk_400->unk_34c->unk_6c;
    for ( Index = 0; Index < Count; Index++ )
    {
        int Found;

        Unk_10c41d70(Index, &Found);
        if ( Found == Id )
        {
            *Out = Index;
            return 1;
        }
    }
    return 0;
}
