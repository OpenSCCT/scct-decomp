// campaign_leaf_4ce260.cpp -- one function at file offset 0x4ce260, preferred VA 0x10dce260.
// It stores the result of the method at 0x10dcdde0, called with the int at offset
// 0xc and Value, in a local byte and passes its address, 1 and -1 to the method at 0x10dce120. The
// class, method, member, variable and parameter names are invented; the offset and the bytes are
// the binary's.

class UnkType_10dce260
{
public:
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;

    char Unk_10dcdde0(int First, int Second);
    void Unk_10dce120(const char* Data, int Size, int Count);
    void Unk_10dce260(int Value);
};

// UnkType_10dce260::Unk_10dce260
void UnkType_10dce260::Unk_10dce260(int Value)
{
    char Byte = Unk_10dcdde0(unk_c, Value);

    Unk_10dce120(&Byte, 1, -1);
}
