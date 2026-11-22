// campaign_leaf_26fd60.cpp -- a member function at VA 0x10b6fd60 that clears the bytes at 0x34 and
// 0x0c and, when the int at 0x14 is not zero, passes it, 0, 1 and 0 to the member at VA 0x10ad5820
// of the object the pointer at 0x08 refers to. The class, method and member names are invented; the
// offsets and addresses are the binary's.

class UnkType_10ad5820
{
public:
    void Unk_10ad5820(int Value, int First, int Second, int Third);
};

class UnkType_10b6fd60
{
public:
    void Unk_10b6fd60();

private:
    int unk_00;
    int unk_04;
    UnkType_10ad5820* unk_08;
    unsigned char unk_0c;
    unsigned char unk_0d[3];
    int unk_10;
    int unk_14;
    unsigned char unk_18[0x34 - 0x18];
    unsigned char unk_34;
};

// UnkType_10b6fd60::Unk_10b6fd60
void UnkType_10b6fd60::Unk_10b6fd60()
{
    unk_34 = 0;
    unk_0c = 0;
    if ( unk_14 )
    {
        unk_08->Unk_10ad5820(unk_14, 0, 1, 0);
    }
}
