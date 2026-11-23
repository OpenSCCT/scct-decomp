// campaign_leaf_26aa20.cpp -- a member function at VA 0x10b6aa20 taking two ints it does not read:
// when the object the pointer at 0x1c refers to exists and its flag byte at 0x20 has bit 1 set and
// bit 0 clear, it divides that object's unsigned int at 0x18 by its unsigned int at 0x1c; when the
// quotient is at most 6 it calls the object's member at VA 0x10d308c0 with seven times the divisor
// and 1, and when it is at least 25 it calls the object's member at VA 0x10d307f0 with 0 and 1 and
// clears the byte at 0x24. It returns false. The class, method, member and parameter names are
// invented; the offsets, addresses and constants are the binary's.

class UnkType_10b6aa20_Item
{
public:
    void Unk_10d307f0(int First, int Second);
    void Unk_10d308c0(int First, int Second);

    // guess: the int at 0x18 divided by the int at 0x1c (an inline accessor; name invented)
    int GetRatio() const
    {
        return unk_18 / unk_1c;
    }

    unsigned char unk_00[0x18];
    unsigned int unk_18;
    unsigned int unk_1c;
    unsigned char unk_20;
};

class UnkType_10b6aa20
{
public:
    bool Unk_10b6aa20(int First, int Second);

private:
    unsigned char unk_00[0x1c];
    UnkType_10b6aa20_Item* unk_1c;
    unsigned char unk_20[0x24 - 0x20];
    bool unk_24;
};

// UnkType_10b6aa20::Unk_10b6aa20
bool UnkType_10b6aa20::Unk_10b6aa20(int First, int Second)
{
    if ( unk_1c && ( unk_1c->unk_20 & 2 ) && !( unk_1c->unk_20 & 1 ) )
    {
        if ( unk_1c->GetRatio() <= 6 )
        {
            unk_1c->Unk_10d308c0(unk_1c->unk_1c * 7, 1);
            return false;
        }
        if ( unk_1c->GetRatio() >= 25 )
        {
            unk_1c->Unk_10d307f0(0, 1);
            unk_24 = false;
        }
    }
    return false;
}
