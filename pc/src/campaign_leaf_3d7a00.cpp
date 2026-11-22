// campaign_leaf_3d7a00.cpp -- one function at file offset 0x3d7a00, preferred VA 0x10cd7a00. It
// clears the word at 0x1c of the entry the old pair (0x10, 0x14) names, a pointer and an index
// into its 0x24-byte table at 0x88, then stores the new pair. The class, method, structure and
// member names are invented; the offsets and the bytes are the binary's.

struct UnkEntry_10cd7a00
{
    unsigned char unk_0[0x1c];
    int unk_1c;
    int unk_20;
};

struct UnkOwner_10cd7a00
{
    unsigned char unk_0[0x88];
    UnkEntry_10cd7a00* unk_88;
};

class UnkType_10cd7a00
{
public:
    void Unk_10cd7a00(UnkOwner_10cd7a00* Owner, int Index);

    unsigned char unk_0[0x10];
    UnkOwner_10cd7a00* unk_10;
    int unk_14;
};

// UnkType_10cd7a00::Unk_10cd7a00
void UnkType_10cd7a00::Unk_10cd7a00(UnkOwner_10cd7a00* Owner, int Index)
{
    if ( unk_10 != 0 )
    {
        unk_10->unk_88[unk_14].unk_1c = 0;
    }
    unk_10 = Owner;
    unk_14 = Index;
}
