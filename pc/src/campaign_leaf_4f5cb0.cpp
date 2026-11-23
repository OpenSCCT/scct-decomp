// campaign_leaf_4f5cb0.cpp -- method at VA 0x10df5cb0: for each index from its second argument to
// its third, writes to the stream that is its first argument the result of the method at VA
// 0x10dfa380 for the index and the marker 0xdeadbeef (method at VA 0x10d9e850), then passes the
// stream and the index to the method at VA 0x10dfa400. The class, method and parameter names are
// invented; the marker and the addresses are the binary's.

class UnkType_10df5cb0_Writer
{
public:
    void Unk_10d9e850(int Value);
};

class UnkType_10df5cb0
{
public:
    void Unk_10df5cb0(UnkType_10df5cb0_Writer* Writer, unsigned int First, unsigned int Last);
    int Unk_10dfa380(unsigned int Index);
    void Unk_10dfa400(UnkType_10df5cb0_Writer* Writer, unsigned int Index);
};

// UnkType_10df5cb0::Unk_10df5cb0
void UnkType_10df5cb0::Unk_10df5cb0(UnkType_10df5cb0_Writer* Writer,
                                    unsigned int First, unsigned int Last)
{
    for ( unsigned int i = First; i <= Last; i++ )
    {
        Writer->Unk_10d9e850(Unk_10dfa380(i));
        Writer->Unk_10d9e850(0xdeadbeef);
        Unk_10dfa400(Writer, i);
    }
}
