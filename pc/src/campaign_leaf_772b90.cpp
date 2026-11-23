// campaign_leaf_772b90.cpp -- one function at file offset 0x772b90, preferred VA 0x11072b90. It
// stores its first argument at 0x50 and, when its second differs from the word at 0x28, stores
// that at 0x28 and calls the method at VA 0x11072550. The class, method and member names are
// invented; the offsets and the callee's address are the binary's.

class UnkType_11072b90
{
public:
    void Unk_11072550();
    void Unk_11072b90(int First, int Second);

    unsigned char unk_0[0x28];
    int unk_28;
    unsigned char unk_2c[0x50 - 0x2c];
    int unk_50;
};

// UnkType_11072b90::Unk_11072b90
void UnkType_11072b90::Unk_11072b90(int First, int Second)
{
    unk_50 = First;
    if ( unk_28 != Second )
    {
        unk_28 = Second;
        Unk_11072550();
    }
}
