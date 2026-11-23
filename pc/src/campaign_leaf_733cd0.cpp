// campaign_leaf_733cd0.cpp -- one function at file offset 0x733cd0, preferred VA 0x11033cd0. It
// calls the method at VA 0x11033f50, sets the byte at 0x1d4 and calls the method at VA 0x11033e60.
// The class, method and member names are invented; the offset and the addresses are the binary's.

class UnkType_11033cd0
{
public:
    void Unk_11033cd0();
    void Unk_11033f50();
    void Unk_11033e60();

    unsigned char unk_0[0x1d4];
    bool unk_1d4;
};

// UnkType_11033cd0::Unk_11033cd0
void UnkType_11033cd0::Unk_11033cd0()
{
    Unk_11033f50();
    unk_1d4 = true;
    Unk_11033e60();
}
