// campaign_leaf_4f5d60.cpp -- method at VA 0x10df5d60: for each index from its second argument to
// its third, writes to the stream that is its first argument the result of the method at VA
// 0x10df8f20 for the index and the marker 0xdeadbeef (method at VA 0x10d9e850), then passes the
// stream and the index to the method at VA 0x10df8f70. The class, method and parameter names are
// invented; the marker and the addresses are the binary's.

class UnkType_10df5d60_Writer
{
public:
    void Unk_10d9e850(int Value);
};

class UnkType_10df5d60
{
public:
    void Unk_10df5d60(UnkType_10df5d60_Writer* Writer, unsigned int First, unsigned int Last);
    int Unk_10df8f20(unsigned int Index);
    void Unk_10df8f70(UnkType_10df5d60_Writer* Writer, unsigned int Index);
};

// UnkType_10df5d60::Unk_10df5d60
void UnkType_10df5d60::Unk_10df5d60(UnkType_10df5d60_Writer* Writer,
                                    unsigned int First, unsigned int Last)
{
    for ( unsigned int i = First; i <= Last; i++ )
    {
        Writer->Unk_10d9e850(Unk_10df8f20(i));
        Writer->Unk_10d9e850(0xdeadbeef);
        Unk_10df8f70(Writer, i);
    }
}
