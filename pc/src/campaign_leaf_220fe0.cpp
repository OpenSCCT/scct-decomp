// campaign_leaf_220fe0.cpp -- a member function at VA 0x10b20fe0 taking three ints: when the
// pointer at 0x40 is set and that object's member at VA 0x10ad4790 returns non-zero, it clears the
// object's byte at 0x14 and returns 1 when the object's int at 0xe4 is set and its member at VA
// 0x10ad4ac0 accepts the three ints; otherwise it returns what its own member at VA 0x10a0db60
// returns for them. It returns 0 when there is no such object. The class, method, member and
// parameter names are invented; the offsets and addresses are the binary's.

class UnkType_10b20fe0_Item
{
public:
    int Unk_10ad4790();
    int Unk_10ad4ac0(int First, int Second, int Third);

    unsigned char unk_00[0x14];
    bool unk_14;
    unsigned char unk_15[0xe4 - 0x15];
    int unk_e4;
};

class UnkType_10b20fe0
{
public:
    int Unk_10a0db60(int First, int Second, int Third);
    int Unk_10b20fe0(int First, int Second, int Third);

private:
    unsigned char unk_00[0x40];
    UnkType_10b20fe0_Item* unk_40;
};

// UnkType_10b20fe0::Unk_10b20fe0
int UnkType_10b20fe0::Unk_10b20fe0(int First, int Second, int Third)
{
    UnkType_10b20fe0_Item* Item = unk_40;
    if ( Item && Item->Unk_10ad4790() )
    {
        Item->unk_14 = false;
        if ( Item->unk_e4 && Item->Unk_10ad4ac0(First, Second, Third) )
        {
            return 1;
        }
        return Unk_10a0db60(First, Second, Third);
    }
    return 0;
}
