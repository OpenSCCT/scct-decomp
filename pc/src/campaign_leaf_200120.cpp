// campaign_leaf_200120.cpp -- thiscall method at VA 0x10b00120 taking a stream, a flag byte and a
// word. For flag bit 1 it reads a value through the stream's method at VA 0x10d9e050 and passes it
// with the word to the method at VA 0x10affe70; for flag bit 2 it does the same with the method at
// VA 0x10afff60. The class, method and member names are invented.

class UnkType_10b00120_Stream
{
public:
    void Unk_10d9e050(int* Value);
};

class UnkType_10b00120
{
public:
    void Unk_10b00120(UnkType_10b00120_Stream* Stream, unsigned char Flags, int Extra);
    void Unk_10affe70(int* Value, int Extra);
    void Unk_10afff60(int* Value, int Extra);
};

// UnkType_10b00120::Unk_10b00120
void UnkType_10b00120::Unk_10b00120(UnkType_10b00120_Stream* Stream, unsigned char Flags,
                                    int Extra)
{
    int Value;

    if ( Flags & 1 )
    {
        Stream->Unk_10d9e050(&Value);
        Unk_10affe70(&Value, Extra);
    }
    if ( Flags & 2 )
    {
        Stream->Unk_10d9e050(&Value);
        Unk_10afff60(&Value, Extra);
    }
}
