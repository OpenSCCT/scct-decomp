// campaign_leaf_57e120.cpp -- thiscall method at VA 0x10e7e120: reads a word through the object at
// 0x78, with the method at VA 0x10e00d60 when the mode byte at 0x0c is 0 or as four bytes with the
// method at VA 0x10e00f10 when it is 1, stores it through its argument and returns the object.
// guess: an archive's operator for a 32-bit value. All names are invented.

class UnkType_10e7e120_Stream
{
public:
    void Unk_10e00d60(int* Value);
    void Unk_10e00f10(void* Data, int Size);
};

class UnkType_10e7e120
{
public:
    UnkType_10e7e120& Unk_10e7e120(int* Value);

private:
    int unk_00[3];
    char unk_0c;
    int unk_10[26];
    UnkType_10e7e120_Stream* unk_78;
};

// UnkType_10e7e120::Unk_10e7e120
UnkType_10e7e120& UnkType_10e7e120::Unk_10e7e120(int* Value)
{
    int Read;
    switch ( unk_0c )
    {
    case 0:
        unk_78->Unk_10e00d60(&Read);
        break;
    case 1:
        unk_78->Unk_10e00f10(&Read, 4);
        break;
    }
    *Value = Read;
    return *this;
}
