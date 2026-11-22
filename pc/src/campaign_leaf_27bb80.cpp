// campaign_leaf_27bb80.cpp -- one function at file offset 0x27bb80, preferred VA 0x10b7bb80. It
// sets bit field 17 of the word at offset 0x2b0, stores its argument at offset 0x984, clears the
// words at offsets 0x988 and 0x98c and clears bit field 30 of the word at offset 0x748. The class,
// method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10b7bb80
{
public:
    unsigned char unk_0[0x2b0];
    unsigned int unk_2b0_0 : 17;
    unsigned int unk_2b0_17 : 1;
    unsigned char unk_2b4[0x748 - 0x2b4];
    unsigned int unk_748_0 : 30;
    unsigned int unk_748_30 : 1;
    unsigned char unk_74c[0x984 - 0x74c];
    int unk_984;
    int unk_988;
    int unk_98c;

    void Unk_10b7bb80(int Value);
};

// UnkType_10b7bb80::Unk_10b7bb80
void UnkType_10b7bb80::Unk_10b7bb80(int Value)
{
    unk_2b0_17 = 1;
    unk_984 = Value;
    unk_988 = 0;
    unk_748_30 = 0;
    unk_98c = 0;
}
