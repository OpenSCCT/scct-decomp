// campaign_leaf_2fa790.cpp -- method at VA 0x10bfa790 taking two pointers to words: passes them to
// the method at VA 0x10bf80a0; then, when the float at 0x554 is below 1, sets bit 7 of the word at
// 0x30 of the object at 0x544 if the first word is 2 and the second is zero, or clears that bit if
// the first word is 1 and the second is nonzero. The class, member and method names are invented;
// the offsets and the address are the binary's.

class UnkType_10bfa790_544
{
public:
    unsigned char unk_00[0x30];
    unsigned int unk_30;
};

class UnkType_10bfa790
{
public:
    void Unk_10bfa790(int* Kind, int* Value);
    void Unk_10bf80a0(int* Kind, int* Value);

private:
    unsigned char unk_00[0x544];
    UnkType_10bfa790_544* unk_544;
    unsigned char unk_548[0x554 - 0x548];
    float unk_554;
};

// UnkType_10bfa790::Unk_10bfa790
void UnkType_10bfa790::Unk_10bfa790(int* Kind, int* Value)
{
    Unk_10bf80a0(Kind, Value);
    switch ( *Kind )
    {
    case 1:
        if ( *Value && unk_554 < 1.0f )
        {
            unk_544->unk_30 &= ~0x80;
        }
        break;
    case 2:
        if ( !*Value && unk_554 < 1.0f )
        {
            unk_544->unk_30 |= 0x80;
        }
        break;
    }
}
