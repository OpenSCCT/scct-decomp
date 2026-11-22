// campaign_leaf_035810.cpp -- one function at file offset 0x35810, preferred VA 0x10935810. It
// resets the defaults of this object: two words to zero, the flag word at 0x9ec to clear bits 0x9
// and set bits 0x6, and four words to the constants -1.0, 150.0, 500.0 and 1.5. The class and
// method names are invented; the offset and the bytes are the binary's.

class UnkType_10935810
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
    float unk_9f0;                  // set to 150.0
    float unk_9f4;                  // set to 500.0
    float unk_9f8;                  // set to 1.5
};

// UnkType_10935810::UnkReset
void UnkType_10935810::UnkReset()
{
    unk_984 = 0;
    unk_978 = 0;
    int Flags = ( unk_9ec & 0xfffffff6 ) | 6;
    unk_988 = -1.0f;
    unk_9f0 = 150.0f;
    unk_9f4 = 500.0f;
    unk_9f8 = 1.5f;
    unk_9ec = Flags;
}
