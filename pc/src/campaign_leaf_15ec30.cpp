// campaign_leaf_15ec30.cpp -- one function at file offset 0x15ec30, preferred VA 0x10a5ec30.
// guess: copies the items of one entry of its list at offset 0x1b0 (28-byte entries, each with an
// array of 4-byte items at offset 4) into the output array through its method at VA 0x10936000,
// first emptying the output when asked to. An invalid index adds nothing.
// The class, member, parameter and callee names are invented; the offset and the bytes are the
// binary's.

class UnkType_10a5ec30_Item;

class UnkType_10a5ec30_Output
{
public:
    UnkType_10a5ec30_Item** Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10936000(UnkType_10a5ec30_Item* const& Item);
};

class UnkType_10a5ec30_Entry
{
public:
    int unk_0;
    UnkType_10a5ec30_Item** unk_4;
    int unk_8;
    unsigned char unk_c[0x1c - 0xc];
};

class UnkType_10a5ec30
{
public:
    unsigned char unk_0[0x1b0];
    UnkType_10a5ec30_Entry* unk_1b0;
    int unk_1b4;

    void Unk_10a5ec30(int Index, UnkType_10a5ec30_Output& Output, int bEmpty);
};

// UnkType_10a5ec30::Unk_10a5ec30
void UnkType_10a5ec30::Unk_10a5ec30(int Index, UnkType_10a5ec30_Output& Output, int bEmpty)
{
    if ( bEmpty )
    {
        Output.ArrayNum = 0;
    }
    if ( Index >= 0 && Index < unk_1b4 )
    {
        for ( int i = 0; i < unk_1b0[Index].unk_8; i++ )
        {
            Output.Unk_10936000(unk_1b0[Index].unk_4[i]);
        }
    }
}
