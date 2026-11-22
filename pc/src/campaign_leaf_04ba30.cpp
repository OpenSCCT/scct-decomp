// campaign_leaf_04ba30.cpp -- one function at file offset 0x4ba30, preferred VA 0x1094ba30. It
// resets the defaults of this object: two words to zero, the flag word at 0x9ec to clear bits 0x9
// and set bits 0x6, and four words to the constants -1.0, 85.0, 1500.0 and 5.0. The class and
// method names are invented; the offset and the bytes are the binary's.

class UnkType_1094ba30
{
public:
    void UnkReset();

private:
    unsigned char unk_00[0x978];    // not touched by this function
    int unk_978;                    // cleared
    unsigned char unk_97c[0x8];     // not touched by this function
    int unk_984;                    // cleared
    float unk_988;                  // set to -1.0
    unsigned char unk_98c[0x60];    // not touched by this function
    int unk_9ec;                    // flag word
    float unk_9f0;                  // set to 85.0
    float unk_9f4;                  // set to 1500.0
    float unk_9f8;                  // set to 5.0
};

// UnkType_1094ba30::UnkReset
void UnkType_1094ba30::UnkReset()
{
    unk_984 = 0;
    unk_978 = 0;
    int Flags = ( unk_9ec & 0xfffffff6 ) | 6;
    unk_988 = -1.0f;
    unk_9f0 = 85.0f;
    unk_9f4 = 1500.0f;
    unk_9f8 = 5.0f;
    unk_9ec = Flags;
}
