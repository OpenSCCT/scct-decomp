// campaign_leaf_117290.cpp -- one function at file offset 0x117290, preferred VA 0x10a17290.
// guess: for each of its three children at offsets 0x48, 0x4c and 0x50 whose flag at bit 11 of
// offset 0x98 is set, clears the flag and calls the child's method at VA 0x10a16d70.
// The class, member and callee names are invented; the offset and the bytes are the binary's.

class UnkType_10a17290_Child
{
public:
    unsigned char unk_0[0x98];
    unsigned int unk_98_0 : 11;
    unsigned int unk_98_11 : 1;

    void Unk_10a16d70();
};

class UnkType_10a17290
{
public:
    unsigned char unk_0[0x48];
    UnkType_10a17290_Child* unk_48;
    UnkType_10a17290_Child* unk_4c;
    UnkType_10a17290_Child* unk_50;

    void Unk_10a17290();
};

// UnkType_10a17290::Unk_10a17290
void UnkType_10a17290::Unk_10a17290()
{
    UnkType_10a17290_Child* Child;

    Child = unk_48;
    if ( Child && Child->unk_98_11 )
    {
        Child->unk_98_11 = 0;
        Child->Unk_10a16d70();
    }
    Child = unk_4c;
    if ( Child && Child->unk_98_11 )
    {
        Child->unk_98_11 = 0;
        Child->Unk_10a16d70();
    }
    Child = unk_50;
    if ( Child && Child->unk_98_11 )
    {
        Child->unk_98_11 = 0;
        Child->Unk_10a16d70();
    }
}
