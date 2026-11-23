// campaign_leaf_75d9a0.cpp -- one function at file offset 0x75d9a0, preferred VA 0x1105d9a0. It
// returns 0 unless all eight words of the table it is given are set; it then stores the table at
// 0x18, sets the word at 0x0 to 1 and returns whether the method at VA 0x1105d360 accepts the
// other three arguments. The class, method and member names are invented; the offsets and the
// callee's address are the binary's.

struct UnkType_1105d9a0_Table
{
    void* unk_0;
    void* unk_4;
    void* unk_8;
    void* unk_c;
    void* unk_10;
    void* unk_14;
    void* unk_18;
    void* unk_1c;
};

class UnkType_1105d9a0
{
public:
    int Unk_1105d360(int First, int Second, int Third);
    int Unk_1105d9a0(UnkType_1105d9a0_Table* Table, int First, int Second, int Third);

    int unk_0;
    unsigned char unk_4[0x18 - 0x4];
    UnkType_1105d9a0_Table* unk_18;
};

// UnkType_1105d9a0::Unk_1105d9a0
int UnkType_1105d9a0::Unk_1105d9a0(UnkType_1105d9a0_Table* Table, int First, int Second,
                                   int Third)
{
    if ( Table->unk_0 == 0 || Table->unk_4 == 0 || Table->unk_8 == 0 || Table->unk_c == 0 ||
         Table->unk_10 == 0 || Table->unk_14 == 0 || Table->unk_18 == 0 || Table->unk_1c == 0 )
    {
        return 0;
    }
    unk_18 = Table;
    unk_0 = 1;
    return Unk_1105d360(First, Second, Third) != 0;
}
