// campaign_leaf_1037c0.cpp -- one function at file offset 0x1037c0, preferred VA 0x10a037c0. It
// returns the first entry other than this object in the pointer array at offset 0x2e0 (count at
// 0x2e4) of the object reached through offsets 0x78 and 0x5d0, or null. The class, method and
// member names are invented; the offset and the bytes are the binary's.

class UnkType_10a037c0;

class UnkType_10a037c0_List
{
public:
    unsigned char unk_0[0x2e0];
    UnkType_10a037c0** unk_2e0;
    int unk_2e4;
};

class UnkType_10a037c0_Owner
{
public:
    unsigned char unk_0[0x5d0];
    UnkType_10a037c0_List* unk_5d0;
};

class UnkType_10a037c0
{
public:
    unsigned char unk_0[0x78];
    UnkType_10a037c0_Owner* unk_78;

    UnkType_10a037c0* Unk_10a037c0();
};

// UnkType_10a037c0::Unk_10a037c0
UnkType_10a037c0* UnkType_10a037c0::Unk_10a037c0()
{
    for ( int i = 0; i < unk_78->unk_5d0->unk_2e4; i++ )
    {
        if ( unk_78->unk_5d0->unk_2e0[i] != this )
        {
            return unk_78->unk_5d0->unk_2e0[i];
        }
    }
    return 0;
}
