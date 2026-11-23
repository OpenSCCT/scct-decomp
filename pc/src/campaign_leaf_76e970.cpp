// campaign_leaf_76e970.cpp -- one function at file offset 0x76e970, preferred VA 0x1106e970. With a
// nonzero first argument it stores the second at 0x3c and the first at 0x38, copies the word at
// 0x30 to 0x44 unless the flag at 0x34 is set, copies 0x44 to 0x40, stores the result of the
// stdcall function at VA 0x1104b270 on the first argument and the word at 0x1c at 0x2c, the third
// argument at 0x30 and sets the flag; with a zero first argument it clears the flag and stores the
// third argument at 0x30. The class, method and member names are invented; the offsets and the
// callee's address are the binary's.

int __stdcall Unk_1104b270(int Value, int Scale);

class UnkType_1106e970
{
public:
    void Unk_1106e970(int First, int Second, int Third);

    unsigned char unk_0[0x1c];
    int unk_1c;
    unsigned char unk_20[0x2c - 0x20];
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
    int unk_40;
    int unk_44;
};

// UnkType_1106e970::Unk_1106e970
void UnkType_1106e970::Unk_1106e970(int First, int Second, int Third)
{
    if ( First != 0 )
    {
        unk_3c = Second;
        unk_38 = First;
        if ( unk_34 == 0 )
        {
            unk_44 = unk_30;
        }
        unk_40 = unk_44;
        unk_2c = Unk_1104b270(First, unk_1c);
        unk_30 = Third;
        unk_34 = 1;
    }
    else
    {
        unk_34 = 0;
        unk_30 = Third;
    }
}
