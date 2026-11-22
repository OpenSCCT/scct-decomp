// versus_leaf_274050.cpp -- stores its three arguments at 0, 4 and 8 of the object, at file offset 0x274050
// (VA 0x10b74050). The class and method names are invented; the offsets, the argument sizes and the calling
// convention are the binary's.

class UnkType_10b74050
{
public:
    void SetUnk00Unk04Unk08(int A, int B, int C);

private:
    int unk_00;                         // written by SetUnk00Unk04Unk08
    int unk_04;                         // written by SetUnk00Unk04Unk08
    int unk_08;                         // written by SetUnk00Unk04Unk08
};

// UnkType_10b74050::SetUnk00Unk04Unk08
// The function pops its three arguments (ret 0xc).
void UnkType_10b74050::SetUnk00Unk04Unk08(int A, int B, int C)
{
    unk_00 = A;
    unk_04 = B;
    unk_08 = C;
}
