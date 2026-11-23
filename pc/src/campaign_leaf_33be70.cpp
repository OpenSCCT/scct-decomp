// campaign_leaf_33be70.cpp -- one function at file offset 0x33be70, preferred VA 0x10c3be70. With
// Other set, it returns 0 when either function at 0x10c3bd00 or 0x10c3bd60 accepts Other and the
// byte at 0x41c is 2; otherwise it clears bit 9 of the word at 0x28 and sets bit 9 of the word at
// 0x30 first. It returns what the method at 0x10bef890 gives for (Other, Second). The class,
// function, method, member, local and parameter names are invented; the offsets, the constants
// and the bytes are the binary's.

class UnkType_10c3be70_Other;

int Unk_10c3bd00(UnkType_10c3be70_Other* Other);
int Unk_10c3bd60(UnkType_10c3be70_Other* Other);

class UnkType_10c3be70
{
public:
    int Unk_10bef890(UnkType_10c3be70_Other* Other, int Second);
    int Unk_10c3be70(UnkType_10c3be70_Other* Other, int Second);

    unsigned char unk_0[0x28];
    int unk_28;
    unsigned char unk_2c[0x4];
    int unk_30;
    unsigned char unk_34[0x3e8];
    unsigned char unk_41c;
};

// UnkType_10c3be70::Unk_10c3be70
int UnkType_10c3be70::Unk_10c3be70(UnkType_10c3be70_Other* Other, int Second)
{
    int First;
    int Next;

    if ( Other == 0 )
    {
        return Unk_10bef890(Other, Second);
    }
    First = Unk_10c3bd00(Other);
    Next = Unk_10c3bd60(Other);
    if ( (First || Next) && unk_41c == 2 )
    {
        return 0;
    }
    unk_28 &= ~0x200;
    unk_30 |= 0x200;
    return Unk_10bef890(Other, Second);
}
