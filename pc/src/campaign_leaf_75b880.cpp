// campaign_leaf_75b880.cpp -- one function at file offset 0x75b880, preferred VA 0x1105b880. It
// runs the method at VA 0x1105b140 when the handle at 0x38 is not -2 and the method at VA
// 0x1105b1a0 when the handle at 0x3c is not -2, stopping when either leaves the state at 0x4 at
// 0x13. When the words at 0x1c and 0x34 are both set it then sets the state to 0xd and runs the
// method at VA 0x1105b730 if both handles are -2, and otherwise sets the state to 0xe. The class,
// method and member names are invented; the offsets and the addresses are the binary's.

class UnkType_1105b880
{
public:
    void Unk_1105b140();
    void Unk_1105b1a0();
    void Unk_1105b730();
    void Unk_1105b880();

    int unk_0;
    int unk_4;
    unsigned char unk_8[0x1c - 0x8];
    int unk_1c;
    unsigned char unk_20[0x34 - 0x20];
    int unk_34;
    int unk_38;
    int unk_3c;
};

// UnkType_1105b880::Unk_1105b880
void UnkType_1105b880::Unk_1105b880()
{
    if ( unk_38 != -2 )
    {
        Unk_1105b140();
        if ( unk_4 == 0x13 )
        {
            return;
        }
    }
    if ( unk_3c != -2 )
    {
        Unk_1105b1a0();
        if ( unk_4 == 0x13 )
        {
            return;
        }
    }
    if ( unk_1c == 0 || unk_34 == 0 )
    {
        return;
    }
    if ( unk_38 == -2 && unk_3c == -2 )
    {
        unk_4 = 0xd;
        Unk_1105b730();
        return;
    }
    unk_4 = 0xe;
}
