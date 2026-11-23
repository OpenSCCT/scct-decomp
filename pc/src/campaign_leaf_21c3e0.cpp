// campaign_leaf_21c3e0.cpp -- a member function at VA 0x10b1c3e0 taking a byte and an int: when the
// byte at 0x23e9 is set it sets the int at 0x16f0 to 1 and calls the member at VA 0x10efe000; when
// the byte argument is 0x26 it sets the int at 0x16f0 to 6; otherwise it calls the member at VA
// 0x10b090d0 with 1, the int argument and 1, sets the int at 0x16f0 to 1, calls the member at VA
// 0x10efe000 and sets the int at 0x16f8 to 1. The class, method, member and parameter names are
// invented; the offsets, constants and addresses are the binary's.

class UnkType_10b1c3e0
{
public:
    void Unk_10b090d0(int First, int Value, int Third);
    void Unk_10efe000();
    void Unk_10b1c3e0(unsigned char Key, int Value);

private:
    unsigned char unk_0000[0x16f0];
    int unk_16f0;
    unsigned char unk_16f4[0x16f8 - 0x16f4];
    int unk_16f8;
    unsigned char unk_16fc[0x23e9 - 0x16fc];
    bool unk_23e9;
};

// UnkType_10b1c3e0::Unk_10b1c3e0
void UnkType_10b1c3e0::Unk_10b1c3e0(unsigned char Key, int Value)
{
    if ( unk_23e9 )
    {
        unk_16f0 = 1;
        Unk_10efe000();
        return;
    }
    if ( Key == 0x26 )
    {
        unk_16f0 = 6;
        return;
    }
    Unk_10b090d0(1, Value, 1);
    unk_16f0 = 1;
    Unk_10efe000();
    unk_16f8 = 1;
}
