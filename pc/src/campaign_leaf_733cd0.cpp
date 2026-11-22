// campaign_leaf_733cd0.cpp -- thiscall method at VA 0x11033cd0: calls the method at VA 0x11033f50,
// sets the byte at 0x1d4 to 1, then calls the method at VA 0x11033e60. The class and method names
// are invented.

class UnkType_11033cd0
{
public:
    void Unk_11033f50();
    void Unk_11033e60();
    void Unk_11033cd0();

private:
    int unk_00[117];
    unsigned char unk_1d4;
};

// UnkType_11033cd0::Unk_11033cd0
void UnkType_11033cd0::Unk_11033cd0()
{
    Unk_11033f50();
    unk_1d4 = 1;
    Unk_11033e60();
}
