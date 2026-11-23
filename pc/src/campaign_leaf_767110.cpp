// campaign_leaf_767110.cpp -- one function at file offset 0x767110, preferred VA 0x11067110. When
// the handle at 0x4 is not -1 it passes it to the function at VA 0x1104a0a0; it then sets the
// handle to -1 and calls the method at VA 0x11066f00 on the member at 0x34 and the method at VA
// 0x11066820 on the member at 0x20. The class, method and member names are invented; the offsets
// and the addresses are the binary's.

void Unk_1104a0a0(int Handle);

class UnkType_11067110_First
{
public:
    void Unk_11066f00();
};

class UnkType_11067110_Second
{
public:
    void Unk_11066820();

    unsigned char unk_0[0x14];
};

class UnkType_11067110
{
public:
    void Unk_11067110();

    int unk_0;
    int unk_4;
    unsigned char unk_8[0x20 - 0x8];
    UnkType_11067110_Second unk_20;
    UnkType_11067110_First unk_34;
};

// UnkType_11067110::Unk_11067110
void UnkType_11067110::Unk_11067110()
{
    if ( unk_4 != -1 )
    {
        Unk_1104a0a0(unk_4);
    }
    unk_4 = -1;
    unk_34.Unk_11066f00();
    unk_20.Unk_11066820();
}
