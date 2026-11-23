// campaign_leaf_4b4890.cpp -- one function at file offset 0x4b4890, preferred VA 0x10db4890.
// It stores the result of the cdecl function at 0x10d98200, called with -1, in the int at offset
// 0x104. The class, function, method and member names are invented; the offset and the bytes are
// the binary's.

int Unk_10d98200(int Value);

class UnkType_10db4890
{
public:
    unsigned char unk_0[0x104];
    int unk_104;

    void Unk_10db4890();
};

// UnkType_10db4890::Unk_10db4890
void UnkType_10db4890::Unk_10db4890()
{
    unk_104 = Unk_10d98200(-1);
}
