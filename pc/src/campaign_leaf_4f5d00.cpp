// campaign_leaf_4f5d00.cpp -- method at VA 0x10df5d00: for each index from its second argument to
// its third, reads a value and a marker from the stream that is its first argument (method at VA
// 0x10d9df90), then passes the stream, the value and the index to the method at VA 0x10dfa5e0. The
// class, method and parameter names are invented; the addresses are the binary's.

class UnkType_10df5d00_Reader
{
public:
    void Unk_10d9df90(int* Value);
};

class UnkType_10df5d00
{
public:
    void Unk_10df5d00(UnkType_10df5d00_Reader* Reader, unsigned int First, unsigned int Last);
    void Unk_10dfa5e0(UnkType_10df5d00_Reader* Reader, int Value, unsigned int Index);
};

// UnkType_10df5d00::Unk_10df5d00
void UnkType_10df5d00::Unk_10df5d00(UnkType_10df5d00_Reader* Reader,
                                    unsigned int First, unsigned int Last)
{
    for ( unsigned int i = First; i <= Last; i++ )
    {
        int Value;
        int Marker;
        Reader->Unk_10d9df90(&Value);
        Reader->Unk_10d9df90(&Marker);
        Unk_10dfa5e0(Reader, Value, i);
    }
}
