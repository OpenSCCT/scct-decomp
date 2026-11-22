// campaign_leaf_1e7db0.cpp -- one function at file offset 0x1e7db0, preferred VA 0x10ae7db0. It
// stores at offset 0x94 the index of the first entry of the pointer array at offset 0x70 (count at
// 0x74) whose word at offset 0x34 equals its argument. The class, method and member names are
// invented; the offset and the bytes are the binary's.

class UnkType_10ae7db0_Item
{
public:
    unsigned char unk_0[0x34];
    int unk_34;
};

class UnkType_10ae7db0
{
public:
    unsigned char unk_0[0x70];
    UnkType_10ae7db0_Item** unk_70;
    int unk_74;
    unsigned char unk_78[0x94 - 0x78];
    int unk_94;

    void Unk_10ae7db0(int Key);
};

// UnkType_10ae7db0::Unk_10ae7db0
void UnkType_10ae7db0::Unk_10ae7db0(int Key)
{
    bool Found = false;
    for ( int i = 0; i < unk_74 && !Found; i++ )
    {
        if ( unk_70[i]->unk_34 == Key )
        {
            unk_94 = i;
            Found = true;
        }
    }
}
