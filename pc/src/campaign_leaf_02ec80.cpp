// campaign_leaf_02ec80.cpp -- one function at file offset 0x2ec80, preferred VA 0x1092ec80. It sets
// the word at offset 0 to its second argument, the words from offset 0x04 to 0x20 to zero, the word
// at 0x24 to its first argument, the word at 0x28 to -1, and the words at 0x2c and 0x30 to zero. It
// returns this object. The class, method and parameter names are invented; the offset and the bytes
// are the binary's.

class UnkType_1092ec80
{
public:
    UnkType_1092ec80 *UnkInit(int First, int Second);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
};

// UnkType_1092ec80::UnkInit
UnkType_1092ec80 *UnkType_1092ec80::UnkInit(int First, int Second)
{
    unk_00 = Second;
    unk_04 = 0;
    unk_08 = 0;
    unk_0c = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
    unk_1c = 0;
    unk_20 = 0;
    unk_24 = First;
    unk_28 = -1;
    unk_2c = 0;
    unk_30 = 0;
    return this;
}
